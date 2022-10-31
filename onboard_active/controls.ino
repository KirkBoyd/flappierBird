void throttle(){
//  if (kill != 1) {
    ESC.write(flapRate);
//  }
}

void trim(){
//  birdsEyeX = birdsEyeX/10;
//  servo1.write(birdsEyeX);
  if(birdsEyeX > 1000){
    servo1.write(180);
  }
  else servo1.write(0);
}
void roll(){
//  birdsEyeY = birdsEyeY/10;
//  servo2.write(birdsEyeY);
  if(birdsEyeY > 1000){
    servo2.write(180);
  }
  else servo2.write(0);
}
