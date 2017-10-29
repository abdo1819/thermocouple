/**
 * \file pwm.h
 *
 * \brief PWM driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */

void pwmInit(void);
void pwmSet(unsigned char channel, unsigned int value);

#define PWM_MAX 0x00FF
