#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BUTTON_TONE_UP 2
#define BUTTON_TONE_DOWN 3
#define BUTTON_PLAY_NOTE 4
#define BUZZER_PIN 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int currentTone = 0;
const int numTones = 10; // Número total de tonos
const int tones[numTones] = {262, 294, 330, 349, 392, 440, 49
                                                  , 523, 587, 659}; // Frecuencias de los tonos en Hz

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_TONE_UP, INPUT_PULLUP);
  pinMode(BUTTON_TONE_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_PLAY_NOTE, INPUT_PULLUP);
  
  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encuentra la pantalla OLED"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Tono: ");
  display.println(currentTone + 1); // Mostrar el tono actual (empezando desde 1)
  display.display();
}

void loop() {
  // Cambiar tono hacia arriba
  if (digitalRead(BUTTON_TONE_UP) == LOW) {
    currentTone = (currentTone + 1) % numTones;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Tono: ");
    display.println(currentTone + 1);
    display.display();
    delay(200); // Debounce delay
  }

  // Cambiar tono hacia abajo
  if (digitalRead(BUTTON_TONE_DOWN) == LOW) {
    currentTone = (currentTone - 1 + numTones) % numTones;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Tono: ");
    display.println(currentTone + 1);
    display.display();
    delay(200); // Debounce delay
  }

  // Tocar nota
  if (digitalRead(BUTTON_PLAY_NOTE) == LOW) {
    tone(BUZZER_PIN, tones[currentTone]);
    delay(500); // Duración de la nota
    noTone(BUZZER_PIN);
    delay(200); // Debounce delay
  }
}
