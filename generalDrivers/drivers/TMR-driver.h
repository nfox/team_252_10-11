/*!@addtogroup other
 * @{
 * @defgroup tmr Timer Library
 * Timer Library
 * @{
 */

/*
 * $Id: TMR-driver.h 29 2010-06-25 12:55:41Z xander $
 */

#ifndef __TMR_H__
#define __TMR_H__
/** \file TMR-driver.h
 * \brief Additional _timers for ROBOTC.
 *
 * TMR-driver.h provides additional timers for ROBOTC.  Please note that there is no
 * roll-over checking done at all.  That means that if the program runs for more than
 * around 596 hours, it will roll over and weird stuff will happen.
 *
 * The default number of timers is 10, but this can be changed by defining MAX_TIMERS
 * before this driver is included.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Removed task and cleaned up the code some more
 *
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 18 May 2010
 * \version 0.2
 * \example TMR-test1.c
 */

#pragma systemFile

#ifndef MAX_TIMERS
#define MAX_TIMERS 10  /*!< Maximum number of _timers */
#endif


/*!< Struct for timer data */
typedef struct {
  long startTime;
  long duration;
} typeTMR;

typeTMR _timers[MAX_TIMERS]; /*!< Array to hold timer data */

// Prototypes
int TMRnewTimer();
bool TMRisExpired(int timerIdx);
void TMRreset(int timerIdx);
void TMRreset(int timerIdx, long duration);
void TMRsetup(int timerIdx, long duration);

/**
 * Create a new timer.  It's an index to the next available timer in the array of
 * timer structs.
 * @return the first available slot in the timer object array or -1 if all slots
 *         have been used.  Increase the MAX_TIMERS variable in this case.
 */
int TMRnewTimer() {
  static int _tmrIdx = -1;
  if (_tmrIdx < (MAX_TIMERS - 2))
    return _tmrIdx++;
  else
    return -1;
}


/**
 * Check if the timer has expired.
 * @param timerIdx the timer to be checked.
 * @return true if the timer has expired, false if it hasn't.
 */
bool TMRisExpired(int timerIdx) {
  if (_timers[timerIdx].startTime < 0) {
    return true;
  } else {
    return (bool)((nPgmTime - _timers[timerIdx].startTime) > _timers[timerIdx].duration);
  }
}


/**
 * Reset the timer, will also mark "expired" flag as false.\n
 * This function will also check if the TMRtask is running and
 * start it up if this isn't the case.
 * @param timerIdx the timer to be checked.
 */
void TMRreset(int timerIdx) {
	_timers[timerIdx].startTime = nPgmTime;
}


/**
 * Reset the timer, will also mark "expired" flag as false.
 * @param timerIdx the timer to be checked.
 * @param duration the amount of time the timer should run for before expiring.
 */
void TMRreset(int timerIdx, long duration) {
  hogCPU();
  _timers[timerIdx].duration = duration;
	_timers[timerIdx].startTime = nPgmTime;
	releaseCPU();
}


/**
 * Cause the timer to expire.
 * @param timerIdx the timer to be expired.
 */
void TMRexpire(int timerIdx) {
  _timers[timerIdx].startTime = -1;
}


/**
 * Configure the duration of the timer.
 * @param timerIdx the timer to be checked.
 * @param duration the amount of time the timer should run for before expiring.
 */
void TMRsetup(int timerIdx, long duration) {
  _timers[timerIdx].duration = duration;
}

#endif // __TMR_H__

/*
 * $Id: TMR-driver.h 29 2010-06-25 12:55:41Z xander $
 */
/* @} */
/* @} */
