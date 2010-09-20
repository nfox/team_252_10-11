#pragma config(Sensor, S1,     HTSMUX,              sensorI2CMindsensorsCompass)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTPB-SMUX-test2.c 25 2010-05-11 13:18:02Z xander $
 */

/**
 * HTPB-driver.h provides an API for the HiTechnic Protoboard.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 25 November 2009
 * version 0.2
 */

#include "drivers/common.h"
#include "drivers/HTPB-driver.h"

task main() {
  int _chVal = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Proto");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and HTPB to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  // Before using the SMUX, you need to initialise the driver
  HTSMUXinit();

  // Tell the SMUX to scan its ports for connected sensors
  HTSMUXscanPorts(HTSMUX);

  PlaySound(soundBeepBeep);
  while(bSoundActive);

  eraseDisplay();

  while(true) {
    eraseDisplay();
    // get the value for ADC channel 0, we want a 10 bit answer
    _chVal = HTPBreadADC(msensor_S1_1, 0, 10);
    nxtDisplayTextLine(4, "A0: %d", _chVal);

    wait1Msec(10);
  }
}

/*
 * $Id: HTPB-SMUX-test2.c 25 2010-05-11 13:18:02Z xander $
 */