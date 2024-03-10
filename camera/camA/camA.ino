void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


int cam() {
  int f1;
  int f2;
  int camturn = 0;
  f1 = analogRead(A4);
  f2 = analogRead(A6);
  if ((f1 > 100) and (f2 > 100)){
    camturn = 3;
  }else if ((f1 > 100) and (f2 < 100)){
    camturn = 2;
  }else if ((f1 < 100) and (f2 > 100)){
    camturn = 1;
  }else if ((f1 < 100) and (f2 < 100)){
    camturn = 0;
  }
  return camturn;
}
void loop(){
  Serial.println(cam());
}
