/**************************************************
   onboard_active - Flappier Bird
   Teensy 4.0
   Kirk Boyd
   10/31/2022
 *************************************************/
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

/************** IMU Setup ***************/
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28); //I2C adress for IMU

/************** Radio Setup ***********/
// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     10   // Must be the same for all nodes
#define MYNODEID      69   // My node ID
#define TONODEID      96   // Destination node ID
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

/************** Servo Setup ***********/
Servo servo1;
Servo servo2;
Servo ESC;

/************* Dynamic Variables ******/
int kill = 0;
int flapRate = 0;
int birdsEyeX = 0;
int birdsEyeY = 0;
char data[PACKSIZE];
char current;
char digit1;
char digit2;
char digit3;
char digit4;
int accelX;
int accelY;
int accelZ;
int hallData;
double xGrav = -100000; 
double yGrav = -1000000; 
double zGrav = -1000000; //dumb values, easy to spot problem
double yGravTol;

/*********** MAIN CODE **************/
void setup() {
  /* Init Serial Monitor for Debug */
  Serial.begin(9600);
  
  /* Init Servos & Sensors */
  pinMode(hall1,INPUT);
  pinMode(hall2,INPUT);
  pinMode(srv1,OUTPUT);
  servo1.attach(srv1);
  servo2.attach(srv2);
  ESC.attach(esc);
  ESC.write(5);
  delay(2000);
  servo1.write(90);
  servo2.write(90);
  
  /* Init Radio */
  randomSeed(analogRead(0));
  Serial.begin(9600);
  Serial.print("Starting...\n");
  Serial.println("CA-CAAAAAAAAAWWWWWW!");
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID); // Initialize the RFM69HCW:
  radio.setHighPower(); // Always use this for RFM69HCW
  if (ENCRYPT) // Turn on encryption if desired:
    radio.encrypt(ENCRYPTKEY);
  
  /* Init IMU */
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
  /*** Main Logic ***/
  if (kill == 1) {ESC.write(0);}
//  calib();
//  checkHall();
  getIMUdata();
//  if (radio.receiveDone()){ // Got one!
//    getRemotePacket();
//  }
//  else{  sendOnboardPacket(); }
//  throttle();
  trim();
//    Tolerance for y gravity component. Desired: x = 0
 
//  roll();
  /*** End Main Logic ***/
//  Testing
  Serial.print("\tx= ");
  Serial.print(xGrav);
  Serial.print(" |\ty= ");
  Serial.print(yGrav);
  Serial.print(" |\tz= ");
  Serial.println(zGrav);
  
  /* Radio Dynamic Variables */
//  static int i = 0;
//  int j;
//  char buf[32];
//  char data[PACKSIZE];
//  static int sendlength = 0;
//  dataXmitLCD();
// Serial.println(analogRead(hall1));
//  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> grav = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
//  z = euler.z();
//  Serial.println(euler.z());
//  dataOut();
//  delay(1000);
//  dataXmitLCD();

}

void servoTest() {
  for (int i=0 ; i<=180 ; i++){
    servo2.write(i);
    delay(10);
  }
}

void checkHall(){
  hallData = analogRead(hall1);
}

void getRot(){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  accelX = (int)euler.x() + 1000;
  accelY = (int)euler.y() + 1000;
  accelZ = (int)euler.z() + 1000;
}
