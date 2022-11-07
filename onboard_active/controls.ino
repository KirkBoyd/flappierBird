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


    double scaleGrav = (xGrav + 9.81);
    scaleGrav = scaleGrav/(2*9.81);
    float sendGrav = 180*scaleGrav;
    servo2.write(sendGrav);

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
void calib(){
  servo1.write(90);
  servo2.write(90);
}
