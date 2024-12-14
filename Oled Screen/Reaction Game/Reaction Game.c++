#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2; // Pin del botón
const int buzzerPin = 3; // Pin del buzzer
bool gameActive = false;
unsigned long startTime;
unsigned long reactionTime;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error al iniciar la pantalla OLED"));
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  if (!gameActive) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Espera...");
    display.display();
    delay(random(1000, 5000)); // Espera aleatoria entre 1 y 5 segundos
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Toca!");
    display.display();
    startTime = millis();
    gameActive = true;
  }

  if (digitalRead(buttonPin) == LOW && gameActive) {
    reactionTime = millis() - startTime;
    if (reactionTime <= 0) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Percance");
      display.display();
      tone(buzzerPin, 500, 1000); // Buzzer suena durante 1 segundo
      delay(1000);
      noTone(buzzerPin);
      gameActive = false;
      delay(3000); // Espera 3 segundos antes de reiniciar
    }
    else {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Tardaste: ");
      display.print(reactionTime);
      display.println(" ms");
      display.display();
      tone(buzzerPin, 1000, 100); // Hacer sonar el buzzer durante 100ms
      delay(100);
      noTone(buzzerPin);
      delay(3900); // Espera 4 segundos antes de volver al estado inicial
      gameActive = false;
    }
  }
}
