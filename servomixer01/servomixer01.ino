#include <Servo.h>

Servo ESC1;
Servo ESC2;

volatile long pwm;
volatile boolean done;
unsigned long start;

volatile long pwm2;
volatile boolean done2;
unsigned long start2;

int diff;
int out1;
int out2;

unsigned long currentMillis;

long previousMillis = 0;    // set up timers
long interval = 20;        // time constant for timers

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, timeit, CHANGE);
  attachInterrupt(1, timeit2, CHANGE);

  ESC1.attach(7);
  ESC2.attach(8);
     
  Serial.begin(115200);

}


void timeit() {
    if (digitalRead(2) == HIGH) {
      start = micros();
    }
    else {
      pwm = micros() - start;
      done = true;
    }
  }

void timeit2() {
    if (digitalRead(3) == HIGH) {
      start2 = micros();
    }
    else {
      pwm2 = micros() - start2;
      done2 = true;
    }
  }



void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {  //start timed event
      previousMillis = currentMillis;

      Serial.print (pwm);
      Serial.print (" , ");
      Serial.print (pwm2);
      Serial.print (" , ");
      Serial.print (diff);
      Serial.print (" ******* ");
      Serial.print (out1);
      Serial.print (" , ");
      Serial.println (out2);

      diff = 1500-pwm;

      out1 = pwm2+diff;
      out2 = pwm-diff;

      ESC1.write(out1);
      ESC2.write(out2);
      
      if (!done)
          return;                     
          done = false;  

      if (!done2)
          return;                         
          done2 = false;


  } // end of timed event

}



