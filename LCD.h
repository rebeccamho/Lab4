// filename ******** LCD.h ************** 
// Lab 4 Spring 2017
// Matt Owens & Rebecca Ho
// 2/17/17


typedef enum  { tensH = 0,
								onesH = 1,
								tensM = 2,
								onesM = 3,
								tensS = 4,
								onesS = 5} TimeIndex;		

void DrawTime(void);

void DrawDigit(TimeIndex);

void DisplayHour(int32_t);

void DisplayMinute(int32_t);					

void DisplaySecond(int32_t);	

								