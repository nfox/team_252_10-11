/*!@addtogroup mindsensors
 * @{
 * @defgroup msdist DIST-Nx Sensor
 * DIST-Nx Sensor
 * @{
 */

/*
 * $Id: MSDIST-driver.h 29 2010-06-25 12:55:41Z xander $
 */

#ifndef __MSDIST_H__
#define __MSDIST_H__
/** \file MSDIST-driver.h
 * \brief Mindsensors DIST-Nx driver
 *
 * MSDIST-driver.h provides an API for the Mindsensors DIST-Nx sensor
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 28 November 2009
 * \version 0.2
 * \example MSDIST-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

#define MSDIST_I2C_ADDR   0x02  /*!< MSDIST I2C device address */

#define MSDIST_CMD        0x41  /*!< MSDIST command register */

#define MSDIST_DIST       0x42  /*!< MSDIST distance data */
#define MSDIST_VOLT       0x44  /*!< MSDIST voltage data */
#define MSDIST_MOD_TYPE   0x50  /*!< MSDIST Sharp module type */
#define MSDIST_MINDIST    0x52  /*!< MSDIST minimum distance in mm */
#define MSDIST_MAXDIST    0x54  /*!< MSDIST maximum distance in mm */

#define MSDIST_GP2D12     0x31  /*!< Sharp IR module GP2D12 */
#define MSDIST_GP2D120    0x32  /*!< Sharp IR module GP2D120 */
#define MSDIST_GP2YA21    0x33  /*!< Sharp IR module GP2YA21 */
#define MSDIST_GP2YA02    0x34  /*!< Sharp IR module GP2YA02 */
#define MSDIST_CUSTOM     0x35  /*!< Custom IR module */

int MSDISTreadDist(tSensors link);
int MSDISTreadVoltage(tSensors link);
int MSDISTreadMinDist(tSensors link);
int MSDISTreadMaxDist(tSensors link);
int MSDISTreadModuleType(tSensors link);
bool MSDISTsendCmd(tSensors link, byte command);

tByteArray MSDIST_I2CRequest;       /*!< Array to hold I2C command data */
tByteArray MSDIST_I2CReply;         /*!< Array to hold I2C reply data */


/**
 * Read the distance from the sensor
 * @param link the sensor port number
 * @return distance to object or -1 if an error occurred
 */
int MSDISTreadDist(tSensors link) {
  memset(MSDIST_I2CRequest, 0, sizeof(tByteArray));

  MSDIST_I2CRequest.arr[0] = 2;               // Number of bytes in I2C command
  MSDIST_I2CRequest.arr[1] = MSDIST_I2C_ADDR; // I2C address of accel sensor
  MSDIST_I2CRequest.arr[2] = MSDIST_DIST;     // Set write address to sensor mode register

  if (!writeI2C(link, MSDIST_I2CRequest, 2))
    return -1;

  if (!readI2C(link, MSDIST_I2CReply, 2))
    return -1;

  return (0x00FF & MSDIST_I2CReply.arr[0]) + ((0x00FF & MSDIST_I2CReply.arr[1]) <<8);
}


/**
 * Read tilt data from the sensor
 * @param link the sensor port number
 * @return voltage reading from IR Sensor -1 if an error occurred
 */
int MSDISTreadVoltage(tSensors link) {
  memset(MSDIST_I2CRequest, 0, sizeof(tByteArray));

  MSDIST_I2CRequest.arr[0] = 2;               // Number of bytes in I2C command
  MSDIST_I2CRequest.arr[1] = MSDIST_I2C_ADDR; // I2C address of accel sensor
  MSDIST_I2CRequest.arr[2] = MSDIST_VOLT;     // Set write address to sensor mode register

  if (!writeI2C(link, MSDIST_I2CRequest, 2))
    return -1;

  if (!readI2C(link, MSDIST_I2CReply, 2))
    return -1;

  // Each result is made up of two bytes.
  return (0x00FF & MSDIST_I2CReply.arr[0]) + ((0x00FF & MSDIST_I2CReply.arr[1]) <<8);
}


