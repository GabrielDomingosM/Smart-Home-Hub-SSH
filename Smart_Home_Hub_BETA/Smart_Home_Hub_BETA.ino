/*
   Smart Home Hub with Alexa
   Nomes: Gabriel Domingos e Guilherme Rodrigues
   Turma: 2190
*/

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


#define R1 15
#define R2 2
#define R3 4
#define R4 22


boolean connectWifi();

//chamando as função
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);



// Informações do WiFi
const char* nome_wifi = "SATC IOT"; // nome do wifi
const char* senha_wifi = "IOT2023@"; // senha do wifi

// Nome dos dispositivos
String Device_1_Name = "Lâmpada sala";
String Device_2_Name = "Lâmpada quarto"; 
String Device_3_Name = "Ventiador"; 
String Device_4_Name = "Lâmpada cozinha";  

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  // Inicializa a conexão Wifi
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Defina os dispositivos aqui
    !espalexa.addDevice(Device_1_Name, firstLightChanged); 
    !espalexa.addDevice(Device_2_Name, secondLightChanged); 
    !espalexa.addDevice(Device_3_Name, thirdLightChanged);
    !espalexa.addDevice(Device_4_Name, fourthLightChanged);

    espalexa.begin();

  }

  else
  {
    while (1)
    {
      Serial.println("Não é possível conectar-se ao WiFi. Verifique os dados e reinicie o ESP.");
      delay(2500);
    }
  }

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//Chama a função do primeiro dispositivo
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R1, HIGH);
      Serial.println("Lâmpada sala - Ligada");
    }
    
  }
  else
  {
    digitalWrite(R1, LOW);
    Serial.println("Lâmpada sala - Desligada");
  }
}

void secondLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, HIGH);
      Serial.println("Lâmpada quarto - Ligada");
    }
    
  }
  else
  {
    digitalWrite(R2, LOW);
    Serial.println("Lâmpada quarto - Desligada");
  }
}

void thirdLightChanged(uint8_t brightness)
{

  //Control the device  
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R3, HIGH);
      Serial.println("Ventilador - Ligado");
    }
    
  }
  else
  {
    digitalWrite(R3, LOW);
    Serial.println("Ventilador - Desligado");
  }
}


void fourthLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R4, HIGH);
      Serial.println("Lâmpada cozinha - Ligada");
    }
    
  }
  else
  {
    digitalWrite(R4, LOW);
    Serial.println("Lâmpada cozinha - Desligada");
  }
}


// conectar-se ao wifi – retorna verdadeiro se for bem-sucedido ou falso se não
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(nome_wifi, senha_wifi);
  Serial.println("");
  Serial.println("Conectando ao WiFi");

  // Wait for connection
  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Conectando em ");
    Serial.println(ssid);
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Conexão falhou.");
  }
  return state;
}