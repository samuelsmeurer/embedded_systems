
void print1(void *arg) {
  while(1){
    Serial.println("oi");
    delay(10000);
  }

}
void print2(void *arg) {
  while(1){
    if(analogRead(18)==4095){
digitalWrite(15,HIGH);}
else{
  digitalWrite(15,LOW);
}}}

void setup() {
  Serial.begin(9600);
  pinMode(25, INPUT);
  pinMode(15,OUTPUT);
  
  xTaskCreate(print1,
  "print1",
  4096,
  NULL,
  1,
  NULL);
    
  xTaskCreate(print2,
  "print2",
  4096,
  NULL,
  1,
  NULL);
  
}

void loop() {

} 
