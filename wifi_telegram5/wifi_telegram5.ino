  #include <WiFi.h>

#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>


/* Credenciais wi-fi */
#define ssid_wifi "NARA RUBIA OI FIBRA 2.4G"      /* Coloque aqui o nome da rede wiifi que o ESP32 deve se conectar */
#define password_wifi "sanais21"  /* Coloque aqui a senha da rede wiifi que o ESP32 deve se conectar */
 
/* Definições do Telegram */
#define TEMPO_ENTRE_CHECAGEM_DE_MENSAGENS   250 //ms
 
/* Token de acesso Telegram */
#define token_acesso_telegram "5626767221:AAEhce_SRFEaddt89Axs47tgsq8TI1El7mY"
#define CMD_LIGA_RELE_1         "L1"
#define CMD_DESLIGA_RELE_1      "L2"
/* GPIOs usados */
#define GPIO_RELE1              15

 
/* Variáveis e objetos globais */
WiFiClientSecure client;
UniversalTelegramBot bot(token_acesso_telegram, client);
unsigned long timestamp_checagem_msg_telegram = 0;
int num_mensagens_recebidas_telegram = 0;
String resposta_msg_recebida;
 
/* Prototypes */
void init_wifi(void);
void conecta_wifi(void);
void verifica_conexao_wifi(void);
unsigned long diferenca_tempo(unsigned long timestamp_referencia);
String trata_mensagem_recebida(String msg_recebida);
 
/* 
 *  Implementações
 */
  
/* Função: inicializa wi-fi
 * Parametros: nenhum
 * Retorno: nenhum 
 */
void init_wifi(void) 
{
    Serial.println("------WI-FI -----");
    Serial.print("Conectando-se a rede: ");
    Serial.println(ssid_wifi);
    Serial.println("Aguarde...");    
    conecta_wifi();
}
 
/* Função: conecta-se a rede wi-fi
 * Parametros: nenhum
 * Retorno: nenhum 
 */
void conecta_wifi(void) 
{
    /* Se ja estiver conectado, nada é feito. */
    if (WiFi.status() == WL_CONNECTED)
        return;
 
    /* refaz a conexão */
    WiFi.begin(ssid_wifi, password_wifi);
     
    while (WiFi.status() != WL_CONNECTED) 
    {        
        vTaskDelay( 100 / portTICK_PERIOD_MS );
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso a rede wi-fi ");
    Serial.println(ssid_wifi);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}
 
/* Função: verifica se a conexao wi-fi está ativa 
 *         (e, em caso negativo, refaz a conexao)
 * Parametros: nenhum
 * Retorno: nenhum 
 */
void verifica_conexao_wifi(void)
{
    conecta_wifi(); 
}
 
/* Função: calcula a diferença de tempo entre o timestamp
 *         de referência e o timestamp atual
 * Parametros: timestamp de referência
 * Retorno: diferença de tempo 
 */

 
void setup() 
{
    Serial.begin(115200);
     
    /* Configura GPIOs de controle dos relés e deixa 
       todos os relés desacionados */
    pinMode(GPIO_RELE1, OUTPUT);
    digitalWrite(GPIO_RELE1, HIGH);

 

    /* Inicializa a conexão wi-fi */
    init_wifi();
 
    /* Inicializa timestamp de checagem de mensagens recebidas via Telegram 
    */
}
 
void loop() 
{
    int i;
      Serial.println("to aqui2");
      Serial.println(num_mensagens_recebidas_telegram);

      delay(1000);
        num_mensagens_recebidas_telegram = bot.getUpdates(bot.last_message_received + 1);
 
}
