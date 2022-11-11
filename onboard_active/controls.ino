void throttle(){
//  if (kill != 1) {
    ESC.write(flapRate);
//  }
}
void trim(){
    int trimOffset = birdsEyeY + 90;
    if (trimOffset < 0) {trimOffset = 0;}
    else if (trimOffset > 180) { trimOffset = 180;}
    trimOffset = trimOffset - 90;
    double scaleGrav = (xGrav + 9.81);
    scaleGrav = scaleGrav/(2*9.81);
    double sendGrav = 180*scaleGrav;
    double trimVal = sendGrav + trimOffset + cruiseOffset;
    servo2.write(trimVal);
}
void roll(){
//  birdsEyeY = birdsEyeY/10;
//  servo2.write(birdsEyeY);
//  if(birdsEyeY > 1000){
//    servo2.write(180);
//  }
//  else {servo2.write(0)};
  servo1.write(birdsEyeX); // for manual direct control with sticks
}

//function: lean()
// adjust angle of tail fin about body (not trim) acccording to stick B x axis
void lean(){
  leanAmt = birdsEyeX*(-1) + 90;
  if ( leanAmt < minLean ){ leanAmt = minLean; }
  else if ( leanAmt > maxLean ) { leanAmt = maxLean; } 
//  Serial.println(leanAmt);
  leanVal = leanAmt - leanCtrOffset;
  servo1.write( leanVal );
}

void calib(){
  servo1.write(90);
  servo2.write(90);
}
