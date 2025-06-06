#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const byte potentiometerPin = A0;    
const byte buzzerPin = 4;  
const byte indicatorLedPin = 5;  

bool emitted = false;

void setup() {
  lcd.begin(16, 2);

  pinMode(indicatorLedPin, OUTPUT);
  digitalWrite(indicatorLedPin, LOW);
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  pinMode(potentiometerPin, INPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  
  int value = analogRead(potentiometerPin);
  
  //Limita o potênciometro de 0 a 20
  int mapped = map(value, 0, 1023, 0, 20);
  
  if (mapped >= 10) {
  	lcd.print("ALERTA CRITICO!");
    lcd.setCursor(0, 1);
    lcd.print("AGUA SUBINDO");
    tone(buzzerPin, 1000);
    emitted = true;
    digitalWrite(indicatorLedPin, HIGH);
  } else {
    if(emitted) {
    	lcd.clear();
        digitalWrite(indicatorLedPin, LOW);
      	noTone(buzzerPin);
      	emitted = false;
    }
    lcd.print("Nivel da agua: ");
    lcd.setCursor(0, 1);
    lcd.print(String(mapped) + " cm");
  }
}
