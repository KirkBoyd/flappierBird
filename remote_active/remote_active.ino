/**************************************************
   remote_active - Flappier Bird
   Teensy 4.0
   Kirk Boyd
   10/31/2022
 *************************************************/
/* LCD Libraries */
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //best functioning I2C library I could find which works with Teensy and the LCD I had lying around

/* RADIO LIBRARIES */
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
#define kSwitch 5 //digital pin 6

/*OBJECTS*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

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
char maxPacket[] = "k1 f255 x9999 y9999"; //example packet with maximum values we will allow
int PACKSIZE = sizeof(maxPacket); // Maximum Packetsize if 3 digit x, y and negative 3 digit angle
RFM69 radio; // Create library object for RFM69HCW:
int rxcoor, rycoor, bxcoor, bycoor, yxcoor, yycoor;

struct ROBOMOTE_DATA_STRUCTURE { //data sent from this device, must match receive on other arduino
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
//ROBOMOTE_DATA_STRUCTURE sticks_directions; //for storing which way sticks are pointing

struct BIRDO_DATA_STRUCTURE {
  int16_t accelX;
  int16_t accelY;
  int16_t hall1;
  int16_t hall2;
};


BIRDO_DATA_STRUCTURE data_birdo; //create an object of receive structure

/* Remote Potentiometer Data */
int stickDirAx = 0;
int stickDirAy = 0;
int stickDirAz = 0;
int stickDirAtrig = 0;
int stickDirBx = 0;
int stickDirBy = 0;
int stickDirBz = 0;
int stickDirBtrig = 0;

//int centers[8];
int centerAx = 513; //Ax
int centerAy = 489; //Ay
int centerAz = 180; //Az
int centerAtrig = 0;   //Atrig
int centerBx = 524; //Bx
int centerBy = 527; //By
int centerBz = 690; //Bz
int centerBtrig = 0;   //Btrig (not relevant here but keeping structure dims)

//int centerDeviations[8];
int centerDeviationAx = 15; // Ax
int centerDeviationAy = 15;
int centerDeviationAz = (170 - 58) / 2; //Az (z pots stray a lot)
int centerDeviationAtrig = 1;
int centerDeviationBx = 15; // Bx
int centerDeviationBy = 15;
int centerDeviationBz = (850 - 650) / 2; //Bz (z pots stray A LOT)
int centerDeviationBtrig = 1;

//int maxes[8];
int maxAx = 1018; // Ax
int maxAy = 1018;
int maxAz = 600; //Az (z pots stray a lot)
int maxAtrig = 1;
int maxBx = 1018; // Bx
int maxBy = 1018;
int maxBz = 1018; //Bz (z pots stray A LOT)
int maxBtrig = 1;

//int mins[8];
int minAx = 5; // Ax
int minAy = 5;
int minAz = 8; //Az (z pots stray a lot)
int minAtrig = 0;
int minBx = 5; // Bx
int minBy = 5;
int minBz = 620; //Bz (z pots stray A LOT)
int minBtrig = 0;

/* Dynamic Variables */
int pot1 = 0;
int data1[3];
int sticks[8];
int stickDirs[8];
//int sendLength;
//int packetLength;
//char packet[];

int birdsEyeX = 5000;
int lastBirdsEyeX = 5000;
int birdsEyeY = 5000;
int lastBirdsEyeY = 5000;
bool kill = false;
int lastKill = 0;
int flapRate = 0;
int lastFlapRate = 0;
int packSize = 0;
char digit1;
char digit2;
char digit3;
char digit4;
char current;
int accelX;
int accelY;
int accelZ;
int hallData;
int cruiseRate = 100; // GUESSED FOR NOW: Flap rate to hold altitude / cruise
int leanAmt = birdsEyeX + 90;
int minLean = 15;
int maxLean = 165;
int cruiseOffset = 40; // Extra tilt to add to trim servo for maintaining altitude
int leanCtrOffset = 10;
int escMin = 50;
int leanVal;

void setup() {
  initPins();
  /* Start Serial Communication */
  Serial.begin(9600);
  Serial.print("Starting...\n");
  Serial.println("Robomote Init");
  
  /* LCD and Serial */
  lcd.init(); //initialize LCD screen
  lcd.init(); //initialize again? (Idk this was in the example)
  lcd.backlight(); //activate backlight on the screen
  lcd.print("Robomote Init");
  
  /* Init Radio */
  randomSeed(analogRead(0));
  Serial.print("Node ");
  Serial.print(MYNODEID, DEC);
  Serial.println(" ready");
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID); // Initialize the RFM69HCW:
  radio.setHighPower(); // Always use this for RFM69HCW
  if (ENCRYPT) radio.encrypt(ENCRYPTKEY); // Turn on encryption if desired  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CA-CAAAAAAAWWWW!");
  delay(1000);
  lcd.clear();
  /* Testing */
}

void loop() {
  /****************** Main Logic *****************/
    killCheck(); // check kill switch
    readSticks(); // read joysticks 
    stickDirections(); // count up or down according to direction
    if (data_robomote.Btrig == 1){ // if right trigger is pressed, come home
      birdsEyeX = 5000; // becomes 0 onboard (to avoid sending negative values)
      birdsEyeY = 5000; // becomes 0 onboard
    }
    if (data_robomote.Atrig == 1){ // if left trigger is pressed, set to cruise flapRate
      flapRate = cruiseRate;
    }
    birdsEyeMap(); // (probably needs rewriting) moves virtual setpoint according to stick B directions
    throttleCheck(); // changes flap rate according to direction of left stick vertical
    packSize = getPackSize(kill,flapRate,birdsEyeX,birdsEyeY);
    if (kill) { 
      sendRemotePacket();
      printCtrlsLcd(); 
    }
    else if (packetChanged()) { 
        sendRemotePacket(); 
        lastFlapRate = flapRate;
        lastBirdsEyeX = birdsEyeX;
        lastBirdsEyeY = birdsEyeY;
        printCtrlsLcd();
    }
    
    // This needs fixing, but not a priority. For now we won't take data back.
    //  getPacket();
  /**************** End Main Logic ****************/
}

/* function:  initPins() - all of the pin initialization lines, 
 * offloaded to make setup loop more legible */
void initPins() {
  pinMode(kSwitch,  INPUT_PULLUP);
  pinMode(joyAx,    INPUT);
  pinMode(joyAy,    INPUT);
  pinMode(joyAz,    INPUT);
  pinMode(joyTrigA, INPUT_PULLDOWN);
  pinMode(joyBx,    INPUT);
  pinMode(joyBy,    INPUT);
  pinMode(joyBz,    INPUT);
  pinMode(joyTrigB, INPUT_PULLDOWN);
  pinMode(lcdSCL,   OUTPUT);
  pinMode(lcdSDA,   OUTPUT);
}
