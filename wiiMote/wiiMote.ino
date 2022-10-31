/**************************************************
 * Robomote - Flappier Bird
 * Teensy 4.0 
 * Kirk Boyd
 * 10/24/2022
 *************************************************/
 /* LCD Libraries */
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //best functioning I2C library I could find which works with Teensy and the LCD I had lying around
//* RADIO LIBRARIES */
#include <SPI.h>
#include <RFM69.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/*VARIABLES*/
//Radio
#define rfm1 6 //digital pin 6 for RFM_1 pin on radio
#define rfm4 7 //digital pin 7 for RFM_4 pin on radio
#define rfm5 8 //digital pin 8 for RFM_5 pin on radio
#define rfm2 9 //digital pin 9 for RFM_2 pin on radio
#define nss 10 //digital pin 10 for S/NSS pin on radio
#define mosi 11 //digital pin 11 for I/MOSI pin on radio
#define miso 12 //digital pin 12 for O/MISO pin on radio
#define sck 13 //digital pin 13 for SCK pin on radio

//Joystick A
#define joyAx A2
#define joyAy A1
#define joyAz A3
#define joyTrigA 3 //digital pin 3

//Joystick B
#define joyBx A7
#define joyBy A8
#define joyBz A9
#define joyTrigB 4 //2 //digital pin 2

//LCD
#define lcdSCL A5 // Teensy Pin 4.0 #19 //Brown
#define lcdSDA A6 // Teensy Pin 4.0 #18 //Orange

/*OBJECTS*/
LiquidCrystal_I2C lcd(0x27,16,2);

/************** Radio Setup ***********/
// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     10   // Must be the same for all nodes
#define MYNODEID      96   // My node ID
#define TONODEID      69   // Destination node ID
#define FREQUENCY     RF69_915MHZ // RFM69 frequency 
// AES encryption (or not):
#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes
#define USEACK        false //true //false // Request ACKs (or not)
#define LED           9 // LED positive pin // Packet sent/received indicator LED (optional)
#define GND           8 // LED ground pin // Packet sent/received indicator LED (optional)
#define PACKSIZE 18 // Maximum Packetsize if 3 digit x, y and negative 3 digit angle
RFM69 radio; // Create library object for RFM69HCW:
int rxcoor, rycoor, bxcoor, bycoor,yxcoor, yycoor;

struct ROBOMOTE_DATA_STRUCTURE{ //data sent from this device, must match receive on other arduino
  int16_t Ax;
  int16_t Ay;
  int16_t Az;
  int16_t Atrig;
  int16_t Bx;
  int16_t By;
  int16_t Bz;
  int16_t Btrig;
};
  int Ax;
  int Ay;
  int Az;
  int Atrig;
  int Bx;
  int By;
  int Bz;
  int Btrig;
ROBOMOTE_DATA_STRUCTURE data_robomote; //create an object of send structure

struct BIRDO_DATA_STRUCTURE{
  int16_t accelX;
  int16_t accelY;
  int16_t hall1;
  int16_t hall2;
};


BIRDO_DATA_STRUCTURE data_birdo; //create an object of receive structure

/* Dynamic Variables */
int pot1 = 0;
int data1[3];
int sticks[8];

void setup() {
  initPins();
  /* Init Radio */
  randomSeed(analogRead(0));
  Serial.begin(9600);
  Serial.print("Starting...\n");
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID); // Initialize the RFM69HCW:
  radio.setHighPower(); // Always use this for RFM69HCW
  if (ENCRYPT) // Turn on encryption if desired:
    radio.encrypt(ENCRYPTKEY);
    
  /* LCD and Serial */
  lcd.init(); //initialize LCD screen
  lcd.init(); //initialize again? (Idk this was in the example)
  lcd.backlight(); //activate backlight on the screen
  lcd.print("Robomote Init");
  Serial.begin(9600);
  Serial.println("Robomote Init");
}

void loop() {
  readSticks();
//  printSticksSerial();
  printSticksSendingSerial();
  printSticksLcd();
//  getPacket();
}

void readSticks() {
  sticks[0] =   analogRead(joyAx);
  sticks[1] =   analogRead(joyAy);
  sticks[2] =   analogRead(joyAz);
  sticks[3] =   digitalRead(joyTrigA);
  sticks[4] =   analogRead(joyBx);
  sticks[5] = (1023- analogRead(joyBy) );
  sticks[6] =   analogRead(joyBz);
  sticks[7] =   digitalRead(joyTrigB);

  data_robomote.Ax    =   sticks[0];
  data_robomote.Ay    =   sticks[1];
  data_robomote.Az    =   sticks[2];
  data_robomote.Atrig =   sticks[3];
  data_robomote.Bx    =   sticks[4];
  data_robomote.By    =   sticks[5];
  data_robomote.Bz    =   sticks[6];
  data_robomote.Btrig =   sticks[7];
}

void initPins(){
  pinMode(joyAx,    INPUT);
  pinMode(joyAy,    INPUT);
  pinMode(joyAz,    INPUT);
  pinMode(joyTrigA, INPUT);
  pinMode(joyBx,    INPUT);
  pinMode(joyBy,    INPUT);
  pinMode(joyBz,    INPUT);
  pinMode(joyTrigB, INPUT);
  pinMode(lcdSCL,   OUTPUT);
  pinMode(lcdSDA,   OUTPUT);
}
