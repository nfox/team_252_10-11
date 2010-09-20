#define EPD 3//amount of encoder tics per degree
int LR = 0;
int LF = 0;
int LE = 0;
int RE = 0;
int RF = 0;
int RR = 0;
int S = 0;
int H = 0;
int B = 0;
int LH = 0;
int LHO = 0;
bool LHR = false;
int LHS = 0;
bool running = true;
#define turn90Enc 90
#pragma systemFile
void updateMotors();
int targetRR;
int targetRF;
int targetLF;
int targetLR;
int Upowers;
/**
rotations roughly = amount of wheel rotation in degrees
UPower = the power in percent to turn wheels at
*motorVar = a pointer to the motor variable to set
*encoder = a pointer to the motor encoder
*/
 void forward(int rotations, int Upower, int *motorVar, long *encoder){
  int power = abs(Upower);  //set power to the absolute value of UPower (param)
  while(encoder/EPD < rotations){//while we are not at target encoder rotations
    motorVar = power;//set the motor variable to the power entered
  }
  motorVar = 0;//stop the motor

}
//see above, just with 2 motors. all things perform like above unless otherwise specified
 void forward(int rotations, int Upower, int *motorVar1, int *motorVar2, long *encoder1, long *encoder2 ){
  int power = abs(Upower);
  while(true){
    if(encoder1/EPD<rotations){
      motorVar1 = power;
    }else{
      motorVar1 = 0;
    }
    if(encoder2/EPD<rotations){
      motorVar2 = power;
    }else{
      motorVar2 = 0;
    }
    if(encoder1/EPD>=rotations && encoder2/EPD>=rotations){//if they have both hit target
      motorVar1 = 0;//stop
      motorVar2 = 0;//stop
      updateMotors();//poll vars and perform on motors
      break;//break the loop
    }
    updateMotors();//for good measure
  }
}
//similar to and works eactly the same as above
 void forward(int rotations, int Upower, int *motorVar1, int *motorVar2, int *motorVar3, long *encoder1, long *encoder2, long *encoder3){
  int power = abs(Upower);
  while(true){
    if(encoder1/EPD<rotations){
      motorVar1 = power;
    }else{
      motorVar1 = 0;
    }
    if(encoder2/EPD<rotations){
      motorVar2 = power;
    }else{
      motorVar2 = 0;
    }
    if(encoder3/EPD<rotations){
      motorVar3 = power;
    }else{
      motorVar3 = 0;
    }
    if(encoder1/EPD>=rotations && encoder2/EPD>=rotations && encoder3/EPD>=rotations){
      motorVar1 = 0;
      motorVar2 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}
void forward(int rotations, int Upower, int *motorVar1, int *motorVar2, int *motorVar3, int *motorVar4, long *encoder1, long *encoder2){
  int power = abs(Upower);
  while(true){
    if(abs(encoder1/EPD)<rotations){
      motorVar1 = power;
      motorVar2 = power;
    }else{
      motorVar1 = 0;
      motorVar2 = 0;
    }
    if(abs(encoder2/EPD)<rotations){
      motorVar3 = power;
      motorVar4 = power;
    }else{
      motorVar3 = 0;
      motorVar4 = 0;
    }
    if(abs(encoder1/EPD)>=rotations && abs(encoder2/EPD)>=rotations){
      motorVar1 = 0;
      motorVar2 = 0;
      motorVar3 = 0;
      motorVar4 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//see forward with same params
void reverse(int rotations, int Upower, int *motorVar, long *encoder){
  int power = -abs(Upower);
  while(encoder/EPD < rotations){
    motorVar = power;
  }
}
//see forward with same params
 void reverse(int rotations, int Upower, int *motorVar1, int *motorVar2, long *encoder1, long *encoder2 ){
  int power = -abs(Upower);
  while(true){
    if(encoder1/EPD>rotations){
      motorVar1 = power;
    }else{
      motorVar1 = 0;
    }
    if(encoder2/EPD>rotations){
      motorVar2 = power;
    }else{
      motorVar2 = 0;
    }
    if(encoder1/EPD<=rotations && encoder2/EPD<=rotations){
      motorVar1 = 0;
      motorVar2 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}
//see forward with same params
 void reverse(int rotations, int Upower, int *motorVar1, int *motorVar2, int *motorVar3, long *encoder1, long *encoder2, long *encoder3){
  int power = -abs(Upower);
  while(true){
    if(encoder1/EPD<rotations){
      motorVar1 = power;
    }else{
      motorVar1 = 0;
    }
    if(encoder2/EPD<rotations){
      motorVar2 = power;
    }else{
      motorVar2 = 0;
    }
    if(encoder3/EPD<rotations){
      motorVar3 = power;
    }else{
      motorVar3 = 0;
    }
    if(encoder1/EPD>=rotations && encoder2/EPD>=rotations && encoder3/EPD>=rotations){
      motorVar1 = 0;
      motorVar2 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}
//see forward with same params
 void reverse(int Urotations, int Upower, int *motorVar1, int *motorVar2, int *motorVar3, int *motorVar4, long *encoder1, long *encoder2){
  int power = -abs(Upower);
  int rotations = -abs(Urotations);
  while(true){
    if(encoder1/EPD>rotations){
      motorVar1 = power;
      motorVar2 = power;
    }else{
      motorVar1 = 0;
      motorVar2 = 0;
    }
    if(encoder2/EPD>rotations){
      motorVar3 = power;
      motorVar4 = power;
    }else{
      motorVar3 = 0;
      motorVar4 = 0;
    }
    if(encoder1/EPD<=rotations && encoder2/EPD<=rotations){
      motorVar1 = 0;
      motorVar2 = 0;
      motorVar3 = 0;
      motorVar4 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}
//go forward for amount of time
//trash = ignored
//time = amount of time
//Upower = power
//*motorVar = pointer to motorVar to update
void forward(bool trash, int time, int Upower, int *motorVar){
  motorVar = Upower; //change motor power
  updateMotors();
  wait1Msec(time);//wait for time
}
//infineitly run a moter forward
//Upower = how fast
//*motorVar = which motor var pointer
void forward(int Upower, int *motorVar){
  while(running){//while the robot is running{
    motorVar = Upower;//set mototr to power param
    updateMotors();
  }
}
//turns clockwise
//rotations = wheel rotation in degrees
//Upower = power to turn with
//*motorVarL1 = the left encoded motor variable pointer
//*motorVarL2 = the left nonencoded motor variable pointer
//*motorVarR1 = the right encoded motor variable pointer
//*motorVarR2 = the right nonencoded motor variable pointer
//*motorEncoderL1 = the pointer to the motor encoder on the left
//*motorEncoderR1 = the pointer to the motor encoder on the right
 void turnCW(int rotations, int Upower, int *motorVarL1, int *motorVarL2, int *motorVarR1, int *motorVarR2, long *motorEncoderL1, long *motorEncoderR1){
  int powerL = abs(Upower);//power on the left is positive power
  int powerR = -abs(Upower);//power in the right is negative power
  while(true){
  nxtDisplayTextLine(1, "Target " + rotations);//display how turn is going
  nxtDisplayTextLine(2, "valL " + motorEncoderL1*EPD);//display how turn is going
  nxtDisplayTextLine(3, "valR " + motorEncoderR1*EPD);//display how turn is going
  //deciding on whether or not to keep the wheels rotating
    if(abs(motorEncoderL1*EPD) < rotations){
      motorVarL1 = powerL;
      motorVarL2 = powerL;
    }else{
      motorVarL1 = 0;
      motorVarL2 = 0;
    }
    if(abs(motorEncoderR1*EPD) < rotations){
      motorVarR1 = powerR;
      motorVarR2 = powerR;
    }else{
      motorVarR1 = 0;
      motorVarR2 = 0;
    }
    if(abs(motorEncoderR1*EPD) >= rotations &&  motorEncoderL1*EPD >= rotations){
      motorVarL1 = 0;
      motorVarL2 = 0;
      motorVarR1 = 0;
      motorVarR2 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}
//see above. exact same but flipped speeds
 void turnCCW(int rotations, int Upower, int *motorVarL1, int *motorVarL2, int *motorVarR1, int *motorVarR2, long *motorEncoder1, long *motorEncoder2){
  int powerL = -abs(Upower);
  int powerR = abs(Upower);
  motorEncoder1 = 0;
  motorEncoder2 = 0;
  while(true){
    if(abs(motorEncoder1*EPD) < rotations){

      motorVarL1 = powerL;
      motorVarL2 = powerL;
    }else{
      motorVarL1 = 0;
      motorVarL2 = 0;
    }
    if(abs(motorEncoder2*EPD) < rotations){
      motorVarR1 = powerR;
      motorVarR2 = powerR;
    }else{
      motorVarR1 = 0;
      motorVarR2 = 0;
    }
    if(abs(motorEncoder2*EPD) >= rotations &&  abs(motorEncoder1*EPD) >= rotations){
      motorVarL1 = 0;
      motorVarL2 = 0;
      motorVarR1 = 0;
      motorVarR2 = 0;
      updateMotors();
      break;
    }
    updateMotors();
  }
}

