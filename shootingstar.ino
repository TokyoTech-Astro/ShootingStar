#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Wire.h>

#define SERVO_PIN0 9  //D9-19
#define SERVO_PIN1 10 //D10-18
#define SERVO_PIN2 13 //SCK-17

#define LED_PIN 2  // RGBLEDに出力するピン番号 D2-26
#define NUMRGBLED 8  // Arduinoにぶら下がっているRGBLEDの個数

// milisecond
#define SERVO_SPEED 50

// RGBLEDのライブラリを生成する(色指定はRGBの並びで行う、LEDの速度は800KHzとする)
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, LED_PIN, NEO_RGB + NEO_KHZ800);

Servo servos[3];

// Global Vars
int currentPulses[3];
int streamDelay = 200;
int shootBrightness = 0;
int powerBrightness = 1;
int servoPins[] = {SERVO_PIN0, SERVO_PIN1, SERVO_pin2};

int getInterval() {
    return 10000;
}

void setup() {
    int i;
    Serial.begin(115200);

    // init servos
    for (i=0;i<3;i++) {
        servos[i].attach(servoPins[i]);
        currentPulses[i] = servos[i].readMicroseconds();
    }

    // init led
    RGBLED.begin();
}

void loop() {
    int i;
    int angle[3];
    for(i=0;i<3;i++) angle[i] = random(10,171);
    moveServo2(angle[0], angle[1], angle[2], SERVO_SPEED);

    allDetach();
    fadeStream(streamDelay);
    allAttach();

    delay(getInterval());
}
