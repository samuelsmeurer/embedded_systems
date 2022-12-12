
QueueHandle_t fila;


void Consumidor(void *param){
  (void)param;
  uint16_t n;
  
  for(;;){
    if (xQueueReceive(fila, &n, pdMS_TO_TICKS(1)) == pdFALSE){
      Serial.println("Consumidor Fila Vazia.");
      continue;
    }
    Serial.println(n);
  }
}

void Produtor(void *param){
  for(;;){
    Serial.println("A");
  }
  
}

void setup() {
  Serial.begin(9600);

  fila = xQueueCreate(5, sizeof(uint16_t));
  
  xTaskCreate(Produtor,"Produtor",2048,NULL,1,NULL);
  xTaskCreate(Consumidor,"Consumidor",2048,NULL,1,NULL);
}

void loop(){

}  
