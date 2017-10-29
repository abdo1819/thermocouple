/**
 * \file timer.h
 *
 * \brief Timer driver
 *
 * (C)2014 OrcaLight Ltd. All rights reserved
 *
 */

extern volatile unsigned int tempUpdateTimer; /*Controls temperature readings*/
extern volatile unsigned int stageTimer; /*Times each reflow stage*/

void timerInit(void);
