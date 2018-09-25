
//int pulse_now1 = sv.readMicroseconds();
//int pulse_now1 = sv.readMicroseconds();
//int pulse_now1 = sv.readMicroseconds();


void allattach()
{
  servo1.attach(servo_pin1);
  servo2.attach(servo_pin2);
  servo3.attach(servo_pin3);
  servo1.writeMicroseconds(pulse_now1);
  servo2.writeMicroseconds(pulse_now2);
  servo3.writeMicroseconds(pulse_now3);

}

void alldetach()
{
  pulse_now1 = servo1.readMicroseconds();
  pulse_now2 = servo2.readMicroseconds();
  pulse_now3 = servo3.readMicroseconds();
  servo1.detach();
  servo2.detach();
  servo3.detach();


}

void moveServo_q(int angle1, int angle2, int angle3) {
  servo1.write(angle1);
  servo1.write(angle2);
  servo1.write(angle3);
}


void moveServo(int angle1, int angle2, int angle3, long int delay_ms)
{
  int pulse1 = map(angle1, 0, 180, 544, 2400);
  int pulse2 = map(angle2, 0, 180, 544, 2400);
  int pulse3 = map(angle3, 0, 180, 544, 2400);

  int pulse_t1 = servo1.readMicroseconds();
  int pulse_t2 = servo2.readMicroseconds();
  int pulse_t3 = servo3.readMicroseconds();

  if ( pulse1 > pulse_t1 ) {
    for ( int i = pulse_t1; i <= pulse1; i++ ) {
      servo1.writeMicroseconds(i);
      delayMicroseconds(delay_ms);
    }
  }
  else if ( pulse1 < pulse_t1 ) {
    for ( int i = pulse_t1; i >= pulse1; i-- ) {
      servo1.writeMicroseconds(i);
      delayMicroseconds(delay_ms);
    }
  }
  else {
    // do nothing
  }

  if ( pulse2 > pulse_t2 ) {
    for ( int i = pulse_t2; i <= pulse2; i++ ) {
      servo2.writeMicroseconds(i);
      delayMicroseconds(delay_ms);
    }
  }
  else if ( pulse2 < pulse_t2 ) {
    for ( int i = pulse_t2; i >= pulse2; i-- ) {
      servo2.writeMicroseconds(i);
      delayMicroseconds(delay_ms);
    }
  }
  else {
    // do nothing
  }

  if ( pulse3 > pulse_t3 ) {
    for ( int i = pulse_t3; i <= pulse3; i++ ) {
      servo3.writeMicroseconds(i);
      delayMicroseconds(delay_ms);
    }
  }
  else if ( pulse3 < pulse_t3 ) {
    for ( int i = pulse_t3; i >= pulse3; i-- ) {
      servo3.writeMicroseconds(i);
      delayMicroseconds(delay_ms);
    }
  }
  else {
    // do nothing
  }


}


void moveServo2(int angle1, int angle2, int angle3, long int delay_ms)
{
  int pulse1 = map(angle1, 0, 180, 544, 2400);
  int pulse2 = map(angle2, 0, 180, 544, 2400);
  int pulse3 = map(angle3, 0, 180, 544, 2400);

  int pulse_t1 = servo1.readMicroseconds();
  int pulse_t2 = servo2.readMicroseconds();
  int pulse_t3 = servo3.readMicroseconds();

  int count = 0;
  while ((pulse1 - pulse_t1 != 0) || (pulse2 - pulse_t2 != 0) || (pulse3 - pulse_t3 != 0)) {

    if ( pulse1 > pulse_t1 ) {
      pulse_t1++;
      servo1.writeMicroseconds(pulse_t1);

    }

    else if ( pulse1 < pulse_t1 ) {
      pulse_t1--;
      servo1.writeMicroseconds(pulse_t1);


    }
    else {
      // do nothing
    }

    if ( pulse2 > pulse_t2 ) {
      pulse_t2++;
      servo2.writeMicroseconds(pulse_t2);


    }
    else if ( pulse2 < pulse_t2 ) {
      pulse_t2--;
      servo2.writeMicroseconds(pulse_t2);


    }
    else {
      // do nothing
    }

    if ( pulse3 > pulse_t3 ) {
      pulse_t3++;
      servo3.writeMicroseconds(pulse_t3);


    }
    else if ( pulse3 < pulse_t3 ) {
      pulse_t3--;
      servo3.writeMicroseconds(pulse_t3);


    }
    else {
      // do nothing
    }
    count++;
    delayMicroseconds(delay_ms);

    if (count <= 10) {
      delayMicroseconds(delay_ms);
      delayMicroseconds(delay_ms);
    }
  }
}


void PCcontrol() {

    int incomingByte = 0;
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      incomingByte = incomingByte - 0x30;
      int angle = incomingByte * 20;
  Serial.println(angle);
        moveServo2(90, angle, 90, 2000);

    
  }
}


