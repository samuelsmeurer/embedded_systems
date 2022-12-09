#include <IRremote.h>

IRsend irsend;



decode_results results;

void setup()
{
Serial.begin(9600);

pinMode(15, OUTPUT);/*
digitalWrite(15, 0x36440000);*/

}

void loop() {
/*
irsend.sendSamsung(0x20DFD02F, 15);
irsend.sendSamsung(0x3772802968, 15);*/

irsend.sendNEC(15, 0x36440000);
Serial.println("comando informado");
delay(5000);
}
