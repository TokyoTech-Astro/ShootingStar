
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Wire.h>


#define servo_pin1 9  //D9-19
#define servo_pin2 10 //D10-18
#define servo_pin3 13 //SCK-17

#define  VRpin1 5 //A5-12
#define  VRpin2 6 //A6-13
#define  VRpin3 7 //A7-14

#define  RSWpin1 14 
#define  RSWpin2 15
#define  RSWpin3 16
#define  RSWpin4 17 
#define  RSWpin5 18

#define  ShotSWpin 4 //D4-24
#define  ShotLEDpin 5 //D3-23
#define  PowerSWpin 3 //D5-25


#define RGBLED_OUTPIN    2  // RGBLEDに出力するピン番号 D2-26
#define NUMRGBLED        8  // Arduinoにぶら下がっているRGBLEDの個数


Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, RGBLED_OUTPIN, NEO_RGB + NEO_KHZ800);// RGBLEDのライブラリを生成する(色指定はRGBの並びで行う、LEDの速度は800KHzとする)

Servo servo1;
Servo servo2;
Servo servo3;


///////////////////プロトタイプ宣言////////////////////

///// servo_function
//void alldetach(void);
//void allattach(void);
//void moveServo2(int angle1, int angle2, int angle3, long int delay_ms);
//
///// LED_function
//void fadestream(int);



//|||||||||||||||||||||||||||||||グローバル変数宣言|||||||||||||||||||||||||||||||||||||//
int pulse_now1;
int pulse_now2;
int pulse_now3;
int streamdelay = 200;
int ShootBrightness = 0;
int PowerBrightness = 1;
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//



/////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
 // Serial.println("Hello Computer");

  ///////////////////////////servo_init////////////////////////////////////////////////////////////////////////////
  servo1.attach(servo_pin1);
  servo2.attach(servo_pin2);
  servo3.attach(servo_pin3);

  pulse_now1 = servo1.readMicroseconds();
  pulse_now2 = servo2.readMicroseconds();
  pulse_now3 = servo3.readMicroseconds();
 // delay(1000);



  ////////////////////////////LED_init//////////////////////////////////////////////////////////////////////////

  RGBLED.begin() ;                   // ライブラリを初期化
  RGBLED.setBrightness(255) ;         // (0-255)
  for (int i = 0; i < 8; i++) {
    RGBLED.setPixelColor(i, 255, 255, 255) ;
  }
  RGBLED.show() ;                    // LEDにデータを送り出す

  /////////////////////////////IO_init//////////////////////////////////////////////////////////////////////////////

  pinMode(RSWpin1, INPUT_PULLUP);
  pinMode(RSWpin2, INPUT_PULLUP);
  pinMode(RSWpin3, INPUT_PULLUP);
  pinMode(RSWpin4, INPUT_PULLUP);
  pinMode(RSWpin5, INPUT_PULLUP);
  pinMode(ShotSWpin, INPUT_PULLUP);

  pinMode(ShotLEDpin, OUTPUT);
  pinMode(PowerSWpin, OUTPUT);

  //////////////////////////////スイッチ点灯///////////////////////////////////////////////////////////////////////

  analogWrite(ShotLEDpin, ShootBrightness);
  analogWrite(PowerSWpin, PowerBrightness);

  ////////////////////////////////I2C初期化/////////////////////////////////////////////////////////////////////////////




  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 // delay(1000);
  //  moveServo2(90, 20, 90, 4000);
  //  delay(1000); //フォーカシング

  for (int i = 0; i < 8; i++) {
    RGBLED.setPixelColor(i, 0, 0, 0) ;
  }
}



