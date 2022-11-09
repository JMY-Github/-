#include <Servo.h>

// Arduino pin assignment
#define PIN_LED 9
#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)
#define _DUTY_RANGE 1846
#define dist_max 250.0
#define dist_min 100.0
#define _EMA_ALPHA 0.5

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

Servo myservo;
unsigned long last_loop_time;   // unit: msec
double dist;
float dist_ema;
float dist_prev;

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED,OUTPUT);
  
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Read IR Sensor value !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  // Convert IR sensor value into distance !!!
  dist = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  // we need distance range filter here !!!
  if (dist>dist_max){
    dist = dist_prev;
    digitalWrite(PIN_LED, 1);
  }
  else if (dist<dist_min){
    dist = dist_prev;
    digitalWrite(PIN_LED, 1);
  }
  else{
    dist_prev = dist;
    digitalWrite(PIN_LED, 0);
  }
  // we need EMA filter here !!!
  dist_ema = dist*_EMA_ALPHA + dist_ema*(1.0-_EMA_ALPHA);

  // map distance into duty
  duty = (dist-100.0)*_DUTY_RANGE/150.0 + 553.0;

  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN: "); Serial.print(dist_min);
  Serial.print(", IR: "); Serial.print(a_value);
  Serial.print(", dist: "); Serial.print(dist);
  Serial.print(", ema: "); Serial.print(dist_ema);
  Serial.print(", servo: "); Serial.print(duty);
  Serial.print(", MAX: "); Serial.print(dist_max);
  Serial.println("");
}