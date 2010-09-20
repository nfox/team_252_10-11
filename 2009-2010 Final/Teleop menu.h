int selection = 0; //the selection number on the menu
int touchHits = 0;//used for debouncing
#pragma systemFile
string opt[] = {"Back", "Log","Drive Motors","Loading Motors", "Launch Motors","RFID Listen","Sensors", "Helo"};//menu items
int current_function = 0; //the current function visible
bool run_once = false; //used for efficiency
#include "RobotCode.c"//RFID
#include "LogController.c"//NSLog
bool logShowingBegin = 1;//show the log when we turn on
string menu_txt;//temp string
int previous_function = 0; //used for back button
int star = 0; //line that the star is on
int top_menu = 0;//top menu line
int compass = 0;//compass value
int compassR = 0;//realative compass value
//String[] motors;
bool joyOverRide = false; //used for overriding menu speeds with joystick
void updateMotors();//declare update motors
//variables the correspond to motors
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
bool LHR;
int LHS;
void PlayBeethoven() {//play sound
  PlaySoundFile("5th.rso");
}
void RFIDRead(){//reading RFID (initiated from menu)
    for(int i=3; i>=0; i--){//count down
      //the following draws countdown
      nxtDisplayCenteredTextLine(2, "Reading in:");
      nxtDisplayCenteredBigTextLine(3,"%i",i);
      wait1Msec(1000);
    }
    eraseDisplay();//clear display
    int RFID;//var to hold tag num in
    nxtDisplayCenteredTextLine(3, "Reading Tag");//say we are reading
    RFID=ReadNewTag();//read the tag
    nxtDisplayCenteredTextLine(3,"Tag %i",RFID);//display tag num
    nxtDisplayCenteredTextLine(4,"Description:");
    string descrip = "";//declare description var
    switch(RFID){//set description based on RIFD tag
      case 6://if tag 6
        descrip = "6";//set descrip six
        nxtDisplayCenteredTextLine(5,descrip);//display descrip
        wait1Msec(2000);
      break;
      default:
      PlayBeethoven();
    }
    wait1Msec(2000);
    if(RFID!=-1){
      NSLog(RFID+" " + descrip);
    }else {
      NSLog("No tag");
    }
    current_function=0; //switch to log step 1
    show_log();//switch to log step 2
}

/* Current_function values:
0=log
1=menu
2=Motor D
3=Motor Lo
4=Motors La
5=RFID Listen
6=TestAll
7=Sensors
*/
void change_menu(int p){ //change menu selection
  //if(star<4){
  if(abs(p)!=1){//if we got invalid input
    p=0;//nullify the input
    NSLog("P must be 1");//log the invalid input
  }else{
    star=star+p;//move the star
    selection=selection+p;//move the selection
    if(star==8){//if we need to scroll
      if (top_menu<((sizeof(opt)/sizeof(opt[0]))-8)){//if we can scroll
		    top_menu++;}//scroll
		    star--;//move the star back to the screen


	  }
	  if(star==-1){//if we need to scroll up
	    if(top_menu>0){//if we can scroll up
	      top_menu--;//scroll up
	    }
	    star++;//move the star back

	  }
	  //star++;
	  for(int i = 0; i<=7;i++){//for the whole screen
	    if(i==star){//if we are on star line
	      menu_txt="*"+opt[i+top_menu]+"";//set text to star + option that should be there
	    }else{
	      menu_txt=" "+opt[i+top_menu]+"";//set text to option for that line
	    }
	    nxtDisplayTextLine(i,menu_txt);//draw the text
	  }
  }


//}
}
void display_menu(){


  run_once=false;//so we draw what we need to
  for(int i = 0; i<=7;i++){//draw code. see above
	    if(i==star){
	      menu_txt="*"+opt[i+0]+"";
	    }else{
	      menu_txt=" "+opt[i+0]+"";
	    }
	    nxtDisplayTextLine(i,menu_txt);
	  }
	  wait1Msec(250);

  while(nNxtButtonPressed!=3){//while not pressing enter
    if(nNxtButtonPressed==2 && time1[T1] > 500 && selection > 0){//if we press left button we have a place to scroll up to and there has been 500 milisec between button presses

      time1[T1] = 0;//reset timer
      change_menu(-1);//star up
      //decrease selection if above one and preventing double reads
    }else if(nNxtButtonPressed==1 && time1[T1] > 500 && selection < 7){//if we press right button and we have another selection to make and there have been 500 ms between presses
      change_menu(1);//star down
      time1[T1] = 0;//reset timer
      //increase selection prevent double reads
    }
  }
  while(nNxtButtonPressed==3);//wait till
  eraseDisplay();
  switch(selection)
  {
    case 0:
      current_function=previous_function;//go back to prev page
      ClearSounds();
    break;
    case 1:
      current_function=0;//log
    break;
    case 2:
      current_function=2;//motor D
    break;
    case 3:
      current_function=3;//motor Lo
    break;
    case 4:
      current_function=4; //Motora La
    break;
    case 5:
      current_function=5; // RFID
    break;
    case 6:
      current_function = 6;//test
    break;
    case 7:
      current_function = 7;//sensors
    break;
  }
  wait1Msec(250);
}

