/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep


  Arranged by Masahiro Furukawa
  Feb 2, 2021
*/

#include <Servo.h>
// https://github.com/arduino-libraries/Servo

Servo myservo;  // create servo object to control a servo

/*
  Kst X08 V5.0
  1.working電圧: DC3.8-8.4V
  2.installationサイズ: 23.5*8*16.8ミリメートル
  3.workingトルク: 2.8キロ。cm-8.4V; 2.2キロ。cm-6.0V; 1.4キロ。cm-3.8V
  4。を最大速度: 0.18秒/60 degree-4.2V; 0.15秒/60 degree-6.0V 0.09秒/60 degree-8.4V
  5.weight: 8グラム
  6.working周波数: 1520us/333hz、900us-2100us
  7.motorタイプ: 7.0ミリメートル中空カップモーター、ダブルベアリング。

  Kst X08H V5.0
  動作電圧: DS3.8V-8.4V
  サイズ: 23.5*8*16.6ミリメートル
  トルク:
  2.8kg.cm 8.4 12v
  2.2kg.cm 6.0 12v
  1.4kg.cm 3.8 12v
  速度:

  0。09sec/60度8.4v
  0。秒/60度6.0v
  0。18sec/60度4.2v
  重量: 8グラム
  動作周波数: 1520us/333hz、900us-2100us
  モーター: 7ミリメートルコアレスモーター
  ボールベアリング: 2BB

  パッケージ付属:

  1 kst X08
  1 kst X08H
*/

// m-sequence
// https://okasho-engineer.com/m-sequence/
int pos = 0;    // variable to store the servo position

// m-series definition
class Mseries {
  private:
#define   MSeries_N   16
    uint8_t M[MSeries_N];
    uint8_t H[MSeries_N];

  public:
    Mseries() {

      // the following initial values are not validated
      M[0] = 0;
      M[1] = 0;
      M[2] = 0;
      M[3] = 1;
      M[4] = 0;
      M[5] = 0;
      M[6] = 0;
      M[7] = 1;
      M[8] = 0;
      M[9] = 0;
      M[10] = 0;
      M[11] = 1;
      M[12] = 0;
      M[13] = 0;
      M[14] = 0;
      M[15] = 1;

      // the following initial values are not validated
      H[0] = 1;
      H[1] = 0;
      H[2] = 0;
      H[3] = 1;
      H[4] = 1;
      H[5] = 0;
      H[6] = 0;
      H[7] = 1;
      H[8] = 1;
      H[9] = 0;
      H[10] = 0;
      H[11] = 1;
      H[12] = 1;
      H[13] = 0;
      H[14] = 0;
      H[15] = 1;
    }

    uint8_t update(void)
    {
      // update M-series
      uint8_t Mtmp = M[0] * H[0];

      // one left-shifting on ring buffer
      M[0] = M[1];

      // take sequential XOR on the entire sequence
      for (int i = 1 ; i < MSeries_N - 1 ; i++) {
        // XOR
        Mtmp = (Mtmp + M[i] * H[i]) % 2;

        // one left-shifting on ring buffer
        M[i] = M[i + 1];
      }

      // store the latest value at the last
      M[MSeries_N - 1] = Mtmp;

      return Mtmp;
    }
};


int max_uSec = 2100;
int min_uSec = 900;
//int max_pos = 120;
//int min_pos = 0;

Mseries m;

void setup()
{
  myservo.attach(3, min_uSec, max_uSec);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (m.update()) {
    myservo.writeMicroseconds(min_uSec);  // set servo to minimum point
    //  myservo.write(max_pos);              // tell servo to go to position in variable 'pos'

  } else {
    myservo.writeMicroseconds(max_uSec);  // set servo to maximum point
    //  myservo.write(min_pos);
    // tell servo to go to position in variable 'pos'
  }
  delay(500);                       // waits 500ms for the servo to reach the position

}

#if 0

int max_pos = 180;
int min_pos = 10;


void loop() {
  for (pos = min_pos; pos <= max_pos; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  for (pos = max_pos; pos >= min_pos; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
}

#endif
