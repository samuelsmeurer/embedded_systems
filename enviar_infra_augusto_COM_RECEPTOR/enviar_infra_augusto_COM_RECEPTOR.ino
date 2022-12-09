#include <IRremote.h>
int botao = 4;
int RECV_PIN = 15;
int estado_botao = 0;


#define POWER         0XE0E06798E0E06798            //from IRrecvDemo, Ken Shirriff
#define SAMSUNG_BITS  16 
IRsend irsend;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
Serial.begin(9600);

pinMode(2, OUTPUT);
irrecv.enableIRIn(); // Start the receiver
/*digitalWrite(2, 0XE0E06798);*/
pinMode(4, INPUT);

}

void loop() {
  estado_botao = digitalRead(botao);
  Serial.println(estado_botao);
  if (estado_botao == HIGH) {//Se estadoButton for igual a HIGH ou 1
    Serial.println(estado_botao);
    digitalWrite(2,HIGH);
    Serial.println("OI");
    /*irsend.sendSAMSUNG(POWER, SAMSUNG_BITS);*/
 if (irrecv.decode(&results)) {
Serial.println(results.value, HEX);
irrecv.resume(); // Receive the next value
}}
}
