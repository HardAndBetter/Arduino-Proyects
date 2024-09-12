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

int currentSong = 0;
int currentNote = 0;
bool playing = false;

const int numSongs = 5;
const int songLengths[numSongs] = {11, 14, 8, 12, 10}; // Longitudes de las canciones

const int songs[numSongs][14][2] = {
  // Canción 1
  {
    {262, 200}, {294, 200}, {330, 200}, {262, 200}, {330, 200}, {349, 200}, {330, 400},
    {262, 200}, {294, 200}, {330, 200}, {262, 200}
  },
  // Canción 2
  {
    {392, 200}, {392, 200}, {440, 200}, {392, 200}, {523, 200}, {494, 200}, {440, 400},
    {392, 200}, {392, 200}, {440, 200}, {392, 200}, {523, 200}, {494, 200}, {440, 400}
  },
  // Canción 3
  {
    {330, 300}, {392, 300}, {440, 300}, {523, 300}, {587, 300}, {659, 300}, {740, 600},
    {740, 300}, {659, 300}, {587, 300}, {523, 300}, {440, 300}
  },
  // Canción 4
  {
    {262, 200}, {294, 200}, {330, 200}, {262, 200}, {330, 200}, {349, 200}, {330, 400},
    {262, 200}, {294, 200}, {330, 200}, {262, 200}, {330, 200}, {349, 200}, {330, 400}
  },
  // Canción 5
  {
    {392, 200}, {392, 200}, {440, 200}, {392, 200}, {523, 200}, {494, 200}, {440, 400},
    {392, 200}, {392, 200}, {440, 200}, {392, 200}
  }
};

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
  display.println("Cancion: ");
  display.println(currentSong + 1); // Mostrar la canción actual (empezando desde 1)
  display.display();
}

void loop() {
  // Cambiar canción hacia arriba
  if (digitalRead(BUTTON_TONE_UP) == LOW) {
    currentSong = (currentSong + 1) % numSongs;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Cancion: ");
    display.println(currentSong + 1);
    display.display();
    delay(200); // Debounce delay
  }

  // Cambiar canción hacia abajo
  if (digitalRead(BUTTON_TONE_DOWN) == LOW) {
    currentSong = (currentSong - 1 + numSongs) % numSongs;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Cancion: ");
    display.println(currentSong + 1);
    display.display();
    delay(200); // Debounce delay
  }

  // Iniciar o detener la reproducción de la canción
  if (digitalRead(BUTTON_PLAY_NOTE) == LOW) {
    if (!playing) {
      currentNote = 0;
      playing = true;
    } else {
      playing = false;
    }
    delay(200); // Debounce delay
  }

  // Reproducir la canción actual si está en modo de reproducción
  if (playing) {
    int frequency = songs[currentSong][currentNote][0];
    int duration = songs[currentSong][currentNote][1];
    tone(BUZZER_PIN, frequency, duration);
    delay(duration); // Esperar la duración de la nota
    noTone(BUZZER_PIN);
    currentNote = (currentNote + 1) % songLengths[currentSong];
  }
}
