#include <Arduino.h>
#include <Wire.h>

#define NUM_SENSORS 16
#define BUFFER_SIZE 5

#define MUX_A0 8
#define MUX_A1 9
#define MUX_A2 10
#define MUX_SIG1 A0 // Сигнал 1-го мультиплексора
#define MUX_SIG2 A7 // Сигнал 2-го мультиплексора

#define I2C_SLAVE_ADDRESS 8 // Адрес I2C меги


class IRDirectionFinder {
private:
    const double angle_step = 22.5;
    double buffer[BUFFER_SIZE];
    uint8_t buffer_index = 0;
    bool buffer_filled = false;
    const double epsilon = 1e-5;

    double deg2rad(double degrees) {
        return degrees * M_PI / 180.0;
    }

    double rad2deg(double radians) {
        radians = fmod(radians, 2 * M_PI);
        if (radians < 0) radians += 2 * M_PI;
        return radians * 180.0 / M_PI;
    }

    // Кластеризация с использованием статических массивов
    void findClusters(const uint8_t data[], uint8_t clusters[][NUM_SENSORS], uint8_t* cluster_sizes, uint8_t* num_clusters) {
        uint8_t double_data[NUM_SENSORS * 2];
        memcpy(double_data, data, NUM_SENSORS);
        memcpy(double_data + NUM_SENSORS, data, NUM_SENSORS);

        uint8_t current_cluster[NUM_SENSORS];
        uint8_t current_size = 0;
        *num_clusters = 0;

        for (uint8_t i = 0; i < NUM_SENSORS * 2; i++) {
            if (double_data[i]) {
                if (current_size < NUM_SENSORS) {
                    current_cluster[current_size++] = i;
                }
            } else if (current_size > 0) {
                addNormalizedCluster(current_cluster, current_size, clusters, cluster_sizes, num_clusters);
                current_size = 0;
            }
        }

        if (current_size > 0) {
            addNormalizedCluster(current_cluster, current_size, clusters, cluster_sizes, num_clusters);
        }
    }

    void addNormalizedCluster(uint8_t cluster[], uint8_t size, uint8_t clusters[][NUM_SENSORS], uint8_t cluster_sizes[], uint8_t* num_clusters) {
        uint8_t normalized[NUM_SENSORS] = {0};
        uint8_t norm_size = 0;

        // Нормализация индексов и удаление дубликатов
        for (uint8_t i = 0; i < size; i++) {
            uint8_t idx = cluster[i] % NUM_SENSORS;
            if (!normalized[idx]) {
                normalized[idx] = 1;
                norm_size++;
            }
        }

        // Проверка на уникальность кластера
        for (uint8_t i = 0; i < *num_clusters; i++) {
            if (cluster_sizes[i] != norm_size) continue;
            
            bool match = true;
            for (uint8_t j = 0; j < NUM_SENSORS; j++) {
                if ((clusters[i][j] != 0) != (normalized[j] != 0)) {
                    match = false;
                    break;
                }
            }
            if (match) return;
        }

        // Добавление нового кластера
        if (*num_clusters < NUM_SENSORS) {
            memcpy(clusters[*num_clusters], normalized, NUM_SENSORS);
            cluster_sizes[*num_clusters] = norm_size;
            (*num_clusters)++;
        }
    }

    double vectorAverage(const uint8_t cluster[]) {
        double x_sum = 0.0;
        double y_sum = 0.0;
        uint8_t count = 0;

        for (uint8_t i = 0; i < NUM_SENSORS; i++) {
            if (cluster[i]) {
                double angle_rad = deg2rad(i * angle_step);
                x_sum += cos(angle_rad);
                y_sum += sin(angle_rad);
                count++;
            }
        }

        if (count == 0) return 0.0;

        double magnitude = sqrt(x_sum * x_sum + y_sum * y_sum);
        if (magnitude < epsilon) return 0.0;

        double angle_rad = atan2(y_sum, x_sum);
        return rad2deg(angle_rad);
    }

    double smoothBuffer() {
        if (buffer_index == 0 && !buffer_filled) return 0.0;

        double x_sum = 0.0;
        double y_sum = 0.0;
        uint8_t count = buffer_filled ? BUFFER_SIZE : buffer_index;

        for (uint8_t i = 0; i < count; i++) {
            double angle_rad = deg2rad(buffer[i]);
            x_sum += cos(angle_rad);
            y_sum += sin(angle_rad);
        }

        double magnitude = sqrt(x_sum * x_sum + y_sum * y_sum);
        if (magnitude < epsilon) return 0.0;

        double angle_rad = atan2(y_sum, x_sum);
        double result = rad2deg(angle_rad);
        
        return (fabs(result) < epsilon) ? 0.0 : result;
    }

public:
    IRDirectionFinder() {
        memset(buffer, 0, sizeof(buffer));
    }

