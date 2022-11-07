void throttle(){
//  if (kill != 1) {
    ESC.write(flapRate);
//  }
}
void trim(){
//  birdsEyeX = birdsEyeX/10;
//  servo1.write(birdsEyeX);
//  if(birdsEyeX > 1000){
//    servo1.write(180);
//  }
//  else servo1.write(0);
    
    int trimOffset = birdsEyeY + 80;
    if (trimOffset < 0) {trimOffset = 0;}
    else if (trimOffset > 160) { trimOffset = 160;}
    trimOffset = trimOffset - 80;
    double scaleGrav = (xGrav + 9.81);
    scaleGrav = scaleGrav/(2*9.81);
    float sendGrav = 180*scaleGrav;
    servo2.write(sendGrav + trimOffset);

//  servo2.write(birdsEyeY); // for manual direct control with sticks
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
  servo1.write( leanAmt );
}
void calib(){
  servo1.write(90);
  servo2.write(90);
}
