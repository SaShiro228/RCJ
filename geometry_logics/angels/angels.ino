  float a_b = 90;

  
  float a1 = 30;
  float a2 = 45;
  float x1 = 14;
  float x2 = 7;
  float y1 = 0;
  float y2 = 0;
  
  float sin1 = 0;
  float sin2 = 0;
  float sin3 = 0;
  float sin4 = 0;
  float sin5 = 0;
  float buf;
  
  float g90=1.5708;
  float g180=3.14159;
  float g270=4.71239;
  float g360=6.28319;
  
  float l1 = 0;
  float l2 = 0;
  float l3 = 0;
  float x = 0;
  float y = 0;

void setup() {
  Serial.begin(9600);
  l1=fabs(x1-x2);
  l2=fabs(y1-y2);
  l3=sqrt(sq(l1)+sq(l2));
  a1=3.14/180*a1; 
  a2=3.14/180*a2;
  
  angel2();
  Serial.print(x);
  Serial.print(" // ");
  Serial.println(y);
}

  
void loop() {
  
}

void angel1(){ 
  sin1=l2/l3;
  sin2=a2-a1;
  sin3=a1+asin(sin1);
  sin4=a2-g90;
  sin5=g180-a2;
  x=l3*sin(sin3)*sin(sin4)/sin(sin2);
  y=l3*sin(sin3)*sin(sin5)/sin(sin2);
  x=x2+x;
  y=y2+y;
}

void angel2(){ 
  sin1=l2/l3;
  sin2=a2-a1;
  sin3=a1+asin(sin1);
  sin4=g90-a2;
  x=l3*sin(sin3)*sin(sin4)/sin(sin2);
  y=l3*sin(sin3)*sin(a2)/sin(sin2);
  x=x2-x;
  y=y2+y;
}
