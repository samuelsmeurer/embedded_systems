
#define ref 1.65

float ep;
float ei;
float ed;

float eantp;
float eanti;
float eantd;


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

  ep = ref - y;
 /*
  ei = eanti + (ep + eantp)*(ts/2);
  ed = ( ep - eantp)/ts;
  eantp = ep;
  eanti = ei;
  eantd = ed;
  
  

                

Vin = Kp*erro + Kd*errod + Ki*erroi; %deve ser substituído pela saída do PID e escrever na saída do DAQ

*/
    Serial.println("erro proporcional é:");
    Serial.println(ep);
    Serial.println("---");
    delay(500);
    
}
