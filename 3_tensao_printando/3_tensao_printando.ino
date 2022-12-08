
float x;
double y;
void setup() {
  pinMode(25,INPUT);
  pinMode(26,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  x = analogRead(25);
  
  analogWrite(26,x);
  y = x*3.3/4095;
    Serial.println(y);
    delay(500);
}