void menu_init(){
  isShowingLog = logShowingBegin;//set whether or not to show log when starting
  NSLog("","1","");//initialize log
  NSLog("Log");//initial message
}
void menu_main(){
  //while (true){
    switch(current_function)//draw depending on what mode we are in
    {
      case 0://if we are showing the log
        if(!isShowingLog) show_log();//if the log isnt already showing show it
        if(nNxtButtonPressed == 2){//if we left button
          while(nNxtButtonPressed == 2);//debounce
          scroll_down();//scroll
        }
        if(nNxtButtonPressed == 1){//if we press right button
          while(nNxtButtonPressed==1);//debounce
          scroll_up();//scroll up
        }
      break;
      case 1://if we are going to display menu
        display_menu();//display menu
      break;
      case 2: //Motor D
        if(!run_once){//prevet redrawing static text
          eraseDisplay();//clear display
          run_once=true;//we have run the one time drawing
          nxtDisplayTextLine(6, "L: -100, R:100");//user interaction directions
        }
        nxtDisplayTextLine(0,"LR: " + LR);//display Left Rear Speed
        nxtDisplayTextLine(1,"LF: " + LF);//Display left fron speed
        nxtDisplayTextLine(2,"RF: " + RF);//display right front speed
        nxtDisplayTextLine(3,"RR: " + RR);//display right rear speed

        if(nNxtButtonPressed == kRightButton){//if we press right button
          while(nNxtButtonPressed == kRightButton){//while we are holding it
            LR = 100;//set Left rear to 100
            LF = 100;//set left front to 100
            RF = 100;//set right front to 100
            RR = 100;//set right rear to 100
            updateMotors();//update the motors
            nxtDisplayTextLine(0,"LR: " + LR);//display Left Rear Speed
            nxtDisplayTextLine(1,"LF: " + LF);//display Left Front speed
            nxtDisplayTextLine(2,"RF: " + RF);//display right front speed
            nxtDisplayTextLine(3,"RR: " + RR);//display right rear speed
          }
        }else if(nNxtButtonPressed == 2){//if we are pressing left
          while(nNxtButtonPressed == kLeftButton){//while it is still pressed
            LR = -100;//set Left Rear to -100
            LF = -100;//set Left Front to -100
            RF = -100;//set Right Front to -100
            RR = -100;//set Right Rear to -100
            updateMotors();//update the motors
            nxtDisplayTextLine(0,"LR: " + LR);//display Left Rear speed
            nxtDisplayTextLine(1,"LF: " + LF);//display Left Front speed
            nxtDisplayTextLine(2,"RF: " + RF);//display right front speed
            nxtDisplayTextLine(3,"RR: " + RR);//display right rear speed
          }
        }else{//if no button is pressed
          if(!joyOverRide){//if the joystick is controlling
            LR = 0;//stop left rear
            LF = 0;//stop left front
            RF = 0;//stop right front
            RR = 0;//stop right rear
            updateMotors();//update the motors
          }
        }

      break;
      case 3://motor Lo
        if(!run_once){//if we havent done the 1 time drawing
          eraseDisplay();//clear display
          nxtDisplayTextLine(6, "L: 75, R: 100");//draw user instructions
          run_once=true;//we have done the one time drawing
        }
        nxtDisplayTextLine(0, "R Elavator: " + RE);//display Right Elavator Speed
        nxtDisplayTextLine(1, "L Elavator " + LE);//Display left elavator speed
        nxtDisplayTextLine(2, "E helper " + LHS);//display elavator helper speed

        if(nNxtButtonPressed==kRightButton){//if pressing right button
          while(nNxtButtonPressed==kRightButton){//while pressing right button
            RE = 100;//set right elavator to 100
            LE = 100;//set left elavator to 100
            updateMotors();//update the motors
            nxtDisplayTextLine(0,"R Elavator: " + RE);//display the speed for the right elavator
            nxtDisplayTextLine(1, "L Elavator " + LE);//display the speed for the left elavator
          }
        }else if(nNxtButtonPressed==kLeftButton){//if we press left button
          while(nNxtButtonPressed==kLeftButton){//while its pressed
            RE = 75;//set right elavator to 75
            LE = 75;//set the left elavator to 75
            updateMotors();//update the motors
            nxtDisplayTextLine(0,"R Elavator: " + RE);//display right elavator speed
            nxtDisplayTextLine(1, "L Elavator " + LE);//display left elavator speed
          }
        }else{//if we arent pressing buttons
          if(!joyOverRide){//if the joystick isn't setting it
            RE = 0;//set right elavator to 0
            LE = 0;//set left elavator to 0
          }
          updateMotors();//update the motors
        }
      break;
      case 4://motors LA
        if(!run_once){//if we have not done the one time drawinging
            eraseDisplay();//clear the display
            run_once=true;//we have done one time drawing
            nxtDisplayTextLine(2,"R btn:");//user directions
            nxtDisplayTextLine(3,"H=100 S=100");//user directions
            nxtDisplayTextLine(4,"L btn:");//user directions
            nxtDisplayTextLine(5,"H=100 S=-100");//user directions
        }
        nxtDisplayTextLine(0,"Hopper: " + H);//display hopper speed
        nxtDisplayTextLine(1,"Swinger: " + S);//display swinger speed
        nxtDisplayTextLine(6,"S touch: " + touchHits);//display number of swinger rotations
        if(nNxtButtonPressed == kRightButton){//if we are pressing right button
          while(nNxtButtonPressed == kRightButton){//while we are pressing it
            H = 100;//set hopper to 100
            S = 100;//set swinger to 100
            updateMotors();//update motors
            nxtDisplayTextLine(0,"Hopper: " + H);//display hopper speed
            nxtDisplayTextLine(1,"Swinger: " + S);//display swinger speed
          }
        }else if(nNxtButtonPressed == kLeftButton){//if we press left button
          while(nNxtButtonPressed == kLeftButton){//while we are pressing it
            H = 100;//set hopper to 100
            S = -100;//set hopper to -100
            updateMotors();//update motors
            nxtDisplayTextLine(0,"Hopper: " + H);//display hopper speed
            nxtDisplayTextLine(1,"Swinger: " + S);//display swinger speed
          }
        }else{//if we arent pressing anything
          if(!joyOverRide){//if the joystick is not setting them
            H = 0;//stop hopper
            S = 0;//stop swinger
          }
          updateMotors();//update motors
        }
      break;
      case 5: //rfid read
        if(!run_once){//if we havent done one time work
          eraseDisplay();//clear display
          RFIDRead();//read the rfid sensor and deal with it
          run_once = false;//let we are switching out of this so the other thing needs to execute it's run once
        }
      case 6: //sensors
        if(!run_once){//if we have not run one time code
          nxtDisplayCenteredTextLine(0,"Sensors");//write sensors
          if(touchFS){//if touch fs pressed
            nxtDisplayTextLine(1,"S touch: pressed");//give output
          }else{//if not pressed
            nxtDisplayTextLine(1,"S touch");//give output
          }
          if(rightH){//if rightHelicopter touch pressed
            nxtDisplayTextLine(2,"Right H: pressed");//give output
          }else{//if right helicopter touch not pressed
            nxtDisplayTextLine(2,"Right H:");//give output
          }
          if(leftH){//if left Helicopter touch is pressed
            nxtDisplayTextLine(3,"Left H: pressed");//give output
          }else{//if left helicopter touch not pressed
            nxtDisplayTextLine(3,"Left H:");//give output
          }
          run_once = false;//we have done our one time code
        }
        if(touchFS){//if the swinger touch sensor is pressed
          nxtDisplayTextLine(1,"S touch: pressed");//give output
        }else{//if swinger touch sensor not pressed
          nxtDisplayTextLine(1,"S touch");//give output
        }
      break;
      case 7: //Helo
        if(!run_once){//if we have not done one time code
          nxtDisplayTextLine(0, "Helo");//what menu
          nxtDisplayTextLine(2, "Left: 100");//instructions
          nxtDisplayTextLine(3, "Right: -100");//instruction
          run_once = true;
        }
        if(nNxtButtonPressed == kRightButton){//if we are pressing right button
          B = 100;//set helicopter to 100
        }else if(nNxtButtonPressed == kLeftButton){//if we are pressing left button
          B = -100;//set helicopter to -100
        }else if(!joyOverRide){//if we are not pressing a button or controlling with joystick
          B = 0;//stop helicopter
        }
        nxtDisplayTextLine(1, "Helo S = " + B);//display helo speed

        break;
    }
    if(nNxtButtonPressed==3 && current_function!=1){//if we are hitting enter on not menu
      while(nNxtButtonPressed==3);//hang till release enter
      hide_log();//hide the log
      previous_function=current_function;//save the previous function so back works
      current_function=1;//set function to menu
    }
}
