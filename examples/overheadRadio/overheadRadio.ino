// RFM69HCW Simple Receive Sketch with Parsing to store coordinate values as integers
// Receive serial input characters from another RFM69 node
// Based on RFM69 library sample code by Felix Rusu
// http://LowPowerLab.com/contact
// Modified for RFM69HCW by Mike Grusin, 4/16

// This sketch will use
// RFM69HCW radio module. SparkFun's part numbers are:
// 915MHz: https://www.sparkfun.com/products/12775
// 434MHz: https://www.sparkfun.com/products/12823

// See the hook-up guide for wiring instructions:
// https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide

// Uses the RFM69 library by Felix Rusu, LowPowerLab.com
// Original library: https://www.github.com/lowpowerlab/rfm69
// SparkFun repository: https://github.com/sparkfun/RFM69HCW_Breakout

// Include the RFM69 and SPI libraries:
#include <SPI.h>
#include <RFM69.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!
#define NETWORKID     10  // Must be the same for all nodes
#define MYNODEID      2   // My node ID
#define TONODEID      1   // Origin node ID

// RFM69 frequency, uncomment the frequency of your module:
//#define FREQUENCY   RF69_433MHZ
#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):
#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):
#define USEACK        false // Request ACKs or not

// Create a library object for our RFM69HCW module:
RFM69 radio;

#define PACKSIZE 25 // Maximum Packetsize is 25,if 4 digit for x and y, and static characters
#define GrnID 1 // #defined constants for clearer code
#define BluID 2
#define YelID 3

int gx, gy, bx, by, yx, yy; //Global variables for storing x and y coordinates of green, blue and yellow ball locations

char buildInt[4];

void setup()
{
  // Open a serial port so we can see the data we receive
  Serial.begin(9600);
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  

  sprintf(buildInt, "    "); // Clear the buildInt array

  // Initialize the RFM69HCW:
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setHighPower(); // Always use this for RFM69HCW

  // Turn on encryption if desired:
  if (ENCRYPT)
    radio.encrypt(ENCRYPTKEY);
}

void loop()
{
  // RECEIVING
  // In this section, we'll check with the RFM69HCW to see
  // if it has received any packets:
  int j=0;
  char data[PACKSIZE];
  for (j=0; j<PACKSIZE; j++) data[j]=0; //Clear the data array to make sure there is no left over junk in it
  if (radio.receiveDone()) { // Got one!
    // Print out the information:
    //Serial.print("received from node ");
    //Serial.print(radio.SENDERID, DEC);
    //Serial.print(", message [");

    // The actual message is contained in the DATA array,
    // and is DATALEN bytes in size:
    for (byte i = 0; i < radio.DATALEN; i++){
      //Serial.print((char)radio.DATA[i]);
      data[i]=(char)radio.DATA[i];
      j=i;
      }
    // RSSI is the "Receive Signal Strength Indicator",
    // smaller numbers mean higher power.
    //Serial.print("], RSSI ");
    //Serial.println(radio.RSSI);
    
    // Now parse the data received into coordinates as integers
    j=0;
    while (j<PACKSIZE) {  //Work through the data and look for color letter indicators
      if(data[j]=='G') {  //Found green
        //Serial.print("Green:");
        pullCoords(data,j,GrnID); //Get the green x and y (as ints) and print them.
        //Serial.print(gx);
        //Serial.print(" ");
        //Serial.println(gy);
        Serial.print("<");
        Serial.print(gx);
        Serial.print("-");
        Serial.print(gy);
        Serial.print("-");
        break;                    // Assuming green is only color in its packet
      } else if (data[j]=='B') { //Found blue
        //Serial.print("Blue:");
        pullCoords(data,j,BluID); //Get the blue x and y (as ints) and print them.
        //Serial.print(bx);
        //Serial.print(" ");
        //Serial.println(by);
//        Serial.print("<BLU|");
        Serial.print(bx);
        Serial.print("-");
        Serial.print(by);
        Serial.print("-");
        j++;                      //Asuming blue and yellow and together, blue first
      } else if (data[j]=='Y') { //Found yellow
        //Serial.print("Yellow:");
        pullCoords(data,j,YelID); //Get the yellow x and y (as ints) and print them.
//        Serial.print("<YLW|");
        Serial.print(yx);
        Serial.print("-");
        Serial.print(yy);
        Serial.println(">");
        //Serial.print(yx);
        //Serial.print(" ");
        //Serial.println(yy);
        break;                    // Assuming yellow is at the end of its packet      
      } else {
        j++;                      // Go to next character
      }
    }
  }
}

void pullCoords(char packet[], int letterLoc, int color) {
    int BrS,Comma,BrE = 0; // Array locations of bracket start character, comma and bracket end character.
    int i=0;
  
    BrS=letterLoc+1; // The start bracket will be immediately after the color letter indicator
    for (i = BrS+1; i < PACKSIZE; i++) {
      if(packet[i]==',') Comma=i;  // Find the location of the comma that divides x and y coordinates
      if(packet[i]=='>') {
        BrE=i;  // Find the location of the end bracket
        break;  // And get out of for loop
      }
    }
    sprintf(buildInt, "    ");  // Clear the buildInt array      
    for (i = 0; i < (Comma-(BrS+1)); i++) {  // Work through the chars that represent the x coordinate
      buildInt[i]=packet[(BrS+1+i)];         // and copy them into the buildInt array
    }
    buildInt[(Comma-(BrS+1))]='\0';  // Terminate the buildInt array to make it easy on the converter
    switch (color) {                 // Convert the buildInt array to an integer and store in the correspoding color x coordinate
      case GrnID: 
        gx=atoi(buildInt); // Green x coord
        break;
      case BluID: 
        bx=atoi(buildInt); // Blue x coord
        break;
      case YelID: 
        yx=atoi(buildInt); // Yellow x coord
        break;
    }
    sprintf(buildInt, "    ");  // Clear the buildInt array 
    for (i = 0; i < (BrE-(Comma+1)); i++) {  // Work through the chars that represent the y coordinate
      buildInt[i]=packet[(Comma+1+i)];         // and copy them into the buildInt array
    }
    buildInt[(BrE-(Comma+1))]='\0';  // Terminate the buildInt array to make it easy on the converter
    switch (color) {                 // Convert the buildInt array to an integer and store in the correspoding color y coordinate
      case GrnID: 
        gy=atoi(buildInt); // Green y coord
        break;
      case BluID: 
        by=atoi(buildInt); // Blue y coord
        break;
      case YelID: 
        yy=atoi(buildInt); // Yellow y coord
        break;
    }
}