/**
 * Read minumum measuring distance from the sensor
 * @param link the sensor port number
 * @return minumum measuring distance from the sensor -1 if an error occurred
 */
int MSDISTreadMinDist(tSensors link) {
  memset(MSDIST_I2CRequest, 0, sizeof(tByteArray));

  MSDIST_I2CRequest.arr[0] = 2;               // Number of bytes in I2C command
  MSDIST_I2CRequest.arr[1] = MSDIST_I2C_ADDR; // I2C address of accel sensor
  MSDIST_I2CRequest.arr[2] = MSDIST_MINDIST;  // Set write address to sensor mode register

  if (!writeI2C(link, MSDIST_I2CRequest, 2))
    return -1;

  if (!readI2C(link, MSDIST_I2CReply, 2))
    return -1;

  // Each result is made up of two bytes.
  return (0x00FF & MSDIST_I2CReply.arr[0]) + ((0x00FF & MSDIST_I2CReply.arr[1]) <<8);
}


/**
 * Read maximum measuring distance from the sensor
 * @param link the sensor port number
 * @return maximum measuring distance from the sensor -1 if an error occurred
 */
int MSDISTreadMaxDist(tSensors link) {
  memset(MSDIST_I2CRequest, 0, sizeof(tByteArray));

  MSDIST_I2CRequest.arr[0] = 2;               // Number of bytes in I2C command
  MSDIST_I2CRequest.arr[1] = MSDIST_I2C_ADDR; // I2C address of accel sensor
  MSDIST_I2CRequest.arr[2] = MSDIST_MAXDIST;     // Set write address to sensor mode register

  if (!writeI2C(link, MSDIST_I2CRequest, 2))
    return -1;

  if (!readI2C(link, MSDIST_I2CReply, 2))
    return -1;

  // Each result is made up of two bytes.
  return (0x00FF & MSDIST_I2CReply.arr[0]) + ((0x00FF & MSDIST_I2CReply.arr[1]) <<8);
}


/**
 * Read Sharp IR module type from the sensor
 * @param link the sensor port number
 * @return Sharp IR module type from the sensor -1 if an error occurred
 */
int MSDISTreadModuleType(tSensors link) {
  memset(MSDIST_I2CRequest, 0, sizeof(tByteArray));

  MSDIST_I2CRequest.arr[0] = 2;               // Number of bytes in I2C command
  MSDIST_I2CRequest.arr[1] = MSDIST_I2C_ADDR; // I2C address of accel sensor
  MSDIST_I2CRequest.arr[2] = MSDIST_MOD_TYPE; // Set write address to sensor mode register

  if (!writeI2C(link, MSDIST_I2CRequest, 1))
    return -1;

  if (!readI2C(link, MSDIST_I2CReply, 1))
    return -1;

  return 0x00FF & MSDIST_I2CReply.arr[0];
}


/**
 * Send a command to the sensor
 * @param link the sensor port number
 * @param command the command to be sent
 * @return true if no error occured, false if it did
 */
bool MSDISTsendCmd(tSensors link, byte command) {
  memset(MSDIST_I2CRequest, 0, sizeof(tByteArray));

  MSDIST_I2CRequest.arr[0] = 3;               // Number of bytes in I2C command
  MSDIST_I2CRequest.arr[1] = MSDIST_I2C_ADDR; // I2C address of accel sensor
  MSDIST_I2CRequest.arr[2] = MSDIST_CMD;      // Set write address to sensor mode register
  MSDIST_I2CRequest.arr[3] = command;         // Command to be sent to the sensor

  return writeI2C(link, MSDIST_I2CRequest, 0);
}


#endif //__MSDIST_H__

/*
 * $Id: MSDIST-driver.h 29 2010-06-25 12:55:41Z xander $
 */
/* @} */
/* @} */
