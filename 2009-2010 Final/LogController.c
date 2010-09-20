#pragma systemFile //no unused func warnings
int mainProgramCounter = 0;//unknown usage
string screenText[15];//declare array of lines for log
bool isShowingLog = false;//declare and start off not showing log
bool logHasBeenInitiated = false;//declare logHasBeenInitiated and set to false
int top = 7;//set the default top index to 7
void scroll_down(){
  if(top<14){//keep from overscrolling down
    top++;//scroll down
  }
    //draw the log to the screen
    for(int i=0;i<=7;i++){
      if(top-i<15){
        nxtDisplayTextLine(i,screenText[top-i]);
    }else if(top>14 && top<=14){
      //draw blanks where needed
      nxtDisplayTextLine(i,"");
    }
  }
}
//
void scroll_up(){
  if(top>7)//keep from overscrolling up
  top--;//scroll up
  for(int i=0;i<=7;i++){//draw menu
    if(top-i<15){
      nxtDisplayTextLine(i,screenText[top-i]);
    }else{
      //write blanks if needed
      nxtDisplayTextLine(i,"");
    }
  }
}
void hide_log(){
  isShowingLog=false;//keep from redrawing by other functions
  eraseDisplay();//clear log from screen
}
void show_log(){
  isShowingLog=true;//we want to draw log
  eraseDisplay();//clear display
  top = 7;//set top to index 7
  //display lines
  nxtDisplayTextLine(7,screenText[0]);
  nxtDisplayTextLine(6,screenText[1]);
  nxtDisplayTextLine(5,screenText[2]);
  nxtDisplayTextLine(4,screenText[3]);
  nxtDisplayTextLine(3,screenText[4]);
  nxtDisplayTextLine(2,screenText[5]);
  nxtDisplayTextLine(1,screenText[6]);
  nxtDisplayTextLine(0,screenText[7]);
}
//Log with format
//DEPRECEATED FOR THE MOST PART
//USE ONLY FOR INITIALiZATION
//DO THAT BY CALLING NSLog("","1","");
void NSLog(string sFormatString, string param1, string param2) {
  //dnt rlly need this
if (mainProgramCounter != 300 && param2 == "1") return;
  //initialized log if neccesary
  if (!logHasBeenInitiated) {for (int i=0;i<15;i++) screenText[i] = "";logHasBeenInitiated=true;}
  //if we are showing the log
  if (isShowingLog) {
    eraseDisplay();//clear the display
    //draw log
    nxtDisplayTextLine(7,screenText[0]);
    nxtDisplayTextLine(6,screenText[1]);
    nxtDisplayTextLine(5,screenText[2]);
    nxtDisplayTextLine(4,screenText[3]);
    nxtDisplayTextLine(3,screenText[4]);
    nxtDisplayTextLine(2,screenText[5]);
    nxtDisplayTextLine(1,screenText[6]);
    nxtDisplayTextLine(0,screenText[7]);
  }
  if (param1 == "1") return;//if param 1 is 1 dont actually update the array

  string screenTextTemp[15];
  for (int i=0;i<15;i++) {//for the length of the array
    screenTextTemp[i] = screenText[i];//copy screenText to screenTextTemp
  }
  string text;
  StringFormat(text, sFormatString, param1, param2);//pass our parameters to string formatter
  screenText[0] = text;//make the first log entry the paramater passed
  for (int i=0;i<14;i++) {
     screenText[i+1] = screenTextTemp[i];//put the most 14 most recent log entires back into the main screen text array
  }
if (isShowingLog) {//if we are drawing the log
    //eraseDisplay();
      //for (int i=14;i>=0;i--) {
          //nxtDisplayTextLine(i,screenText[14-i]);
      //}
    //draw log
    nxtDisplayTextLine(7,screenText[0]);
    nxtDisplayTextLine(6,screenText[1]);
    nxtDisplayTextLine(5,screenText[2]);
    nxtDisplayTextLine(4,screenText[3]);
    nxtDisplayTextLine(3,screenText[4]);
    nxtDisplayTextLine(2,screenText[5]);
    nxtDisplayTextLine(1,screenText[6]);
    nxtDisplayTextLine(0,screenText[7]);

}
}

