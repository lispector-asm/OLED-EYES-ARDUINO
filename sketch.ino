#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SONAR_TRIGGER_LEFT 7
#define SONAR_ECHO_LEFT 6

#define SONAR_TRIGGER_RIGHT 5
#define SONAR_ECHO_RIGHT 4

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1

#define BUTTON_SAD 3
#define BUTTON_ANGRY 2

int distance_right, distance_left;
int eyeX = 64;
int eyeY = 32;

int i = 0;
int j = 0;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

void setup(){
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	pinMode(SONAR_ECHO_RIGHT, INPUT);
	pinMode(SONAR_TRIGGER_RIGHT, OUTPUT);
  pinMode(SONAR_ECHO_LEFT, INPUT);
  pinMode(SONAR_TRIGGER_LEFT, OUTPUT);
  pinMode(BUTTON_SAD, INPUT);
  pinMode(BUTTON_ANGRY, INPUT);
  Serial.begin(9600);
}

void loop(){
  int buttonAngryState = digitalRead(BUTTON_ANGRY);
  int buttonSadState = digitalRead(BUTTON_SAD);
  distance_left = getSonarDist(SONAR_TRIGGER_LEFT, SONAR_ECHO_LEFT);
  distance_right = getSonarDist(SONAR_TRIGGER_RIGHT, SONAR_ECHO_RIGHT);
  updateEyePosition(distance_left, distance_right);
  if (i >= 25) {
    blinkEyes();
    i = 0;
  } else if (buttonAngryState == HIGH) {
    angryEyes();
  } else if (buttonSadState == HIGH) {
    sadEyes();
  } else if (j >= 50) {
    happyEyes();
    if (j >= 75) {
      j = 0;
    }
  } else {
    neutralEyes();
  }
  j++;
  i++;
  delay(50);
}

void updateEyePosition(long dist1, long dist2) {

  dist1 = constrain(dist1, 5, 100);
  dist2 = constrain(dist2, 5, 100);

  int offset = map(abs(dist1 - dist2), 0, 100, 0, 20);

  if (dist1 > dist2) {
    eyeX =  min(OLED_WIDTH - 30, 64 + offset);
  } else {
    eyeX = max(40, 64 - offset);
  }
}

void blinkEyes() {
  // linha para simular piscar
  display.clearDisplay();
  display.drawLine(eyeX - 30, eyeY, eyeX - 5, eyeY, WHITE);
  display.drawLine(eyeX + 5, eyeY, eyeX + 30, eyeY, WHITE);
  display.display();
  delay(100);
}

void neutralEyes() {
  display.clearDisplay();
  
  // parâmetros: x, y, largura, altura, raio do canto dos dois olhos
  display.fillRoundRect(eyeX - 30, eyeY - 15, 25, 30, 5, WHITE);
  display.fillRoundRect(eyeX + 5, eyeY - 15, 25, 30, 5, WHITE);
  
  display.display();
}

void angryEyes() {
  display.clearDisplay();

  display.fillRoundRect(eyeX - 30, eyeY - 15, 25, 30, 5, WHITE);
  display.fillRoundRect(eyeX + 5, eyeY - 15, 25, 30, 5, WHITE);

    display.fillTriangle(
    eyeX - 30, eyeY - 15,          // vértice esquerda-cima do olho
    eyeX - 5, eyeY - 15,           // direita-cima
    eyeX - 5, eyeY + 5,           // meio do lado
    BLACK
  );


  display.fillTriangle(
    eyeX + 30, eyeY - 15,
    eyeX + 5, eyeY - 15,        
    eyeX + 5, eyeY + 5,
    BLACK
  );

  display.display();
}

void happyEyes() {
  display.clearDisplay();
  
  display.drawRoundRect(eyeX - 30, eyeY - 15, 25, 30, 10, WHITE);
  display.drawRoundRect(eyeX + 5, eyeY - 15, 25, 30, 10, WHITE);

  display.fillRect(0, 38, 128, 32, BLACK);

  display.display();
}

void sadEyes() {
  display.clearDisplay();

  // parâmetros: x, y, largura, altura, raio do canto dos dois olhos
  display.fillRoundRect(eyeX - 30, eyeY - 15, 25, 30, 5, WHITE);
  display.fillRoundRect(eyeX + 5, eyeY - 15, 25, 30, 5, WHITE);

    display.fillTriangle(
    eyeX - 30, eyeY - 15,          // vértice esquerda-cima do olho
    eyeX - 5, eyeY - 15,           // direita-cima
    eyeX - 30, eyeY - 5,           // meio do lado
    BLACK
  );


  display.fillTriangle(
    eyeX + 5, eyeY - 15,
    eyeX + 30, eyeY - 15,        
    eyeX + 30, eyeY - 5,
    BLACK
  );

  display.display();
}


long getSonarDist(int trigPin, int echoPin) {
    long distance;
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    distance = pulseIn(echoPin, HIGH)/58.2;

    return distance;
}