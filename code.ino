#include <JC_Button.h>
#include <Adafruit_NeoPixel.h>

int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;

int threshold = 1;

int solenoidPin = 10;

//Button buttons[] = { { 8 }, { 9 }, { 10 }, { 11 } };

const uint8_t ledsCount = 24;

Adafruit_NeoPixel rings[] = {
  {
    ledsCount,
    7,
    NEO_GRB + NEO_KHZ800
  },
  {
    ledsCount,
    6,
    NEO_GRB + NEO_KHZ800
  },
  {
    ledsCount,
    5,
    NEO_GRB + NEO_KHZ800
  },
  {
    ledsCount,
    4,
    NEO_GRB + NEO_KHZ800
  },
};

uint8_t randomRing() {
  static uint8_t id = UINT8_MAX;
  const uint8_t old = id;

  // if needed, turn previous ring off
  if (old != UINT8_MAX) {
    for (uint8_t i = 0; i < ledsCount; ++i) {
      rings[old].setPixelColor(i, 0, 0, 0);
    }
    rings[old].show();
  }

  // choose new ring
  while (old == id) {
    id = random(0, 4);
  }

  // turn new ring on
  for (uint8_t i = 0; i < ledsCount; ++i) {
    rings[id].setPixelColor(i, 0, 160, 200);
  }
  rings[id].show();

  return id;
}

void setup() {
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW);
  Serial.begin(9600);
  Serial.println("Whack-a-LED started");
  randomSeed(analogRead(A0));

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  for (uint8_t i = 0; i < 4; ++i) {
    //buttons[i].begin();

    rings[i].begin();
    rings[i].show();
  }

}

void loop() {
  const uint32_t now = millis();
  static uint32_t past = now;
  static uint32_t interval = 1000;
  static bool hit = true;
  static uint8_t id;
  if (now - past >= interval) {
    past = now;
    hit = false;
    id = randomRing();
    //digitalWrite(solenoidPin, LOW);
  }

  if (hit == false) {
    //buttons[id].read();
    int sensorVal1 = analogRead(sensor1);
    int sensorVal2 = analogRead(sensor2);
    int sensorVal3 = analogRead(sensor3);
    int sensorVal4 = analogRead(sensor4);
    digitalWrite(solenoidPin, LOW);

    Serial.println(sensorVal4);

    if (sensorVal1 > threshold && id == 0) {
      hit = true;
      digitalWrite(solenoidPin, HIGH);
      delay(200);
      digitalWrite(solenoidPin, LOW);
      delay(1000);

    }

    if (sensorVal2 > threshold && id == 1) {
      hit = true;
      digitalWrite(solenoidPin, HIGH);
      delay(200);
      digitalWrite(solenoidPin, LOW);
      delay(1000);

    }

    if (sensorVal3 > threshold && id == 2) {
      hit = true;
      digitalWrite(solenoidPin, HIGH);
      delay(200);
      digitalWrite(solenoidPin, LOW);
      delay(1000);

    }

    if (sensorVal4 > threshold && id == 3) {
      hit = true;
      digitalWrite(solenoidPin, HIGH);
      delay(200);
      digitalWrite(solenoidPin, LOW);
      delay(1000);

    }
  }
}
