#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
#define WIFI_SSID "SamuelSM"
#define WIFI_PASSWORD "05070105"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5626767221:AAEhce_SRFEaddt89Axs47tgsq8TI1El7mY"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const int ledPin = 15;
int ledStatus = 0;


void desliga(void *param){
  (void)param;
  uint16_t n;
 digitalWrite(ledPin, LOW);

}

void liga(void *param){
  (void)param;
  uint16_t i;
digitalWrite(ledPin, HIGH);
  
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // initialize pin as off (active LOW)

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
  xTaskCreate(liga,"liga",4096,NULL,1,NULL);
  xTaskCreate(desliga,"desliga",4096,NULL,1,NULL);
  
  pinMode(18,OUTPUT);
}

void loop(){

}
