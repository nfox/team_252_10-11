/*!@addtogroup Lego
 * @{
 * @defgroup legous Ultrasonic Sensor
 * Ultrasonic Sensor
 * @{
 */

/*
 * $Id: LEGOUS-driver.h 29 2010-06-25 12:55:41Z xander $
 */

#ifndef __LEGOUS_H__
#define __LEGOUS_H__
/** \file LEGOUS-driver.h
 * \brief SMUX driver for the Lego US sensor.
 *
 * LEGOUS-driver.h provides an API for the Lego US driver.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 28 June 2009
 * \version 0.1
 * \example LEGOUS-SMUX-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

int USreadDist(tMUXSensor muxsensor);

tByteArray LEGOUS_SMUXData;      /*!< Array to hold SMUX data */


/**
 * Get the distance value from the sensor
 * @param muxsensor the SMUX sensor port number
 * @return distance from the sensor or 255 if no valid range has been specified.
 */
int USreadDist(tMUXSensor muxsensor) {
	memset(LEGOUS_SMUXData, 0, sizeof(tByteArray));

  if (smuxData[SPORT(muxsensor)].sensor[MPORT(muxsensor)] != HTSMUXLegoUS)
    return 255;

  if (!HTSMUXreadPort((tSensors)SPORT(muxsensor), MPORT(muxsensor), LEGOUS_SMUXData, 1, 0)) {
    return 255;
  }

  return ubyteToInt(LEGOUS_SMUXData.arr[0]);
}
#endif // __LEGOSNR_H__

/*
 * $Id: LEGOUS-driver.h 29 2010-06-25 12:55:41Z xander $
 */
/* @} */
/* @} */
