void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}
int k;
long timing;
long timer;
void loop() {
  // put your main code here, to run repeatedly:
  timing = millis(); 
  if((digitalRead(3)>0) and (timing-timer > 400)) {
    k++;
    timer = timing;
    Serial.println(1);
  }
  //Serial.println('b');
}
