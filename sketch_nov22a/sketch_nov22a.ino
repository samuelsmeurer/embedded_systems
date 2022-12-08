
void print1(void *arg) {
  while(1){
    Serial.println("1");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}
void print2(void *arg) {
  while(1){
    Serial.println("0");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}

void setup() {
  Serial.begin(9600);
  
  xTaskCreate(print1,
  "print1",
  1024,
  NULL,
  1,
  NULL);
    
  xTaskCreate(print2,
  "print2",
  1024,
  NULL,
  1,
  NULL);
  
}

void loop() {
  Serial.println("2");

} 
