#pragma systemFile //no unused func warnings
/*
 * $Id: RFID_Implementation_Example.c 1 2010-01-12 16:12:0Z Oliver Graff Stephen Hall $
 */

/** \file RFID_Implementation_Example.c
 * \brief Example Usage of RFID Sensor
 *
 * RFID_Implementation_Example.c provides an example usage technique for the Codatex RFID Sensor.
 *
 * Changelog:
 * - 1.0: Initial Release
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE HAS ONLY BEEN TESTED ON ROBOTC 2.01.
 * \author Stephen Hall and Oliver Graff (oliver.graff_at_wheelerschool.org)
 * \date 12 January 2010
 * \version 1.0
 */


#include "RFIDDriver.c"
#define kPort S1
typedef int RFIDTag;
#define TAG_UNKNOWN -1
#define TAG_1 1
#define TAG_2 2
#define TAG_3 3
#define TAG_4 4
#define TAG_5 5
#define TAG_6 6
#define TAG_7 7
#define TAG_8 8
#define TAG_9 9
#define TAG_10 10
#define TAG_11 11



RFIDTag ReadNewTagS(){
  string s; //make a string to read the tag to
  RFIDGetTagSingleString(kPort,s,false);//read it to string
  //identify which tag number it is
  if (s == "0.0.0.0.0") return TAG_UNKNOWN;
  if (s == "50.0.4a.82.10") return TAG_1;
  if (s == "50.0.49.58.1b") return TAG_2;
  if (s == "50.0.54.3c.28") return TAG_3;
  if (s == "50.0.54.11.45") return TAG_4;
  if (s == "50.0.53.fd.d6") return TAG_5;
  if (s == "50.0.52.f6.7c") return TAG_6;
  if (s == "50.0.50.ca.fa") return TAG_7;


  wait1Msec(100);
  return TAG_UNKNOWN;
}

RFIDTag ReadNewTag() {
  string s;//string to read tag to
  for(int i=0;i<=10; i++){//do it continuously
    RFIDGetTagContinuousString(kPort,s,false);//start read
    wait10Msec(50);//give time to read
    if(s!="0.0.0.0.0") break;//once we read a tag
  }
  //return which tag we read
  if (s == "0.0.0.0.0") return TAG_UNKNOWN;
  if (s == "50.0.4a.82.10") return TAG_1;
  if (s == "50.0.49.58.1b") return TAG_2;
  if (s == "50.0.54.3c.28") return TAG_3;
  if (s == "50.0.54.11.45") return TAG_4;
  if (s == "50.0.53.fd.d6") return TAG_5;
  if (s == "50.0.52.f6.7c") return TAG_6;
  if (s == "50.0.50.ca.fa") return TAG_7;
  if (s == "50.0.50.d6.e6") return TAG_8;
  if (s == "50.0.51.7b.8e") return TAG_9;
  if (s == "50.0.50.4e.1e") return TAG_10;
  if (s == "50.0.50.f6.6")  return TAG_11;
  return TAG_UNKNOWN;
}
/*task main(){
 RFIDInit(S1);
 while(true){
   RFIDTag n = ReadNewTag();
   nxtDisplayBigTextLine(3,""+n+"");
 }
}*/
