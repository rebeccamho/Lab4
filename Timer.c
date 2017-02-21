// filename ******** Timer.c ************** 
// Lab 4 Spring 2017
// Matt Owens & Rebecca Ho
// 2/17/17

#include <stdint.h>
#include "Timer.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include "LCD.h"
#include "LED.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

int32_t second = 0;
int32_t minute = 0;
int32_t hour = 0;
bool updateM = false;
bool updateH = false;
bool setting = false;

// This debug function initializes Timer0A to request interrupts
// at a 100 Hz frequency.  It is similar to FreqMeasure.c.
void Timer0A_Init1HzInt(void){
  volatile uint32_t delay;
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = 49999999;         // start value for 1 Hz interrupts 79999999
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
}


void Timer0A_Handler(void){
	LED_BlueToggle();
	if(setting) { return; }
	
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
	second++;
	updateM = false;
	updateH = false;
	if(second == 60) { // reached end of minute
	//if(second == 1) { // reached end of minute
		minute++;
		updateM = true;
		second = 0;
		if(minute == 60) { // reached end of hour
			minute = 0;
			hour++;
			updateH = true;
			if(hour == 13) { // reached end of 12-hr interval
				hour = 1;
			}
		}
	}
	
	DisplaySecond(second);
	if(updateM) { DisplayMinute(minute); }
	if(updateH) { DisplayHour(hour); }
}

uint32_t GetHour(){
	return hour;
}

uint32_t GetMinute(){
	return minute;
}

uint32_t GetSecond(){
	return second;
}


void SetTime(int32_t h, int32_t m, int32_t s) {
	setting = true;
	hour = h;
	minute = m;
	second = s;
	DisplaySecond(second);
	DisplayMinute(minute);
	DisplayHour(hour);
	setting = false;
}

