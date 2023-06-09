#include <Adafruit_BNO055.h>
#include <Arduino.h>
#include <LIDARLite_v3HP.h>
#include <Servo.h>
#include <SparkFun_TB6612.h>
#include <Wire.h>

#ifndef MONITOR_SPEED
#define MONITOR_SPEED 115200
#endif

#define FAST_I2C

Servo servo;
Motor fl(7, 8, 6, 1, 9), fr(2, 4, 5, 1, 9);
Motor bl(10, 14, 3, 1, 15), br(13, 12, 11, 1, 15);
LIDARLite_v3HP lidar_lite;
Adafruit_BNO055 bno(12, 0x28, &Wire);

void setup() {
  Serial.begin(MONITOR_SPEED);
  while (servo.attach(22) == INVALID_SERVO) {
    Serial.println("Invalid Servo on pin 22");
    delay(500);
  }
  Wire.begin();
#ifdef FAST_I2C
#if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz (for Arduino Due)
#else
  TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
#endif
#endif
  lidar_lite.configure(0);

  while (!bno.begin()) {
    Serial.println(
        "Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    delay(500);
  }
}

void loop() {}
