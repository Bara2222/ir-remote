#include <Arduino.h> // Vložení hlavičkového souboru Arduino.h.

// Nastavení použití alternativního časovače pro knihovnu IRremote.
#define IR_USE_ARV_TIMER 1

#include <IRremote.hpp> // Vložení knihovny pro práci s IR přijímačem.

#define IR_RECEIVE_PIN 12 // Definice pinu pro připojení IR přijímače.

// Definice pinů pro řízení RGB LED.
#define REDPIN 9
#define GREENPIN 6
#define BLUEPIN 5

// Definice kódů tlačítek na dálkovém ovladači pro různé barvy.
#define IR_BUTTON_RED 4077715200   // Kód pro červenou barvu.
#define IR_BUTTON_GREEN 3877175040 // Kód pro zelenou barvu.
#define IR_BUTTON_BLUE 2707357440  // Kód pro modrou barvu.

int bar[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Rozsah pinů pro LED bar.

// Pole IR kódů odpovídajících tlačítkům na dálkovém ovladači.
unsigned long codes[] = {
    3910598400, // Kód pro 0
    4077715200, // Kód pro 1
    3877175040, // Kód pro 2
    2707357440, // Kód pro 3
    4144561920, // Kód pro 4
    3810328320, // Kód pro 5
    2774204160, // Kód pro 6
    3175284480, // Kód pro 7
    2907897600, // Kód pro 8
    3041591040, // Kód pro 9
};

int codesSize = sizeof(codes) / sizeof(codes[0]); // Počet prvků v poli kódů.

String stringNum = ""; // Inicializace prázdného řetězce pro uchování čísla.

// Funkce pro nastavení barvy RGB LED.
void setColor(int red, int green, int blue) {
  analogWrite(REDPIN, red);   // Nastavení hodnoty pro červenou barvu.
  analogWrite(GREENPIN, green); // Nastavení hodnoty pro zelenou barvu.
  analogWrite(BLUEPIN, blue);   // Nastavení hodnoty pro modrou barvu.
}

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializace IR přijímače.
  Serial.begin(9600);  // Inicializace sériové komunikace.
  // Inicializace pinů pro RGB LED.
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {   // Kontrola, zda byl přijat signál z IR dálkového ovládání.
    unsigned long receivedValue = IrReceiver.decodedIRData.decodedRawData; // Získání přijaté hodnoty.
    Serial.println(receivedValue); // Výpis přijaté hodnoty na sériový monitor.
    
    for (int i = 0; i < 10; i++) { // Porovnání přijaté hodnoty s kódy čísel 0-9.
      if (receivedValue == codes[i])
        stringNum += String(i).c_str(); // Přidání čísla do řetězce.
    }
    
    if (receivedValue == IR_BUTTON_RED) { 
      int intNum = stringNum.toInt(); 
      stringNum = ""; // Vyprázdnění řetězce.
      if (intNum >= 0 && intNum <= 255) { 
        Serial.print("Zadaná hodnota: ");
        Serial.println(intNum); // Výpis hodnoty na sériový monitor.
        analogWrite(REDPIN, intNum); 
      } else {
        Serial.println("Zadané číslo není v daném rozsahu."); 
      }
    }

    if (receivedValue == IR_BUTTON_GREEN) { 
      int intNum = stringNum.toInt(); 
      stringNum = ""; // Vyprázdnění řetězce.
      if (intNum >= 0 && intNum <= 255) { 
        Serial.print("Zadaná hodnota: ");
        Serial.println(intNum); // Výpis hodnoty na sériový monitor.
        analogWrite(GREENPIN, intNum); 
      } else {
        Serial.println("Zadané číslo není v daném rozsahu."); 
      }
    }

    if (receivedValue == IR_BUTTON_BLUE) { 
      int intNum = stringNum.toInt(); 
      stringNum = ""; // Vyprázdnění řetězce.
      if (intNum >= 0 && intNum <= 255) { 
        Serial.print("Zadaná hodnota: ");
        Serial.println(intNum); // Výpis hodnoty na sériový monitor.
        analogWrite(BLUEPIN, intNum); 
      } else {
        Serial.println("Zadané číslo není v daném rozsahu."); 
      }
    }

    IrReceiver.resume(); // Povolí přijímání dalšího signálu.
  }
}
