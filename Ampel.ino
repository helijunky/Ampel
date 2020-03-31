/*
 Ampelsteuerung mit Arduino

 Manuel Haag
 März 2020
 
*/

// Definition der Ein- und Ausgänge
#define LED_AUTO_ROT 9
#define LED_AUTO_GELB 8
#define LED_AUTO_GRUEN 7

#define LED_FUSSG_ROT 6
#define LED_FUSSG_GELB 5
#define LED_FUSSG_GRUEN 4

#define LED_KNOPF 3
#define KNOPF 2

// Definition der Variablen
bool blinken = true;
volatile bool gedrueckt = false;


// die setup Funktion wird beim Start einmal ausgeführt
void setup() {
  Serial.begin(9600); // zum Debuggen

  // alle LEDs werden als Ausgang definiert
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_AUTO_ROT, OUTPUT);
  pinMode(LED_AUTO_GELB, OUTPUT);
  pinMode(LED_AUTO_GRUEN, OUTPUT);
  pinMode(LED_FUSSG_ROT, OUTPUT);
  pinMode(LED_FUSSG_GELB, OUTPUT);
  pinMode(LED_FUSSG_GRUEN, OUTPUT);
  pinMode(LED_KNOPF, OUTPUT);

  // der Knopf wird als Eingang definiert
  pinMode(KNOPF, INPUT_PULLUP);

  // sobald der Knopf gedrückt wird, wird die Funktion "druecken" aufgerufen (Interrupt-Funktion)
  attachInterrupt(digitalPinToInterrupt(KNOPF), druecken, FALLING);

  // zum Testen werden alle LEDs kurz eingeschaltet
  digitalWrite(LED_AUTO_ROT, HIGH);
  digitalWrite(LED_AUTO_GELB, HIGH);
  digitalWrite(LED_AUTO_GRUEN, HIGH);
  digitalWrite(LED_FUSSG_ROT, HIGH);
  digitalWrite(LED_FUSSG_GELB, HIGH);
  digitalWrite(LED_FUSSG_GRUEN, HIGH);
  digitalWrite(LED_KNOPF, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);

  // und wieder ausgeschaltet
  digitalWrite(LED_AUTO_ROT, LOW);
  digitalWrite(LED_AUTO_GELB, LOW);
  digitalWrite(LED_AUTO_GRUEN, LOW);
  digitalWrite(LED_FUSSG_ROT, LOW);
  digitalWrite(LED_FUSSG_GELB, LOW);
  digitalWrite(LED_FUSSG_GRUEN, LOW);
  digitalWrite(LED_KNOPF, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  gedrueckt = false;  // erster Knopfdruck löschen (Interrupt wird bei jedem Start einmal ausgeführt)
}


// Interrupt-Funktion wird aufgerufen, sobald der Knopf gedrückt wird
void druecken() {
  Serial.println("Knopf gedrückt");   // zum Debuggen
  if (!gedrueckt) {
    gedrueckt = true;                 // merken, dass Knopf gedrückt wurde
    digitalWrite(LED_KNOPF, HIGH);    // die LED im Knopf einschalten
    digitalWrite(LED_BUILTIN, HIGH);  // die kleine LED auf dem Arduino einschalten
  }
}


// die loop Funktion wird immer wieder ausgeführt
void loop() {
  
  // Blinken der orangen LEDs
  if (blinken) {                        // wenn Blinken aktiv ist (nach dem Einschalten)
    digitalWrite(LED_AUTO_GELB, HIGH);  // gelbe LED für Auto einschalten
    digitalWrite(LED_FUSSG_GELB, HIGH); // gelbe LED für Fussgänger einschalten
    digitalWrite(LED_BUILTIN, HIGH);    // kleine LED auf dem Arduino einschalten
    delay(750);                         // 750 Millisekunden warten
    digitalWrite(LED_AUTO_GELB, LOW);   // gelbe LED für Auto ausschalten
    digitalWrite(LED_FUSSG_GELB, LOW);  // gelbe LED für Fussgänger ausschalten
    digitalWrite(LED_BUILTIN, LOW);     // kleine LED auf dem Arduino ausschalten
    delay(750);                         // 750 Millisekunden warten
  }

  if (gedrueckt) {                      // wenn gedrückt wurde
    if (blinken) {                      // wenn noch Blinken aktiv ist (nach dem Einschalten)
      blinken = false;                  // Blinken ausschalten
      
      // Fussgänger Ampel auf Orange stellen
      digitalWrite(LED_FUSSG_ROT, LOW);
      digitalWrite(LED_FUSSG_GELB, HIGH);
      digitalWrite(LED_FUSSG_GRUEN, LOW);
    }
    
    // Auto Ampel auf Orange stellen
    digitalWrite(LED_AUTO_ROT, LOW);
    digitalWrite(LED_AUTO_GELB, HIGH);
    digitalWrite(LED_AUTO_GRUEN, LOW);
    delay(4000);                        // 4 Sekunden warten

    // Auto Ampel auf Rot stellen
    digitalWrite(LED_AUTO_ROT, HIGH);
    digitalWrite(LED_AUTO_GELB, LOW);
    digitalWrite(LED_AUTO_GRUEN, LOW);

    // Fussgänger Ampel auf Rot stellen
    digitalWrite(LED_FUSSG_ROT, HIGH);
    digitalWrite(LED_FUSSG_GELB, LOW);
    digitalWrite(LED_FUSSG_GRUEN, LOW);
    delay(4000);                        // 4 Sekunden warten

    // Fussgänger Ampel auf Grün stellen
    digitalWrite(LED_FUSSG_ROT, LOW);
    digitalWrite(LED_FUSSG_GELB, LOW);
    digitalWrite(LED_FUSSG_GRUEN, HIGH);
    digitalWrite(LED_KNOPF, LOW);       // LED im Knopf ausschalten
    digitalWrite(LED_BUILTIN, LOW);     // kleine LED ausschalten
    delay(10000);                       // 10 Sekunden warten

    // Fussgänger Ampel auf Orange stellen
    digitalWrite(LED_FUSSG_ROT, LOW);
    digitalWrite(LED_FUSSG_GELB, HIGH);
    digitalWrite(LED_FUSSG_GRUEN, LOW);
    delay(4000);                        // 4 Sekunden warten

    // Fussgänger Ampel auf Rot stellen
    digitalWrite(LED_FUSSG_ROT, HIGH);
    digitalWrite(LED_FUSSG_GELB, LOW);
    digitalWrite(LED_FUSSG_GRUEN, LOW);
    gedrueckt = false;                  // ab jetzt kann man wieder drücken
    delay(2000);                        // 2 Sekunden warten

    // Auto Ampel auf Rot+Orange stellen
    digitalWrite(LED_AUTO_ROT, HIGH);
    digitalWrite(LED_AUTO_GELB, HIGH);
    digitalWrite(LED_AUTO_GRUEN, LOW);
    delay(2000);                        // 2 Sekunden warten

    // Auto Ampel auf Grün stellen
    digitalWrite(LED_AUTO_ROT, LOW);
    digitalWrite(LED_AUTO_GELB, LOW);
    digitalWrite(LED_AUTO_GRUEN, HIGH);
    delay(12000);                       // 12 Sekunden warten
  }
  
}
