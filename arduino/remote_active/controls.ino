//void trim(){
//    int trimOffset = birdsEyeY + 90;
//    if (trimOffset < 0) {trimOffset = 0;}
//    else if (trimOffset > 180) { trimOffset = 180;}
//    trimOffset = trimOffset - 90;
//    double scaleGrav = (xGrav + 9.81);
//    scaleGrav = scaleGrav/(2*9.81);
//    float sendGrav = 180*scaleGrav;
//    double trimVal = sendGrav + trimOffset + cruiseOffset;
////    servo2.write(sendGrav + trimOffset + cruiseOffset);
//}
//function: lean()
// adjust angle of tail fin about body (not trim) acccording to stick B x axis
void lean(){ 
//  Serial.print("birdsEyeX:");
//  Serial.print(birdsEyeX); 
  leanAmt = (birdsEyeX-5000)*(-1) + 90;
  if ( leanAmt < minLean ){ leanAmt = minLean; }
  else if ( leanAmt > maxLean ) { leanAmt = maxLean; } 
//  Serial.print(" leanAmt:");
//  Serial.print(leanAmt);
  leanVal = leanAmt + leanCtrOffset;
  leanBias = leanVal - 90 + (-1)*leanCtrOffset; // how far from center is the tail
//  Serial.print(" leanVal:");
//  Serial.println(leanVal);
//  servo1.write( leanVal );
}
