/* function: killCheck() - reads killswitch and sets to kill to true when button is moved to the "kill" position */
void killCheck() {
  if(digitalRead(kSwitch) == 0){ kill = true; }
  else{ kill = false; }
}

/* function: birdsEyeMap() - uses stick B to move around a set point in x,y coordinates
 * viewed from above (bird's eye view) to tell bird where to go */
void birdsEyeMap() {
  if (stickDirBx > 0) { birdsEyeX ++; }
  else if (stickDirBx < 0) { birdsEyeX --; }
  if (stickDirBy > 0) { birdsEyeY ++; }
  else if (stickDirBy < 0) { birdsEyeY --; }
  if( birdsEyeX < 0) { birdsEyeX = 0; }
  if( birdsEyeY < 0) { birdsEyeY = 0; }
}

/* function: throttleCheck() - reads stick A up and down to control flapRate */
void throttleCheck(){
  if (kill) { flapRate = 0; }
  else{
    if (flapRate < 255 && stickDirAy > 0) {flapRate++; }
    else if (flapRate > 0 && stickDirAy < 0) { flapRate--; }
  }
}

/* function: stickDirections() - checks each stick input for centered, up, all the way up, down, and all the way down
/* with values of 0, 1, 2, -1, -2, respectively */
void stickDirections() {
  if (data_robomote.Ax >= (centerAx - centerDeviationAx) && (centerAx + centerDeviationAx) >= data_robomote.Ax) { stickDirAx = 0; }
  else if (data_robomote.Ax < minAx) { stickDirAx = -2;  }
  else if (data_robomote.Ax > maxAx) { stickDirAx = 2;   }
  else if (data_robomote.Ax < (centerAx - centerDeviationAx)) { stickDirAx = -1; }
  else if (data_robomote.Ax > (centerAx + centerDeviationAx)) { stickDirAx = 1;  }
  else {  stickDirAx = 0;  }

  if (data_robomote.Ay >= (centerAy - centerDeviationAy) && (centerAy + centerDeviationAy) >= data_robomote.Ay) { stickDirAy = 0; }
  else if (data_robomote.Ay < minAy) { stickDirAy = -2;  }
  else if (data_robomote.Ay > maxAy) { stickDirAy = 2;   }
  else if (data_robomote.Ay < (centerAy - centerDeviationAy)) { stickDirAy = -1; }
  else if (data_robomote.Ay > (centerAy + centerDeviationAy)) { stickDirAy = 1;  }
  else {  stickDirAy = 0; }

  if (data_robomote.Az >= (centerAz - centerDeviationAz) && (centerAz + centerDeviationAz) >= data_robomote.Az) { stickDirAz = 0; }
  else if (data_robomote.Az < minAz) { stickDirAz = -2; }
  else if (data_robomote.Az > maxAz) { stickDirAz = 2;  }
  else if (data_robomote.Az < (centerAz - centerDeviationAz)) { stickDirAz = -1; }
  else if (data_robomote.Az > (centerAz + centerDeviationAz)) { stickDirAz = 1;  }
  else { stickDirAz = 0; }

  if (data_robomote.Bx >= (centerBx - centerDeviationBx) && (centerBx + centerDeviationBx) >= data_robomote.Bx) { stickDirBx = 0; }
  else if (data_robomote.Bx < minBx) { stickDirBx = -2;  }
  else if (data_robomote.Bx > maxBx) { stickDirBx = 2;   }
  else if (data_robomote.Bx < (centerBx - centerDeviationBx)) { stickDirBx = -1; }
  else if (data_robomote.Bx > (centerBx + centerDeviationBx)) { stickDirBx = 1;  }
  else { stickDirBx = 0;  }

  if (data_robomote.By >= (centerBy - centerDeviationBy) && (centerBy + centerDeviationBy) >= data_robomote.By) { stickDirBy = 0; }
  else if (data_robomote.By < minBy) { stickDirBy = -2;  }
  else if (data_robomote.By > maxBy) { stickDirBy = 2;   }
  else if (data_robomote.By < (centerBy - centerDeviationBy)) { stickDirBy = -1; }
  else if (data_robomote.By > (centerBy + centerDeviationBy)) { stickDirBy = 1;  }
  else { stickDirBy = 0;  }

  if (data_robomote.Bz >= (centerBz - centerDeviationBz) && (centerBz + centerDeviationBz) >= data_robomote.Bz) { stickDirBz = 0; }
  else if (data_robomote.Bz < minBz) { stickDirBz = -2;  }
  else if (data_robomote.Bz > maxBz) { stickDirBz = 2;   }
  else if (data_robomote.Bz < (centerBz - centerDeviationBz)) { stickDirBz = -1;  }
  else if (data_robomote.Bz > (centerBz + centerDeviationBz)) { stickDirBz = 1;   }
  else { stickDirBz = 0; }
}

/* function: readSticks() - imports and stores raw analog inputs from each potentiometer/button in each stick */
void readSticks() {
  sticks[0] =   analogRead(joyAx);
  sticks[1] =   analogRead(joyAy);
  sticks[2] =   analogRead(joyAz);
  sticks[3] =   digitalRead(joyTrigA);
  sticks[4] =   analogRead(joyBx);
  sticks[5] = (1023 - analogRead(joyBy) );
  sticks[6] =   analogRead(joyBz);
  sticks[7] =   digitalRead(joyTrigB);

  data_robomote.Ax    =   sticks[0];
  data_robomote.Ay    =   sticks[1];
  data_robomote.Az    =   sticks[2];
  data_robomote.Atrig =   sticks[3];
  data_robomote.Bx    =   sticks[4];
  data_robomote.By    =   sticks[5];
  data_robomote.Bz    =   sticks[6];
  data_robomote.Btrig =   sticks[7];
}
