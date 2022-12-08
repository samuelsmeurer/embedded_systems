
#define ref 2047

float vout=4095;
float ep;


float x;

double y;
void setup() {
  pinMode(25,INPUT);
  pinMode(26,OUTPUT);
  Serial.begin(9600);
  analogWrite(26,4095);
}

void loop() {
  x = analogRead(25);

  
  ep = x - ref;

  vout = vout - ep;

  
  analogWrite(26,vout);
   
  y = x*3.3/4095;
  Serial.println(y);
  


 
  Serial.println("vout é:");
  Serial.println(ep);
  Serial.println("---");
  delay(500);
    
}