    double update(const uint8_t sensor_data[], const uint8_t scrap[]) {
        // Буфер для кластеров
        uint8_t clusters[NUM_SENSORS][NUM_SENSORS];
        uint8_t cluster_sizes[NUM_SENSORS];
        uint8_t num_clusters = 0;

        findClusters(sensor_data, clusters, cluster_sizes, &num_clusters);

        if (num_clusters == 0) {
            return smoothBuffer();
        }

        // Поиск самого большого кластера
        uint8_t main_index = 0;
        uint8_t max_size = cluster_sizes[0];
        for (uint8_t i = 1; i < num_clusters; i++) {
            if (cluster_sizes[i] > max_size) {
                max_size = cluster_sizes[i];
                main_index = i;
            }
        }

        double current_angle = vectorAverage(clusters[main_index]);

        // Обновление кольцевого буфера
        buffer[buffer_index] = current_angle;
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;
        if (buffer_index == 0) buffer_filled = true;

        return smoothBuffer();
    }
};


class Multiplexer {
private:
  const uint8_t s0, s1, s2, analogPin;
  
public:
  Multiplexer(uint8_t s0_pin, uint8_t s1_pin, uint8_t s2_pin, uint8_t mux_pin) 
    : s0(s0_pin), s1(s1_pin), s2(s2_pin), analogPin(mux_pin) {}

  void begin() {
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    setChannel(0);
  }

  void setChannel(uint8_t channel) {
    digitalWrite(s0, channel & 0b001);
    digitalWrite(s1, channel & 0b010);
    digitalWrite(s2, channel & 0b100);
  }

  bool readChannel(uint8_t channel) {
    setChannel(channel);
    delayMicroseconds(20); // Стабилизация сигнала
    return (analogRead(analogPin) < 512);
  }
};



class IRSensorSystem {
private:
  Multiplexer mux1, mux2;
  
public:
  bool sensors1[8], sensors2[8];

  IRSensorSystem(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t mux1_pin, uint8_t mux2_pin)
    : mux1(s0, s1, s2, mux1_pin), mux2(s0, s1, s2, mux2_pin) {}

  void begin() {
    mux1.begin();
    mux2.begin();
  }

  void scanAll() {
    for (uint8_t ch = 0; ch < 8; ch++) {
      sensors1[ch] = mux1.readChannel(ch);
      sensors2[ch] = mux2.readChannel(ch);
    }
  }

  void printData() {
    Serial.println("\n--- ИК датчики ---");
    
    Serial.print("MUX1: ");
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(sensors1[i] ? "[ACT] " : "[---] ");
    }
    
    Serial.print("\nMUX2: ");
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(sensors2[i] ? "[ACT] " : "[---] ");
    }
    
    Serial.println("\n------------------");
  }
};

// Функция упаковки массива bool в один байт (окак)
byte packBoolArray(bool arr[8]) {
  byte result = 0;
  for (int i = 0; i < 8; i++) {
    if (arr[i]) {
      result |= (1 << i);  // Устанавливаем бит если значение true
    }
  }
  return result;
}
void printBinary(byte b) {
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(b, i));
  }
}

// Создание объекта для систем датчиков
IRDirectionFinder directionFinder;
IRSensorSystem sensorSystem(8, 9, 10, A0, A6);

void setup() {
    Serial.begin(115200);
    sensorSystem.begin();
    Wire.begin(I2C_SLAVE_ADDRESS);                // join i2c bus with address #8
    Wire.onRequest(requestEvent);
}

void loop() {
delay(100);
/*
    uint8_t sensor_data1[NUM_SENSORS] = {
        0, 0, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    uint8_t sensor_data2[NUM_SENSORS] = {
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    
    double angle = directionFinder.update(sensor_data2, sensor_data1);
    
    Serial.print("Угол источника: ");
    Serial.print(angle, 2); 
    Serial.println("°");
*/
}

void requestEvent() {
  sensorSystem.scanAll();
  byte packedByte1 = packBoolArray(sensorSystem.sensors1);
  byte packedByte2 = packBoolArray(sensorSystem.sensors2);
  
  Wire.write(packedByte1);  // Отправляем первый байт
  Wire.write(packedByte2);  // Отправляем второй байт
}
