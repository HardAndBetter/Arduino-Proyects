#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PLAYER_SIZE 10
#define ENEMY_SIZE 10
#define BULLET_SIZE 2
#define LEFT_BUTTON_PIN 2
#define RIGHT_BUTTON_PIN 3
#define SHOOT_BUTTON_PIN 4
#define BUZZER_PIN 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct Player {
  int x;
  int y;
};

struct Enemy {
  int x;
  int y;
  bool isActive;
};

struct Bullet {
  int x;
  int y;
  bool isActive;
};

Player player;
Enemy enemies[3];
Bullet bullets[3];

int score = 0;
int buzzerPin = BUZZER_PIN;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SHOOT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encuentra la pantalla OLED"));
    while (true);
  }

  player.x = SCREEN_WIDTH / 2 - PLAYER_SIZE / 2;
  player.y = SCREEN_HEIGHT - PLAYER_SIZE - 2;

  for (int i = 0; i < 3; i++) {
    enemies[i].isActive = false;
    bullets[i].isActive = false;
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  handleInput();
  updateGame();
  drawGame();
  delay(20);  // Ajusta la velocidad del juego según sea necesario
}

void handleInput() {
  int leftButtonState = digitalRead(LEFT_BUTTON_PIN);
  int rightButtonState = digitalRead(RIGHT_BUTTON_PIN);
  int shootButtonState = digitalRead(SHOOT_BUTTON_PIN);

  // Mover hacia la izquierda
  if (leftButtonState == LOW && player.x > 0) {
    player.x -= 2;
  }

  // Mover hacia la derecha
  if (rightButtonState == LOW && player.x < SCREEN_WIDTH - PLAYER_SIZE) {
    player.x += 2;
  }

  // Disparar
  if (shootButtonState == LOW) {
    for (int i = 0; i < 3; i++) {
      if (!bullets[i].isActive) {
        bullets[i].x = player.x + PLAYER_SIZE / 2 - BULLET_SIZE / 2;
        bullets[i].y = player.y - BULLET_SIZE;
        bullets[i].isActive = true;
        
        // Hacer sonar el buzzer suavemente (click)
        tone(buzzerPin, 1000, 50);
        delay(50); // Pequeña pausa para dar efecto
        noTone(buzzerPin);
        
        break;
      }
    }
  }
}

void updateGame() {
  // Actualizar posición de los enemigos
  for (int i = 0; i < 3; i++) {
    if (!enemies[i].isActive) {
      if (random(0, 100) < 2) {
        enemies[i].x = random(0, SCREEN_WIDTH - ENEMY_SIZE);
        enemies[i].y = 0;
        enemies[i].isActive = true;
      }
    } else {
      enemies[i].y += 2;

      // Verificar colisión con el jugador
      if (player.x < enemies[i].x + ENEMY_SIZE && player.x + PLAYER_SIZE > enemies[i].x &&
          player.y < enemies[i].y + ENEMY_SIZE && player.y + PLAYER_SIZE > enemies[i].y) {
        // Colisión, reiniciar el juego
        score = max(0, score - 1);
        player.y = SCREEN_HEIGHT - PLAYER_SIZE;
        for (int j = 0; j < 3; j++) {
          enemies[j].isActive = false;
          bullets[j].isActive = false;
        }
      }

      // Verificar si el enemigo ha pasado al jugador
      if (enemies[i].y > SCREEN_HEIGHT) {
        enemies[i].isActive = false;
        score = max(0, score - 1); // Restar puntos si el enemigo se escapa
      }
    }
  }

  // Actualizar posición de las balas
  for (int i = 0; i < 3; i++) {
    if (bullets[i].isActive) {
      bullets[i].y -= 4;

      // Verificar colisión con enemigos
      for (int j = 0; j < 3; j++) {
        if (enemies[j].isActive && bullets[i].x < enemies[j].x + ENEMY_SIZE &&
            bullets[i].x + BULLET_SIZE > enemies[j].x &&
            bullets[i].y < enemies[j].y + ENEMY_SIZE &&
            bullets[i].y + BULLET_SIZE > enemies[j].y) {
          // Enemigo derrotado
          enemies[j].isActive = false;
          bullets[i].isActive = false;
          score++;

          // Hacer sonar el buzzer con un sonido más dramático (PPPOOOOM)
          tone(buzzerPin, 800, 200);
          delay(200); // Pequeña pausa para dar efecto
          noTone(buzzerPin);
        }
      }

      // Verificar si la bala ha salido de la pantalla
      if (bullets[i].y < 0) {
        bullets[i].isActive = false;
      }
    }
  }
}

void drawGame() {
  display.clearDisplay();

  // Dibujar jugador
  display.fillRect(player.x, player.y, PLAYER_SIZE, PLAYER_SIZE, SSD1306_WHITE);

  // Dibujar enemigos si están activos
  for (int i = 0; i < 3; i++) {
    if (enemies[i].isActive) {
      display.fillRect(enemies[i].x, enemies[i].y, ENEMY_SIZE, ENEMY_SIZE, SSD1306_WHITE);
    }
  }

  // Dibujar balas si están activas
  for (int i = 0; i < 3; i++) {
    if (bullets[i].isActive) {
      display.fillRect(bullets[i].x, bullets[i].y, BULLET_SIZE, BULLET_SIZE, SSD1306_WHITE);
    }
  }

  // Mostrar puntuación
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);

  display.display();
}
