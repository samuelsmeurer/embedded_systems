/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#define ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Espalexa.h>
#include <UniversalTelegramBot.h>

#define ledd 15
int ledStatus = 0;

#define BOT_TOKEN "5626767221:AAEhce_SRFEaddt89Axs47tgsq8TI1El7mY"


WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

unsigned long bot_lasttime; // last time messages' scan has been done


const unsigned long BOT_MTBS = 1000; // mean time between scan messages


boolean connectWifi();

void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

const char* ssid = "NARA RUBIA OI FIBRA 2.4G";
const char* password = "sanais21";

boolean wifiConnected = false;

Espalexa espalexa;


void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "Ligar")
    {
      digitalWrite(ledd, HIGH); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "Desligar")
    {
      ledStatus = 0;
      digitalWrite(ledd,LOW); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/status")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start")
    {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup()
{
  Serial.begin(115200);
  
  // Initialise wifi connection
  wifiConnected = connectWifi();
  pinMode(ledd,OUTPUT);

  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Luz do esp", firstLightChanged); //simplest definition, default state off
    espalexa.addDevice("Light 2", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);


    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();

    if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
   
   delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
    Serial.print("Samuel, a luz do esp está");
    
    digitalWrite(ledd,brightness);


    if (brightness) {
      Serial.print("ON!!!");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF!!");
    }
}

void secondLightChanged(uint8_t brightness) {
  //do what you need to do here
}

void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
