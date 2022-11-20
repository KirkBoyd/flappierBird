// function: packetChanged()
//bool packetChanged(){
//  if (flapRate != lastFlapRate || birdsEyeX != lastBirdsEyeX || birdsEyeY != lastBirdsEyeY) {  return true;  }
//  else return false;
//}

// function: 
int getPackSize(int kill,int flapRate,int birdsEyeX,int birdsEyeY){
  int packSize;
  packSize = sizeof("k") + intCharLen(kill);
  packSize = packSize + sizeof(" ") + sizeof("f") + intCharLen(flapRate);
  packSize = packSize + sizeof(" ") + sizeof("x") + intCharLen(birdsEyeX);
  packSize = packSize + sizeof(" ") + sizeof("y") + intCharLen(birdsEyeY);
  return packSize;
}

// function: 
int intCharLen(int testVal) {
  int len = 0;
  if (testVal <= 0) { len = len + 1;  }
  while (abs(testVal) > 0) {
    len = len + 1;
    testVal = testVal / 10;
  }
  return len;
}


// function: 
int char2int3(char digit1, char digit2, char digit3){
//  char digit1 = '6';
//  Serial.print("digit1: ");
//  Serial.print(digit1);
//  char digit2 = '9';
//  Serial.print(" digit2: ");
//  Serial.print(digit2);
//  char digit3 = '6';
//  Serial.print(" digit3: ");
//  Serial.println(digit3);
//  Serial.print("(int)digit1: ");
//  Serial.println((int)digit1);
//  Serial.print("(int)digit1: ");
//  Serial.print((int)digit1 - '0');
//  Serial.print(" digit2: ");
//  Serial.print((int)digit2 - '0');
//  Serial.print(" digit3: ");
//  Serial.println((int) digit3 - '0');
  int digit1int = (int)digit1 - '0';
  int digit2int = (int)digit2 - '0';
  int digit3int = (int)digit3 - '0';
  int ans = digit1int*100 + digit2int*10 + digit3int;
  return ans;
//  Serial.print("ans: ");
//  Serial.println(ans);
}
int char2int4(char digit1, char digit2, char digit3, char digit4){
//    char digit1 = '6';
//  Serial.print("digit1: ");
//  Serial.print(digit1);
//  char digit2 = '9';
//  Serial.print(" digit2: ");
//  Serial.print(digit2);
//  char digit3 = '6';
//  Serial.print(" digit3: ");
//  Serial.println(digit3);
//  Serial.print("(int)digit1: ");
//  Serial.println((int)digit1);
//  Serial.print("(int)digit1: ");
//  Serial.print((int)digit1 - '0');
//  Serial.print(" digit2: ");
//  Serial.print((int)digit2 - '0');
//  Serial.print(" digit3: ");
//  Serial.println((int) digit3 - '0');
  int digit1int = (int)digit1 - '0';
  int digit2int = (int)digit2 - '0';
  int digit3int = (int)digit3 - '0';
  int digit4int = (int)digit4 - '0';
  int ans = digit1int*1000 + digit2int*100 + digit3int*10 + digit4int;
  return ans;
//  Serial.print("ans: ");
//  Serial.println(ans);
}
