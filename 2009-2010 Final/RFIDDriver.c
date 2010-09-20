/*
 * $Id: RFIDDriver.c 1 2010-01-12 16:20:00Z Oliver Graff and Stephen Hall $
 */

/** \file RFIDDriver.c
 * \brief Codatex RFID Driver
 *
 * RFIDDriver.c provides an API for the Codatex RFID Sensor
 *
 * Changelog:
 * - 1.0: Initial Release
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE HAS ONLY BEEN TESTED ON ROBOTC 2.01
 * \author Stephen Hall and Oliver Graff (oliver.graff_at_wheelerschool.org)
 * \date 12 January 2010
 * \version 1.0
 * \example RobotCode.c
 * \example RFID Demo.c
 */



/////////////////////////////////////////////////////////
//Convenience Defines for RFID Information and Data Queries
#define RFID_VERSION 0x00
#define RFID_MANUF 0x08
#define RFID_TYPE 0x10
#define RFID_STATUS 0x32
#define RFID_SERIAL(i) 0xA0+(i)
#define RFID_DATA(i) 0x42+(i)

//RFID has a hard-coded address of 0x04
#define kAddr 0x04

//Stores the current mode of the RFID Sensor
int RFIDMode = -1;
//Possible Values:
// -1 : Mode Unknown
//  81 : Boot Mode (For reading the serial number)
//  83 : Application Firmware Mode (For all other RFID Sensor Functions)



//Message Structures:
//RobotC Cannot pass arrays to functions. Instead, we create information structs which contain the bytes
//Of data to be sent/received.

//This message struct is what is used to hold an I2C Message (Packet), and is what is passed
//To the sendI2CMsg function.
typedef struct {
   byte nMessageSize;
   byte nDeviceAddress;
   byte nLocationPointer;
   byte nData;
} MesStruct;

//This holds the 5 bytes of information in a RFID transponder
typedef struct {
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  byte b5;
} TagStruct;
//This holds 8 bytes of of information. This is returned from RFIDGetInfo()
typedef struct {
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  byte b5;
  byte b6;
  byte b7;
  byte b8;
} InfoStruct;
//This 16 byte structure can hold the RFID sensor's serial number. It is returned from RFIDGetSerial()
typedef struct {
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  byte b5;
  byte b6;
  byte b7;
  byte b8;
  byte b9;
  byte b10;
  byte b11;
  byte b12;
  byte b13;
  byte b14;
  byte b15;
  byte b16;
} SerialStruct;
//Convenience Method for getting the byte at an index in a structure. Assume all structures can be cast as
//SerrialStructs, since these are the longest.
byte RFIDByteForIndexInStruct(int i, SerialStruct &s) {
  i++;
  switch (i) {
    case 1:
    return s.b1;
    case 2:
    return s.b2;
    case 3:
    return s.b3;
    case 4:
    return s.b4;
    case 5:
    return s.b5;
    case 6:
    return s.b6;
    case 7:
    return s.b7;
    case 8:
    return s.b8;
    case 9:
    return s.b9;
    case 10:
    return s.b10;
    case 11:
    return s.b11;
    case 12:
    return s.b12;
    case 13:
    return s.b13;
    case 14:
    return s.b14;
    case 15:
    return s.b15;
    case 16:
    return s.b16;
   default:
    return 0x00;
  }
}
//Convenience method to set a byte value at a given index inside a struct.
//Assume all structs are SerialStructs, as they are the longest used by the sensor.
void RFIDSetByteForIndexInStruct(int i, byte b, SerialStruct &s) {
    i++;
  switch (i) {
    case 1:
    {s.b1=b;}
    case 2:
    {s.b2=b;}
    case 3:
    {s.b3=b;}
    case 4:
    {s.b4=b;}
    case 5:
    {s.b5=b;}
    case 6:
    {s.b6=b;}
    case 7:
    {s.b7=b;}
    case 8:
    {s.b8=b;}
    case 9:
    {s.b9=b;}
    case 10:
    {s.b10=b;}
    case 11:
    {s.b11=b;}
    case 12:
    {s.b12=b;}
    case 13:
    {s.b13=b;}
    case 14:
    {s.b14=b;}
    case 15:
    {s.b15=b;}
    case 16:
    {s.b16=b;}
   default:
  }
}

//The Sensor Needs to be initialized by ROBOTC in order for I2C to work
//9V is needed presumably to power the sensor
void RFIDInit(tSensors port) {
 SetSensorType(port, sensorI2CCustomFastSkipStates9V);
}


