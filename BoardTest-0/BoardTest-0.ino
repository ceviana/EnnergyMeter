// VERSÃO DE TESTES PARA PORTA SERIAL. SEM CONEXÃO COM INTERNET!!!!!
// PLACA WEMOS - D1 R2 & MINI
// BN: Unknown board + VID: 1A86 + PID: 7523
// CPU: 80 MHz + FLASH SIZE: 4M (3M SPIFFS) + UPLOAD SPEED: 921600 bps
// http://arduino.esp8266.com/stable/package_esp8266com_index.json 
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// ESP8266 TYPE 12 - PROGRAM HEADER TEMPLATE - 2017 - FEBRUARY
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// COMPILED ARDUINO IDE VERSION - 1.8.1 - WEMOS - D1 R2 & MINI
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define      LED_BUILTIN   2    // LED_BUILTIN
#define      LED_EXTERNAL  D1    // EXTERNAL LED
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// EXTERNAL LIBRARIES - UPDATE IF THEY ARE NOT!
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#include     <ESP8266WiFi.h>  //  LIB TO CONFIGURE THE TRANSCEIVER
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// SENSOR PINS SETTINGS
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// GLOBAL VARIABLES DEFINITIONS
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
unsigned T = 0, F = 0;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// LED BLINK FUNCTION
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void LedATLblinks(unsigned M) {
  Serial.print("\n| JUST EXT LED IS BLINKING N TIMES: "); Serial.print(M);
  Serial.println("   - - - - - |");
  Serial.print("| ");
  for (short j = 0; j < M; j++) {F++;
    Serial.print(j + 1);  Serial.print(" | ");
    digitalWrite(LED_EXTERNAL, HIGH);                         delay(100);
    digitalWrite(LED_EXTERNAL, LOW);                        delay(2500);}
  digitalWrite(LED_EXTERNAL, LOW);
  digitalWrite(LED_BUILTIN, LOW);                             delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
//Serial.println("\n| - - - - - - - - - - - - - - - - - - - - - - - - |");
  Serial.print("\n| CONTINUOUS COUNTER UP TO NOW:   >---> | ");
  Serial.print(F);
  Serial.print(" |");
  Serial.print("\n| - - - - - - BUILTIN LED BLINKS! - - - - - - - - |");
Serial.println("\n| - - - - - - - - - - - - - - - - - - - - - - - - |");}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// ANOTHER FUNCTION HERE!
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
float getPressure() {/*YOUR CODE HERE*/}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// SETUP WILL RUN JUST ONCE!
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void setup() {                         // COMMENT - UNCOMMENT AS NECESSARY
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN - output
  digitalWrite(LED_BUILTIN, HIGH);    // turn LED OFF - acive low on ESP07
  pinMode(LED_EXTERNAL, OUTPUT);    // Initialize the LED_BUILTIN - output
  digitalWrite(LED_EXTERNAL, LOW);    // turn LED ON - acive low on ESP07

/*----------------------------------------------------------------------*/
  Serial.begin(115200);
  Serial.print("\n| - - - - - - - - - - - - - - - - - - - - - - - - |");
  Serial.print("\n| PLACA WEMOS - D1 R2 & MINI  - - - - - - - - - - |");
  Serial.print("\n| BN: Unknown board + VID: 1A86 + PID: 7523 - - - |");
  Serial.print("\n| CPU: 80 MHz + FLASH SIZE: 4M (3M SPIFFS)  - - - |");
  Serial.print("\n| ULTIMA ATUALIZACAO: 16/02/2017  - - - - - - - - |");
  Serial.print("\n| - - - - - - - - - - - - - - - - - - - - - - - - |");
  Serial.print("\n| Informacoes do ESP8266  - - - - - - - - - - - - |");
  Serial.print("\n| MAC NUMBER: " + WiFi.macAddress());
  Serial.print(" - - - - - - - - - |");
  Serial.print("\n| - - - - - - - - - - - - - - - - - - - - - - - - |");
/* YOUR SETTINGS HERE!!!*/
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// LOOP FUNCTION RUNS LIKE A WHILE LOOP IN ANY LANGUAGE
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void loop() {
LedATLblinks(T);    T++;  if (T == 10) T = 0;
//  F++; // CONTADOR SEM FIM DESDE QUE FOI LIGADO!
/* YOUR CODE HERE!!!*/
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// MAIN FUNCTION END - FINAL
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

