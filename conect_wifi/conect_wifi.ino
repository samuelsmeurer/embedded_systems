/*
 * Pontos de Acesso com ESP32
 * Miguel Sena - blog.eletrogate.com
 * https://blog.eletrogate.com/pontos-de-acesso-com-esp32/#:~:text=Como%20conectar%3A,rede%20e%20insira%20a%20senha
 */
#include <WiFi.h> //Inclui a biblioteca
const char* ssid = "SamuelSM"; //Define o nome do ponto de acesso
const char* pass = "05070105"; //Define a senha
 
WiFiServer sv(80); //Cria um servidor na porta 80
void setup() {
  Serial.begin(115200); //Inicia o monitor serial
  pinMode(15, OUTPUT);  //Define a porta 23 como saída
  delay(10);  //Atraso de 10 milissegundos
  Serial.println("\n"); //Pula uma linha
  WiFi.softAP(ssid, pass); //Inicia o ponto de acesso
  Serial.print("Se conectando a: "); //Imprime mensagem sobre o nome do ponto de acesso
  Serial.println(ssid);
  IPAddress ip = WiFi.softAPIP(); //Endereço de IP
  
  Serial.print("Endereço de IP: "); //Imprime o endereço de IP
  Serial.println(ip);
  sv.begin(); //Inicia o servidor 
  Serial.println("Servidor online"); //Imprime a mensagem de início
}
void loop() {
  WiFiClient client = sv.available(); //Cria o objeto cliente
  if (client) { //Se este objeto estiver disponível
    String line = ""; //Variável para armazenar os dados recebidos
    while (client.connected()) { //Enquanto estiver conectado
      if (client.available()) { //Se estiver disponível
        char c = client.read(); //Lê os caracteres recebidos
        if (c == '\n') { //Se houver uma quebra de linha
          if (line.length() == 0) { //Se a nova linha tiver 0 de tamanho
            client.println("HTTP/1.1 200 OK"); //Envio padrão de início de comunicação
            client.println("Content-type:text/html");
            client.println();
            client.print("Ligue o led clicando <a href=\"/ligar\">aqui</a><br>"); //Linha para ligar o led
            client.print("Desligue o led clicando <a href=\"/desligar\">aqui</a><br>"); //Linha para desligar o led
            client.println();
            break;
          } else {   
            line = "";
          }
        } else if (c != '\r') { 
          line += c; //Adiciona o caractere recebido à linha de leitura
        }
        if (line.endsWith("GET /ligar")) { //Se a linha terminar com "/ligar", liga o led
          digitalWrite(15, HIGH);
          Serial.println("ligado");             
        }
        if (line.endsWith("GET /desligar")) { //Se a linha terminar com "/desligar", desliga o led
          digitalWrite(15, LOW); 
          Serial.println("desligado");              
        }
      }
    }
    client.stop(); //Para o cliente
  }
}
