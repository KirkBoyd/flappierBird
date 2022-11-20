//
// The Pixy isn't doing anything besides providing power, in this setup.
// The pro mini sends random data to the RFM69 radio via SPI and the LCD screen via data lines.
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// Based on RFM69 library sample code by Felix Rusu
// http://LowPowerLab.com/contact
// Modified for RFM69HCW by Mike Grusin, 4/16
// This sketch will show you the basics of using an
// RFM69HCW radio module. SparkFun's part numbers are:
// 915MHz: https://www.sparkfun.com/products/12775
// 434MHz: https://www.sparkfun.com/products/12823
// See the hook-up guide for wiring instructions:
// https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide
// Uses the RFM69 library by Felix Rusu, LowPowerLab.com
// Original library: https://www.github.com/lowpowerlab/rfm69
// SparkFun repository: https://github.com/sparkfun/RFM69HCW_Breakout

// LiquidCrystal Library originally added 18 Apr 2008 by David A. Mellis library modified 5 Jul 2009
// by Limor Fried (http://www.ladyada.net) example added 9 Jul 2009
// by Tom Igoe modified 22 Nov 2010
// by Tom Igoe modified 7 Nov 2016 by Arturo Guadalupi
// This example code is in the public domain.
// http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld


#include <Wire.h>
#include <RFM69.h>
#include <SPI.h>
#include <LiquidCrystal.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     10   // Must be the same for all nodes
#define MYNODEID      1   // My node ID
#define TONODEID      2   // Destination node ID

// RFM69 frequency, uncomment the frequency of your module:

//#define FREQUENCY   RF69_433MHZ
#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        false // Request ACKs or not

// Packet sent/received indicator LED (optional):
// #define LED           9 // LED positive pin
// #define GND           8 // LED ground pin

#define PACKSIZE 18 // Maximum Packetsize if 3 digit x, y and negative 3 digit angle

// Create a library object for our RFM69HCW module:
RFM69 radio;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int rxcoor, rycoor, bxcoor, bycoor,yxcoor, yycoor;

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(9600);
  Serial.print("Starting...\n");
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Initialize the RFM69HCW:
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setHighPower(); // Always use this for RFM69HCW
  // Turn on encryption if desired:
  if (ENCRYPT)
    radio.encrypt(ENCRYPTKEY);
}


void loop() 
{ 
  static int i = 0;
  int j;
  char buf[32];
  char data[PACKSIZE];
  static int sendlength = 0;

  lcd.setCursor(0,0);
//  lcd.autoscroll();
    for (i=0; i<1000; i++) {
      // Generate random coordinates for the red, blue and yellow balls.
      rxcoor=random(20, 80);
      rycoor=random(100, 199);
      bxcoor=random(40, 90);
      bycoor=random(200, 299);
      yxcoor=random(300, 399);
      yycoor=random(10, 40);
      sendlength = 0; // reset the packet
      // Construct a packet called data. Show sample number and red ball x, y coords.
      sprintf(data, "TX#: %d R:%d,%d", i, rxcoor, rycoor);
      sendlength = sizeof(data); // measure the constructed packet
      lcd.setCursor(2,0); //Red ball coords on 1st line, after activity char
      sendPacket(data, sendlength);
      sendlength = 0; // reset the packet
       // Construct a packet called data. Include blue and yellow ball x, y coords.
       sprintf(data, "B:%d,%d Y:%d,%d", bxcoor, bycoor, yxcoor, yycoor);
       sendlength = sizeof(data); // measure the constructed packet
       lcd.setCursor(0,1); //Blue and yellow ball coords on 2nd line
       sendPacket(data, sendlength);
       sendlength = 0; // reset the packet
      lcd.setCursor(0,0);
      if (i%20==0) lcd.print("->"); // Activity characters. Shows in top right.
      else if (i%10==0) lcd.print("> "); // Activity characters. Shows in top right.
      }
}
  

void sendPacket(char packet[], int plength) {
//    Serial.println(packet); // Send to serial monitor
    Serial.print("sending to node ");
    Serial.print(TONODEID, DEC);
    Serial.print(", message [");
    for (byte i = 0; i < plength; i++) {
      Serial.print(packet[i]);
      lcd.write(packet[i]);
    }
    Serial.println("]");
    // There are two ways to send packets. If you want
    // acknowledgements, use sendWithRetry():
    if (USEACK)
    {
      if (radio.sendWithRetry(TONODEID, packet, plength))
        Serial.println("ACK received!");
      else
        Serial.println("no ACK received");
    }
    // If you don't need acknowledgements, just use send():
    else // don't use ACK
    {
      radio.send(TONODEID, packet, plength);
    }
}
