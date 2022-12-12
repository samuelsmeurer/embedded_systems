void setup() {
  pinMode(15,INPUT);
 

}

void loop() {
  Serial.begin(9600);
  Serial.println(analogRead(15));
  delay(500);

}
