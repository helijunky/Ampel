/*
 Ampel
 
*/

#define LED_ROT_A 9
#define LED_GELB_A 8
#define LED_GRUEN_A 7

#define LED_ROT_F 6
#define LED_GELB_F 5
#define LED_GRUEN_F 4

#define LED_KNOPF 3
#define KNOPF 2

bool blinken = true;
volatile bool gedrueckt = false;
unsigned long zeit = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_ROT_A, OUTPUT);
  pinMode(LED_GELB_A, OUTPUT);
  pinMode(LED_GRUEN_A, OUTPUT);
  pinMode(LED_ROT_F, OUTPUT);
  pinMode(LED_GELB_F, OUTPUT);
  pinMode(LED_GRUEN_F, OUTPUT);
  pinMode(LED_KNOPF, OUTPUT);
  pinMode(KNOPF, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(KNOPF), druecken, FALLING);

  // LED Test
  digitalWrite(LED_ROT_A, HIGH);
  digitalWrite(LED_GELB_A, HIGH);
  digitalWrite(LED_GRUEN_A, HIGH);
  digitalWrite(LED_ROT_F, HIGH);
  digitalWrite(LED_GELB_F, HIGH);
  digitalWrite(LED_GRUEN_F, HIGH);
  digitalWrite(LED_KNOPF, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  
  digitalWrite(LED_ROT_A, LOW);
  digitalWrite(LED_GELB_A, LOW);
  digitalWrite(LED_GRUEN_A, LOW);
  digitalWrite(LED_ROT_F, LOW);
  digitalWrite(LED_GELB_F, LOW);
  digitalWrite(LED_GRUEN_F, LOW);
  digitalWrite(LED_KNOPF, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  gedrueckt = false;  // erster Knopfdruck löschen (Interrupt wird bei jedem Start einmal ausgeführt)
}

void druecken() {
  Serial.println("Knopf gedrückt");
  if (!gedrueckt) {
    gedrueckt = true;
    digitalWrite(LED_KNOPF, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

// the loop function runs over and over again forever
void loop() {
  if (blinken) {
    digitalWrite(LED_GELB_A, HIGH);
    digitalWrite(LED_GELB_F, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(750);
    digitalWrite(LED_GELB_A, LOW);
    digitalWrite(LED_GELB_F, LOW);
    if (!gedrueckt) {
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(750);
  }

  if (gedrueckt && millis() > zeit) {
    if (blinken) {
      blinken = false;
      // Fussgänger Orange (nur beim ersten mal)
      digitalWrite(LED_GELB_F, HIGH);
    }
    // Auto Orange
    digitalWrite(LED_ROT_A, LOW);
    digitalWrite(LED_GELB_A, HIGH);
    digitalWrite(LED_GRUEN_A, LOW);
    delay(4000);

    // Auto und Fussgänger Rot
    digitalWrite(LED_ROT_A, HIGH);
    digitalWrite(LED_GELB_A, LOW);
    digitalWrite(LED_GRUEN_A, LOW);
    digitalWrite(LED_ROT_F, HIGH);
    digitalWrite(LED_GELB_F, LOW);
    digitalWrite(LED_GRUEN_F, LOW);
    delay(4000);

    // Fussgänger Grün
    digitalWrite(LED_ROT_F, LOW);
    digitalWrite(LED_GELB_F, LOW);
    digitalWrite(LED_GRUEN_F, HIGH);
    digitalWrite(LED_KNOPF, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(10000);

    // Fussgänger Orange
    digitalWrite(LED_ROT_F, LOW);
    digitalWrite(LED_GELB_F, HIGH);
    digitalWrite(LED_GRUEN_F, LOW);
    delay(4000);

    // Fussgänger Rot
    digitalWrite(LED_ROT_F, HIGH);
    digitalWrite(LED_GELB_F, LOW);
    digitalWrite(LED_GRUEN_F, LOW);
    gedrueckt = false; // ab jetzt kann man wieder drücken
    delay(2000);

    // Auto Rot+Orange
    digitalWrite(LED_ROT_A, HIGH);
    digitalWrite(LED_GELB_A, HIGH);
    digitalWrite(LED_GRUEN_A, LOW);
    delay(2000);

    // Auto Grün
    digitalWrite(LED_ROT_A, LOW);
    digitalWrite(LED_GELB_A, LOW);
    digitalWrite(LED_GRUEN_A, HIGH);

    // nächste Fussgängerphase frühestens in 15 Sekunden
    zeit = millis() + 12000;
  }
  
}