//Construct an I2C packet and send it to the sensor on a specific port.
//The Function also ensures the data is sent.
void SendI2CByte(tSensors sensorPort, byte ad,  byte re, byte da) {
  nI2CRetries = 3;
  MesStruct sendBuff;
  sendBuff.nMessageSize = 0x03;
  sendBuff.nDeviceAddress = ad;
  sendBuff.nLocationPointer = re;
  sendBuff.nData = da;
  while(nI2CStatus[sensorPort] == STAT_COMM_PENDING) {wait1Msec(5);}
  sendI2CMsg(sensorPort, sendBuff.nMessageSize, 0);
  while(nI2CStatus[sensorPort] == STAT_COMM_PENDING) {wait1Msec(5);}
}
//Command Functions (Shortcuts for sending commands (Register 0x41) to the RFID Sensor
void RFIDSendDummy(tSensors sensorPort) {
      SendI2CByte(sensorPort, kAddr, 0x00,0x00);
}
void RFIDSendCommand(tSensors sensorPort, ubyte command) {
  if (command == 0x81) {
      if (RFIDMode != 0) {
        RFIDMode = 0;
        SendI2CByte(sensorPort, kAddr, 0x41, command);
      }
  } else if (command == 0x83) {
      if (RFIDMode != 1) {
         RFIDMode = 1;
         SendI2CByte(sensorPort, kAddr, 0x41, command);
      }
  } else {
   SendI2CByte(sensorPort, kAddr, 0x41, command);
  }
}



//Get one Byte from RFID Sensor, given its register
byte RFIDGetByte(tSensors sensorPort, byte address, unsigned byte regist) {
  nI2CRetries = 3;
  RFIDSendDummy(sensorPort);
  byte outBuff[1];
  MesStruct RFIDGetBuff;
  RFIDGetBuff.nMessageSize = 0x02;
  RFIDGetBuff.nDeviceAddress = address;
  RFIDGetBuff.nLocationPointer = regist;
  while(nI2CStatus[sensorPort] == STAT_COMM_PENDING) {wait1Msec(5);}
  sendI2CMsg(sensorPort, RFIDGetBuff.nMessageSize, 1);
  while(nI2CStatus[sensorPort] == STAT_COMM_PENDING) {wait1Msec(5);}
  while(nI2CBytesReady[sensorPort] == 0) {
    wait10Msec(1);
    if (nI2CStatus[sensorPort] == ERR_COMM_BUS_ERR) return 0x00;
  }
  readI2CReply(sensorPort, outBuff, 1);
  return outBuff[0];
}

///Get Info: read 8 bytes from a given register
void RFIDGetInfo(tSensors sensorPort, unsigned byte regist, InfoStruct &infoBytes) {
  nI2CRetries = 3;
  RFIDSendDummy(sensorPort);
  RFIDSendCommand(sensorPort,0x83);
  byte outBuff[8];

   MesStruct RFIDGetBuff;
  RFIDGetBuff.nMessageSize = 0x02;
  RFIDGetBuff.nDeviceAddress = kAddr;
  RFIDGetBuff.nLocationPointer = regist;
  while(nI2CStatus[sensorPort] == STAT_COMM_PENDING) {wait1Msec(5);}
  sendI2CMsg(sensorPort, RFIDGetBuff.nMessageSize, 8);

  while(nI2CStatus[sensorPort] == STAT_COMM_PENDING) {wait1Msec(5);}
  while(nI2CBytesReady[sensorPort] == 0) {
    wait1Msec(1);
    if (nI2CStatus[sensorPort] == ERR_COMM_BUS_ERR) {return;}
  }
  readI2CReply(sensorPort, outBuff, 8);

  for(int i=0;i<8;i++) {RFIDSetByteForIndexInStruct(i, outBuff[i], (SerialStruct)infoBytes);}

}
//Return a string for information
void RFIDGetInfoString(tSensors sensorPort, unsigned byte regist, string &infoString) {
  InfoStruct outBuff;
  RFIDGetInfo(sensorPort, regist, outBuff);
  string s = "";
  for (int i=0;i<8;i++) {
   string ss = "";
   StringFormat(ss, "%c",RFIDByteForIndexInStruct(i,(SerialStruct)outBuff));
   strcat(s, ss);
  }
  infoString = s;
}

//Get the 16 byte serial number by activating the bootloader
void RFIDGetSerial(tSensors thePort, SerialStruct &serialBytes) {
  nI2CRetries = 3;
    RFIDSendDummy(thePort);
  RFIDSendCommand(thePort,0x81);
  byte serialNumber[16];
   for (int i=0;i<16;i++) {
    byte b = RFIDGetByte(thePort, kAddr, RFID_SERIAL(i));
    serialNumber[i] = b;
   }
  for(int i=0;i<16;i++) {RFIDSetByteForIndexInStruct(i, serialNumber[i], serialBytes);}
}

