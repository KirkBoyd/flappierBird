/* IMU LIBRARIES */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
/* RADIO LIBRARIES */
#include <SPI.h>
#include <RFM69.h>
/* OTHER LIBRARIES */
#include <Servo.h>
/* PINS */
#define D0 2 //digital pin 2 for D0 pin on radio
#define esc 3 //digital pin 3 for ESC
#define gate 4 //digital pin 4 for solenoid gate pin
#define rfm1 6 //digital pin 6 for RFM_1 pin on radio
#define rfm4 7 //digital pin 7 for RFM_4 pin on radio
#define rfm5 8 //digital pin 8 for RFM_5 pin on radio
#define rfm2 9 //digital pin 9 for RFM_2 pin on radio
#define nss 10 //digital pin 10 for S/NSS pin on radio
#define mosi 11 //digital pin 11 for I/MOSI pin on radio
#define miso 12 //digital pin 12 for O/MISO pin on radio
#define sck 13 //digital pin 13 for SCK pin on radio
#define srv1 15 //digital pin 15 for servo 1 header on PCB
#define srv2 14 //digital pin 14 for servo 2 header on PCB
#define hall1 17 //digital pin 17 for hall effect sensor 1
#define hall2 16 //digital pin 16 for hall effect sensor 2
#define sda 18 //digital pin 18 for SDA pin on IMU
#define scl 19 //digital pin 19 for SCL pin on IMU
#define ps0 20 //digital pin 20 for PS0 pin on IMU (likely won't be used)
#define ps1 21 //digital pin 21 for PS1 pin on IMU (likely won't be used)
#define INT 22 //digital pin 22 for int pin on IMU (likely won't be used)
#define adr 23 //digital pin 23 for adr pin on IMU (likely won't be used)
#define r 29 //digital pin 29 for R pin on radio
#define BNO055_SAMPLERATE_DELAY_MS (100) //delay used between fresh samples

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28); //I2C adress for IMU
Servo servo1;
Servo servo2;

int poop = 9;

void setup() {
  pinMode(hall1,INPUT);
//  pinMode(srv1,OUTPUT);
  servo1.attach(srv1);
  servo2.attach(srv2);
  servo1.write(90);
  servo2.write(90);

  if (!bno.begin()) {
    Serial.print("No BNO055 detected");
    while(1);
  }
  delay(1000);
  printTemp();
  displaySensorDetails();
  displaySensorStatus();
  bno.setExtCrystalUse(true);
}

void loop() {
  for (int i=0 ; i<=180 ; i++){
    servo2.write(i);
    delay(10);
  }
}
