// filename ******** Timer.h ************** 
// Lab 4 Spring 2017
// Matt Owens & Rebecca Ho
// 2/17/17

//#include <stdint.h>
#include <stdbool.h>

//------------Timer0A_Init1HzInt------------
// Initializing of Timer with 1 Hz interrupts
// Input: none
// Output: none
void Timer0A_Init1HzInt(void);

//------------Timer0A_Handler------------
// Handler for Timer0A interrupts
// Input: none
// Output: none
void Timer0A_Handler(void);

//------------GetHour----------------------
// Returns the current hour of the timer
// Input: none
// Output: The current hour of the timer
uint32_t GetHour(void);

//------------GetHour----------------------
// Returns the current minute of the timer
// Input: none
// Output: The current minute of the timer
uint32_t GetMinute(void);

//------------GetSecond----------------------
// Returns the current second of the timer
// Input: none
// Output: The current second of the timer
uint32_t GetSecond(void);

//------------SetTime----------------------
// Set the current time 
// Input: hour, minute, second values to set
// Output: none
void SetTime(int32_t, int32_t, int32_t);


