

/*Descritor de timer */
TimerHandle_t timerHndl1Sec;

/* Descritor de task */
TaskHandle_t taskrun;

/* Callback de timer. É chamado quando experirar o timer. */
static void vTimerCallback1SecExpired(TimerHandle_t pxTimer) {
  xTaskNotifyGive(taskrun);
}

/* Tarefa que recebe notificação do callback de timer.  */
void TaskRun(void *param){
  (void) param;
  uint16_t count = 0;

  for(;;){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    digitalWrite(2, !digitalRead(2));
    
    Serial.println(count++);
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(2, OUTPUT);

  /* Criação do Timer. */
  timerHndl1Sec = xTimerCreate(
      "timer1Sec", /* name */
      pdMS_TO_TICKS(1000), /* period/time */
      pdTRUE, /* auto reload */
      (void*)0, /* timer ID */
      vTimerCallback1SecExpired); /* callback */
  
  if (timerHndl1Sec==NULL) {
    Serial.println("Timer Error!");
  } 
  
  /* Start timer. */
  xTimerStart(timerHndl1Sec, 0);

  /* Criação da task */
  xTaskCreate( TaskRun,   /* Task function. */
               "TaskRun",     /* name of task. */
               1024,        /* Stack size of task */
               NULL,        /* parameter of the task */
               1,           /* priority of the task */
               &taskrun      /* Task handle to keep track of created task */
             );          /* pin task to core 0 */ 
  
  Serial.println("Running.");
}

void loop(){
  
}
