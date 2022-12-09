//Turn Samsung TV on/off repeatedly to test program. IR LED connected to pin 3.

#include <IRremote.h>

#define POWER         0XE0E06798E0E06798            //from IRrecvDemo, Ken Shirriff
#define SAMSUNG_BITS  16 

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  pinMode (15, OUTPUT);  //output as used in library
}

void loop() {

  irsend.sendSAMSUNG(POWER, SAMSUNG_BITS); 
  Serial.println("COMANDO ENVIADO");
  delay (5000);

}//end of loop