//Return a string for the serial bytes
void RFIDGetSerialString(tSensors thePort, string &serialString) {
 SerialStruct serial;
 RFIDGetSerial(thePort, serial);
   string s = "";
  for (int i=0;i<16;i++) {
   string ss = "";
   StringFormat(ss, "%x",RFIDByteForIndexInStruct(i,serial));
   if (i!= 0) {
    strcat(s,".");
   }
   strcat(s, ss);
  }
  serialString = s;
}

//Get the bytes for a continuous tag read. This function should be used in a while loop with a mild delay
//Approximately 100-200ms works well.
void RFIDGetTagContinuous(tSensors port, TagStruct &tag, bool sound) {
  RFIDSendDummy(port);
  RFIDSendCommand(port,0x83);
  RFIDSendCommand(port, 0x02);
  byte status = RFIDGetByte(port, kAddr, RFID_STATUS);
  if (status == 0) {
    wait1Msec(250);
  }
  ubyte TagArray[5] = {0,0,0,0,0};
  int sum = 0;
  for (int i=0;i<5;i++) {
     ubyte b = RFIDGetByte(port, kAddr, RFID_DATA(i));
      if (b!= 0) {
        TagArray[i] = b;
      }
      sum += TagArray[i];
    }
    if (TagArray[0]!= 255 && TagArray[1]!= 255 && TagArray[2]!= 255 && TagArray[3]!= 255 && TagArray[4]!= 255 && sound == true) {
      PlayImmediateTone(sum*7,10);
    }
   wait1Msec(100);
   for(int i=0;i<5;i++) {RFIDSetByteForIndexInStruct(i, TagArray[i], (SerialStruct)tag);}
   RFIDSendCommand(port,0x00);
}

//Return a string for the continuous tag
void RFIDGetTagContinuousString(tSensors port, string &theString, bool sound) {
  TagStruct tag;
  RFIDGetTagContinuous (port, tag, sound);
    string s = "";
  for (int i=0;i<5;i++) {
   string ss = "";
   StringFormat(ss, "%x",RFIDByteForIndexInStruct(i, (SerialStruct)tag));
   if (i!=0) {
   strcat(s,".");
   }
   strcat(s, ss);
  }
  theString = s;
}

//Read the bytes of a tag in single mode
void RFIDGetTagSingle(tSensors port, TagStruct &tag, bool sound) {
  RFIDSendDummy(port);
  RFIDSendCommand(port,0x83);
  RFIDSendCommand(port, 0x01);
  ubyte TagArray[5] = {0,0,0,0,0};
  wait1Msec(300);
  int sum = 0;
  for (int i=0;i<5;i++) {
     ubyte b = RFIDGetByte(port, kAddr, RFID_DATA(i));
      if (b!= 0) {
        TagArray[i] = b;
      }
      sum += TagArray[i];
    }
    if(sound==true){
    if (TagArray[0]!= 255 || TagArray[1]!= 255 || TagArray[2]!= 255 || TagArray[3]!= 255 || TagArray[4]!= 255) {
      PlayImmediateTone(sum*7,10);
    }}
   wait1Msec(100);
   for(int i=0;i<5;i++) {RFIDSetByteForIndexInStruct(i, TagArray[i], (SerialStruct)tag);}
  RFIDSendCommand(port, 0x00);
}

//Return a string for a single read
void RFIDGetTagSingleString(tSensors port, string &theString, bool sound) {
  TagStruct tag;
  RFIDGetTagSingle(port, tag, sound);
    string s = "";
  for (int i=0;i<5;i++) {
   string ss = "";
   StringFormat(ss, "%x",RFIDByteForIndexInStruct(i, (SerialStruct)tag));
   if (i!=0) {
   strcat(s,".");
   }
   strcat(s, ss);
  }
  theString = s;
}

//This function is to get rid of compiler warnings. Don't call it.
void GetRidOfWarnings() {
  return;
  GetRidOfWarnings();
  RFIDInit(S1);
  string s;
  RFIDGetInfoString(S1,0x00,s);
  RFIDGetSerialString(S1,s);
  TagStruct t;
  RFIDGetTagContinuous(S1,t,true);
  RFIDGetTagSingleString(S1,s,true);
  RFIDGetTagContinuousString(S1,s,true);
}