void NSLog(int sFormatStrings) {
  string sFormatString = ""+sFormatStrings+"";//make a string from the passed int
//if (mainProgramCounter != 300 && param2 == "1") return;
  //if (!logHasBeenInitiated) {for (int i=0;i<15;i++) screenText[i] = "";logHasBeenInitiated=true;}
  if (isShowingLog) {//if we are going to draw the log
    eraseDisplay();//clear the display
    //draw the log
    nxtDisplayTextLine(7,screenText[0]);
    nxtDisplayTextLine(6,screenText[1]);
    nxtDisplayTextLine(5,screenText[2]);
    nxtDisplayTextLine(4,screenText[3]);
    nxtDisplayTextLine(3,screenText[4]);
    nxtDisplayTextLine(2,screenText[5]);
    nxtDisplayTextLine(1,screenText[6]);
    nxtDisplayTextLine(0,screenText[7]);
  }
  string screenTextTemp[15];//make a temporary array
  for (int i=0;i<15;i++) {//loop through the arrays
    screenTextTemp[i] = screenText[i];//copt the most recent back over
  }
  string text; //declare the string to add
  StringFormat(text, sFormatString);//format it
  screenText[0] = text;//add it to array
  for (int i=0;i<14;i++) {//loop through the array
     screenText[i+1] = screenTextTemp[i];//copt the 14 most recent entries into the main array
  }
if (isShowingLog) { //if we should draw the log
    //eraseDisplay();
      //for (int i=14;i>=0;i--) {
          //nxtDisplayTextLine(i,screenText[14-i]);
      //}
    //draw the log
    nxtDisplayTextLine(7,screenText[0]);
    nxtDisplayTextLine(6,screenText[1]);
    nxtDisplayTextLine(5,screenText[2]);
    nxtDisplayTextLine(4,screenText[3]);
    nxtDisplayTextLine(3,screenText[4]);
    nxtDisplayTextLine(2,screenText[5]);
    nxtDisplayTextLine(1,screenText[6]);
    nxtDisplayTextLine(0,screenText[7]);

}
}
//NSLog only needs one param
void NSLog(string sFormatString) {
//if (mainProgramCounter != 300 && param2 == "1") return;
  //if (!logHasBeenInitiated) {for (int i=0;i<15;i++) screenText[i] = "";logHasBeenInitiated=true;}
  if (isShowingLog) {//if we are showing the log
    eraseDisplay();//erase the display
    //draw the log
    nxtDisplayTextLine(7,screenText[0]);
    nxtDisplayTextLine(6,screenText[1]);
    nxtDisplayTextLine(5,screenText[2]);
    nxtDisplayTextLine(4,screenText[3]);
    nxtDisplayTextLine(3,screenText[4]);
    nxtDisplayTextLine(2,screenText[5]);
    nxtDisplayTextLine(1,screenText[6]);
    nxtDisplayTextLine(0,screenText[7]);
  }

  string screenTextTemp[15];//make temp array
  for (int i=0;i<15;i++) {//loop through array
    screenTextTemp[i] = screenText[i];//restore temp to live
  }
  string text;//decalare string that we will add
  StringFormat(text, sFormatString);//format string to add
  screenText[0] = text;//set string to add to the first element
  for (int i=0;i<14;i++) {//loop through array
     screenText[i+1] = screenTextTemp[i];//restore most recent 14 items
  }
if (isShowingLog) {//should we draw
    //eraseDisplay();
      //for (int i=14;i>=0;i--) {
          //nxtDisplayTextLine(i,screenText[14-i]);
      //}
    //drawing
    nxtDisplayTextLine(7,screenText[0]);
    nxtDisplayTextLine(6,screenText[1]);
    nxtDisplayTextLine(5,screenText[2]);
    nxtDisplayTextLine(4,screenText[3]);
    nxtDisplayTextLine(3,screenText[4]);
    nxtDisplayTextLine(2,screenText[5]);
    nxtDisplayTextLine(1,screenText[6]);
    nxtDisplayTextLine(0,screenText[7]);

}
}

void NSLogClear() {
  logHasBeenInitiated = false;//uninitialize
  eraseDisplay();//clear display
  isShowingLog = false;//dont draw
}
