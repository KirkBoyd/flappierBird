/* function: printCtrlsLcd() -  prints all relevant bird values to LCD screen on remote*/ 
void printCtrlsLcd(){
  trim();
  lean();
  // first line
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("K:");
  lcd.print(kill);
  lcd.print(" Lean: ");
  lcd.print(leanVal);
  // second line
  lcd.setCursor(0,1);
//  lcd.print("Bx");
//  lcd.print(data_robomote.Bx);
//  lcd.print("y");
//  lcd.print(data_robomote.By);
}
/* function: printTrigs() - print joystick button/trigger values */
void printTrigs(){
    Serial.print("TrigA: ");
    Serial.print(data_robomote.Atrig);
    Serial.print(", TrigB: ");
    Serial.println(data_robomote.Btrig);
}

/* function: printSticksLcd() -  prints all joystick values to LCD screen on remote*/ 
void printSticksLcd(){
  //print joystick A info
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ax");
  lcd.print(data_robomote.Ax);
  lcd.print("y");
  lcd.print(data_robomote.Ay);
//  lcd.print("z");
//  lcd.print(data_robomote.Az);
  lcd.print("T");
  lcd.print(data_robomote.Atrig);
  //print joystick B info
  lcd.setCursor(0,1);
  lcd.print("Bx");
  lcd.print(data_robomote.Bx);
  lcd.print("y");
  lcd.print(data_robomote.By);
//  lcd.print("z");
//  lcd.print(data_robomote.Bz);
  lcd.print("T");
  lcd.print(data_robomote.Btrig);
  //delay(200);
}

/* function: printSticksSerial() - prints raw analog joystick values to serial monitor */ 
void printSticksSerial(){
  //print joystick A info
  Serial.print("\nAx: ");
  Serial.print(analogRead(joyAx));
  Serial.print("\t Ay: ");
  Serial.print(analogRead(joyAy));
//  Serial.print("\t Az: ");
//  Serial.print(analogRead(joyAz));
  Serial.print("\t AT: ");
  Serial.print(digitalRead(joyTrigA));
  //print joystick B info
  Serial.print("\t Bx: ");
  Serial.print(analogRead(joyBx));
  Serial.print("\t By: ");
  Serial.print(analogRead(joyBy));
//  Serial.print("\t Bz: ");
//  Serial.print(analogRead(joyBz));
  Serial.print("\t BT: ");
  Serial.print(digitalRead(joyTrigB));
}

/* function: printSticksSendingSerial() - prints properly aligned/shifted joystick values to Serial monitor */ 
void printSticksSendingSerial(){
  //print joystick A info
  Serial.print("\nAx: ");
  Serial.print(data_robomote.Ax);
  Serial.print("\t Ay: ");
  Serial.print(data_robomote.Ay);
//  Serial.print("\t Az: ");
//  Serial.print(data_robomote.Az);
  Serial.print("\t AT: ");
  Serial.print(data_robomote.Atrig);
  //print joystick B info
  Serial.print("\t Bx: ");
  Serial.print(data_robomote.Bx);
  Serial.print("\t By: ");
  Serial.print(data_robomote.By);
//  Serial.print("\t Bz: ");
//  Serial.print(data_robomote.Bz);
  Serial.print("\t BT: ");
  Serial.print(data_robomote.Btrig);
}

/* function: printStickDirs() - prints converted directional joystick values */ 
void printStickDirs(){
  //print joystick A info
  Serial.print("\nAx: ");
  Serial.print(stickDirAx);
  Serial.print("\t Ay: ");
  Serial.print(stickDirAy);
//  Serial.print("\t Az: ");
//  Serial.print(stickDirAz);
  Serial.print("\t AT: ");
  Serial.print(stickDirAtrig);
  //print joystick B info
  Serial.print("\t Bx: ");
  Serial.print(stickDirBx);
  Serial.print("\t By: ");
  Serial.print(stickDirBy);
//  Serial.print("\t Bz: ");
//  Serial.print(stickDirBz);
  Serial.print("\t BT: ");
  Serial.print(stickDirBtrig);
}

/* function: printBirdo() - prints sensor data from bird to serial monitor */ 
void printBirdo(){
  Serial.print("\nHall1: ");
  Serial.print(data_birdo.hall1);
  Serial.print("\t\t Hall2: ");
  Serial.print(data_birdo.hall2);
  Serial.print("\t\t Ax: ");
  Serial.print(data_birdo.accelX);
  Serial.print("\t\t Ay: ");
  Serial.print(data_birdo.accelY);
}
