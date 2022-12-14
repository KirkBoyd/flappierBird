//void dataOut () {
//    static int i = 0;
//    int j;
//    char buf[32];
//    char data[PACKSIZE];
//    static int sendlength = 0;
//    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//      // Construct a packet called data.
//    int xdata = euler.x();
//    int ydata = euler.y();
//    int zdata = euler.z();
//      Serial.print("Going to send z: ");
//      Serial.print( zdata );
//      sprintf(data, "x: %d, y: %d, z: %d", xdata, ydata, zdata);
//      Serial.print(" | Packet: " );
//      Serial.println(data);
//      sendlength = sizeof(data); // measure the constructed packet
//      sendPacket(data, sendlength);
//      sendlength = 0;
//}
void sendPacket(char packet[], int plength) {
    Serial.println(packet); // Send to serial monitor
    Serial.print("sending to node ");
    Serial.print(TONODEID, DEC);
    Serial.print(", message [");
    for (byte i = 0; i < plength; i++) { Serial.print(packet[i]); }
    Serial.println("]");
    // There are two ways to send packets. If you want acknowledgements, use sendWithRetry():
    if (USEACK) {
      if (radio.sendWithRetry(TONODEID, packet, plength)) { Serial.println("ACK received!"); }
      else { Serial.println("no ACK received"); }
    }
    else{ // don't use ACK
      radio.send(TONODEID, packet, plength);
    }
}

void dataXmitLCD () {
    static int i = 0;
    int j;
    char buf[32];
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
void Blink(byte PIN, int DELAY_MS)
// Blink an LED for a given number of ms
{
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
void getPacket(){
    if (radio.receiveDone()) // Got one!
  {
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
    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.println("ACK sent");
    }
    Blink(LED,10); // This will slow down the code, so comment it out for maximum speed.
  }
}
