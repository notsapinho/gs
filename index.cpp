#include <Adafruit_LiquidCrystal.h>   // Biblioteca para usar displays LCD 

Adafruit_LiquidCrystal lcd(0);        // Cria o objeto LCD

const byte potentiometerPin = A0;     // Pino analógico onde o potenciômetro está ligado
const byte buzzerPin        = 4;      // Pino digital que aciona o buzzer (alerta sonoro)
const byte indicatorLedPin  = 5;      // Pino digital para o LED indicador (alerta visual)

bool emitted = false;                 // Flag para sabermos se o alerta já foi disparado (evita repetir comandos)

void setup() {
  lcd.begin(16, 2);                   // Inicializa o display LCD: 16 colunas, 2 linhas

  pinMode(indicatorLedPin, OUTPUT);   // LED como saída
  digitalWrite(indicatorLedPin, LOW); // Garante que o LED comece apagado

  pinMode(buzzerPin, OUTPUT);         // Buzzer como saída
  noTone(buzzerPin);                  // Garante buzzer silencioso na inicialização

  pinMode(potentiometerPin, INPUT);   // Leitura analógica do potenciômetro
}

void loop() {
  lcd.setCursor(0, 0);                // Coloca o cursor na primeira linha, primeira coluna do LCD
  
  int value = analogRead(potentiometerPin);   // Lê o valor bruno-bruto (0 – 1023) do potenciômetro
  
  /* 
     Converte (map) o intervalo de 0-1023 para 0-20 cm. 
     Isso simula um sensor de nível
  */
  int mapped = map(value, 0, 1023, 0, 20);
  
  /* ----------------------------- LÓGICA DE ALERTA ----------------------------- */
  if (mapped >= 10) {                           // Se o nível é 10 cm ou mais → condição crítica
    lcd.print("ALERTA CRITICO!");               // Linha 0: mensagem de alerta
    lcd.setCursor(0, 1);                        // Linha 1
    lcd.print("AGUA SUBINDO");                  // Mensagem extra
    tone(buzzerPin, 1000);                      // Gera tom de 1 kHz (buzzer ativo)
    emitted = true;                             // Marca que o alerta foi emitido
    digitalWrite(indicatorLedPin, HIGH);        // Acende o LED indicador
  } else {
    /* Se o nível voltou ao normal e havia um alerta ativo, limpa o display e silencia tudo */
    if (emitted) {
      lcd.clear();                              // Limpa as duas linhas do LCD
      digitalWrite(indicatorLedPin, LOW);       // Apaga o LED
      noTone(buzzerPin);                        // Desliga o buzzer
      emitted = false;                          // Reseta a flag
    }
    
    /* Exibe leitura normal do nível d'água em cm */
    lcd.print("Nivel da agua: ");
    lcd.setCursor(0, 1);
    lcd.print(String(mapped) + " cm");
  }
}
