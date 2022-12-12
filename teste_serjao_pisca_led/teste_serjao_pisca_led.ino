
void desliga(void *param){
  (void)param;
  uint16_t n;
 digitalWrite(15, LOW);


}

void liga(void *param){
  (void)param;
  uint16_t i;
digitalWrite(15, HIGH);
 delay(1000);
  
}

void setup() {
  Serial.begin(9600);
  
  xTaskCreate(liga,"liga",1024,NULL,1,NULL);
  xTaskCreate(desliga,"desliga",1024,NULL,2,NULL);
  
  pinMode(15,OUTPUT);
}

void loop(){
}
