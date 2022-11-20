void getOnboardPacket(){
  char data[PACKSIZE];
  if(radio.receiveDone()){
        // Print out the information:
    Serial.print("FromNode: ");
    Serial.print(radio.SENDERID, DEC);
    // RSSI is the "Receive Signal Strength Indicator",
    // smaller numbers mean higher power.
    Serial.print(", RSSI ");
    Serial.print(radio.RSSI);
    // The actual message is contained in the DATA array,
    // and is DATALEN bytes in size:
    for (byte i = 0; i < radio.DATALEN; i++)
      data[i] = radio.DATA[i];
    Serial.print(", data: ");
    Serial.println(data);
    
    for (byte i = 0; i < radio.DATALEN; i++) {
      current = data[i];
//      Serial.print("current: ");
//      Serial.print(current);
//      Serial.print(", val: ");
//      Serial.println((int)current);
      if((int)current == (int)'x'){ 
        digit1 = data[i+1];
        digit2 = data[i+2];
        digit3 = data[i+3];
        digit4 = data[i+4];
        accelX = char2int3(digit1, digit2, digit3) - 1000;
//        i++; 
        }
      else if((int)current == (int)'y'){ 
        digit1 = data[i+1];
        digit2 = data[i+2];
        digit3 = data[i+3];
        digit4 = data[i+4];
        accelY = char2int3(digit1, digit2, digit3) - 1000;
//        i = i+3;
      }
      else if((int)current == (int)'z'){ 
        digit1 = data[i+1];
        digit2 = data[i+2];
        digit3 = data[i+3];
        digit4 = data[i+4];
        accelZ = char2int4(digit1, digit2, digit3, digit4) - 1000;
//        i = i+4;
      }
      else if((int)current == (int)'h'){ 
        digit1 = data[i+1];
        digit2 = data[i+2];
        digit3 = data[i+3];
        digit4 = data[i+4];
        hallData = char2int4(digit1, digit2, digit3, digit4) - 1000;
//        i = i+4;
      }
      else{
        digit1 = '\0';
        digit2 = (char)0;
        digit3 = (char)0;
        digit4 = (char)0;
      }
    }
    //Serial.print((char)radio.DATA[i]);
    // Send an ACK if requested.
    if (radio.ACKRequested()) {
      radio.sendACK();
      Serial.println("ACK sent");
    }
    Blink(LED,10); // This will slow down the code, so comment it out for maximum speed.
  }
}
/* function:  -  */ 
void sendRemotePacket() {
    char data[PACKSIZE];
    static int sendlength = 0;
    sprintf(data, "k%d f%d x%d y%d", kill, (flapRate+100), (birdsEyeX+1000), (birdsEyeY+1000));
    sendlength = sizeof(data); // measure the constructed packet
    sendPacket(data, sendlength);
    Blink(LED,10); // This will slow down the code, so comment it out for maximum speed.
    sendlength = 0;
}

/* function:  -  */ 
void sendPacket(char packet[], int plength) {
    Serial.print("Node Target: ");
    Serial.print(TONODEID, DEC);
    Serial.print(", message [");
    Serial.print(packet);
    Serial.println("]");
    if (USEACK) { // There are two ways to send packets. If you want acknowledgements, use sendWithRetry():
      if (radio.sendWithRetry(TONODEID, packet, plength)) { Serial.println("ACK received!"); }
      else { Serial.println("no ACK received"); }
    }
    else{ radio.send(TONODEID, packet, plength); } // don't use ACK
}

/* function:  -  */ 
void dataXmitLCD () {
    static int i = 0;
//    int j;
//    char buf[32];
    char data[PACKSIZE];
    static int sendlength = 0;
  
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
      sendPacket(data, sendlength);
      sendlength = 0; // reset the packet
      sprintf(data, "B:%d,%d Y:%d,%d", bxcoor, bycoor, yxcoor, yycoor);
      sendlength = sizeof(data); // measure the constructed packet
      sendPacket(data, sendlength);
      sendlength = 0; // reset the packet]
    }
}

/* function:  -  */ 
void Blink(byte PIN, int DELAY_MS){
// Blink an LED for a given number of ms
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}

/* function:  -  */ 
void getPacket(){
    if (radio.receiveDone()){ // Got one!
    // Print out the information:
    Serial.print("received from node ");
    Serial.print(radio.SENDERID, DEC);
    Serial.print(", message [");

    // The actual message is contained in the DATA array,
    // and is DATALEN bytes in size:
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);

    // RSSI is the "Receive Signal Strength Indicator",
    // smaller numbers mean higher power.
    Serial.print("], RSSI ");
    Serial.println(radio.RSSI);

    // Send an ACK if requested.
    // (You don't need this code if you're not using ACKs.)
    if (radio.ACKRequested()){
      radio.sendACK();
      Serial.println("ACK sent");
    }
    Blink(LED,10); // This will slow down the code, so comment it out for maximum speed.
  }
}
