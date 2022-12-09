#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// informacoes do wifi
#define WIFI_SSID "SamuelSM"
#define WIFI_PASSWORD "05070105"

// token do bot
#define token_bot "5626767221:AAEhce_SRFEaddt89Axs47tgsq8TI1El7mY"

const unsigned long BOT_MTBS = 1000; // tempo entre as verificações de mensagens 

WiFiClientSecure secured_client;

UniversalTelegramBot bot(token_bot, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const int pino_led = 15;
int status_led = 0;

void novas_mensagens(int num_novas_mensagens)
{
  Serial.println(num_novas_mensagens);
  Serial.print("nova mensagem");
  

  for (int i = 0; i < num_novas_mensagens; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    Serial.println(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "Ligar")
    {
      digitalWrite(ledPin, HIGH); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "Desligar")
    {
      ledStatus = 0;
      digitalWrite(pino_led,LOW); // turn the LED off (LOW is the voltage level)
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
  Serial.println();

  pinMode(pino_led, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(pino_led, HIGH); // initialize pin as off (active LOW)

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
}

void loop()
{
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
}