void loop()
{
  int RSW1 = 0;
  int RSW2 = 0;
  int RSW3 = 0;
  int RSW4 = 0;
  int RSW5 = 0;
  int ShotSW = 0;
  int PowerSW = 0;


  RSW1 = digitalRead(RSWpin1);
  RSW2 = digitalRead(RSWpin2);
  RSW3 = digitalRead(RSWpin3);
  RSW4 = digitalRead(RSWpin4);
  RSW5 = digitalRead(RSWpin5);

  ShotSW = digitalRead(ShotSWpin);
  //RSW2 = digitalRead(RSWpin2);

  if (ShotSW == 0) {
    for (int i = 0; i < 8; i++) {
      RGBLED.setPixelColor(i, 0, 0, 0) ;
    }
  }


  bailout:
  if (RSW1 == 0) { //manual
    if (ShotSW == 0) {
      alldetach();
      fadestream(streamdelay);
      allattach();
    }

    int servospeed = 300;
    //    servospeed = analogRead(VRpin3) * 5;
    double val1 =  (double)analogRead(VRpin1) / (double)5.6888 ;//red
    double val2 =  (double)analogRead(VRpin2) / (double)5.6888 ;//green
    double val3 =  (double)analogRead(VRpin3) / (double)5.6888 ;//blue
    //     moveServo2(val1, val2, val3, 500);

//    Serial.print("val1=");
//    Serial.print(val1);
//    Serial.print(" val2=");
//    Serial.print(val2);
//    Serial.print(" val3=");
//    Serial.println(val3);

    moveServo2(val1, val2, val3, servospeed); ////(base,arm,roll,speed)

    //      int angle1, angle2, angle3;
    //      if (val1 <= 90) {
    //        angle2 = val1 / 2;
    //        angle1 = val2;
    //        moveServo2(angle1, angle2, 0, 1000);
    //      } else if (val1 >= 90) {
    //        angle2 = val1 / 2 + 90;
    //        angle1 = -1 * val2;
    //        moveServo2(angle1, angle2, 0, 1000);
    //      }


  } else if (RSW2 == 0) { //remote

    int servospeed = 3000;
    int angle1, angle2, angle3;
    int incomingByte = 0;

    //    if (Serial.available() > 0) {
    //      incomingByte = Serial.read();
    //      // incomingByte = incomingByte - 0x30;
    //      int angle = incomingByte;
    //      Serial.println(angle);
    //      moveServo2(90, angle, 90, 2000);
    //    }


    if (Serial.available() > 0) {
      incomingByte = Serial.read();

      if (incomingByte == 0) {
        alldetach();
        fadestream(streamdelay);
        allattach();
      }

      if (incomingByte == 3) {
        while (Serial.available() < 3);
        angle1 = Serial.read();
        angle2 = Serial.read();
        angle3 = Serial.read();
        moveServo2(angle1, angle2, angle3, 2000);
      }

    }

    ///////////////////////////////////////////////////
    /*
      RSW3 = digitalRead(RSWpin3);
      if (RSW3 != 0) {
      goto bailout;
      }
      moveServo2(90, 90, 90, servospeed);

      alldetach();
      fadestream(streamdelay);
      allattach();
      RSW3 = digitalRead(RSWpin3);
      if (RSW3 != 0) {
      goto bailout;
      }

      moveServo2(20, 20, 20, servospeed);

      alldetach();
      fadestream(streamdelay);
      fadestream(streamdelay);
      // stream(datan,data);
      allattach();
      RSW3 = digitalRead(RSWpin3);
      if (RSW3 != 0) {
      goto bailout;
      }
      moveServo2(160, 160, 160, servospeed);

      alldetach();
      fadestream(streamdelay);

      //  stream(datan,data);
      allattach();
      RSW3 = digitalRead(RSWpin3);
      if (RSW3 != 0) {
      goto bailout;
      }
      //moveServo2(90,90,90,servospeed);
      //
      //alldetach();
      //fadestream(streamdelay);
      //allattach();

      //PCcontrol();

    */


  } else if (RSW3 == 0) { //auto
    {

      int servospeed;
      int intarval;
      servospeed = analogRead(VRpin3) * 5;
      intarval = analogRead(VRpin1) * 10;
      int randangle1 = random(10, 171);
      int randangle2 = random(10, 171);
      int randangle3 = random(10, 171);

      moveServo2(randangle1, randangle2, randangle3, servospeed);

      alldetach();
      fadestream(streamdelay);
      allattach();


      delay(intarval);
    }

  } else if (RSW4 == 0) { //focusing

    int servospeed = 300;
    double val1 =  (double)analogRead(VRpin1) / (double)5.6888 ;//red
    double val2 =  (double)analogRead(VRpin2) / (double)5.6888 ;//green
    double val3 =  (double)analogRead(VRpin3) / (double)5.6888 ;//blue
    moveServo2(val1, val2, val3, servospeed); ////(base,arm,roll,speed)


    alldetach();
    for (int i = 0; i < 8; i++) {
      RGBLED.setPixelColor(i, 255, 255, 255) ;
    }
    allattach();

  } else if (RSW5 == 0) { //setting

    {
      ShootBrightness =  analogRead(VRpin1) / 4 - 10;
      PowerBrightness =  analogRead(VRpin2) / 4 - 10;

      if (ShootBrightness < 0) {
        ShootBrightness = 0;
      }
      if (PowerBrightness < 0) {
        PowerBrightness = 0;
      }


      analogWrite(ShotLEDpin,  ShootBrightness);
      analogWrite(PowerSWpin, PowerBrightness);
    }

  }






  /////////////////////////////////////////////////////////////////////
  /*
    int servospeed = 3000;
    int streamdelay = 200;
    ///////////////////////////////////////////////////

    moveServo2(90, 90, 90, servospeed);

    alldetach();
    fadestream(streamdelay);
    allattach();

  */

}
