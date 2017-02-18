// filename ******** LCD.c ************** 
// Lab 4 Spring 2017
// Matt Owens & Rebecca Ho
// 2/17/17

#include <stdint.h>
#include "ST7735.h"
#include "Timer.h"
#include "LCD.h"


struct TimeSet {
	int16_t x;
	int16_t y;
	char num;
	int16_t fontColor;
	int16_t backColor;
	uint8_t size;
};
typedef struct TimeSet TimeSet;


TimeSet timeSetting[6] = {{5,15,'0',ST7735_WHITE,ST7735_BLACK,3},{25,15,'1',ST7735_WHITE,ST7735_BLACK,3},
		{50,15,'0',ST7735_WHITE,ST7735_BLACK,3},{75,15,'0',ST7735_WHITE,ST7735_BLACK,3},
		{100,15,'0',ST7735_WHITE,ST7735_BLACK,3},{125,15,'0',ST7735_WHITE,ST7735_BLACK,3}};
		// index 0 is hour tens, 1 is hour ones, 2 is minute tens, 3 is minute ones, 4 is sec tens, 5 is sec tens

void DrawTime() {
	ST7735_DrawChar(35, 0, ':', ST7735_WHITE, ST7735_BLACK, 3);
	TimeSet current;
	for(int i = 0; i < 4; i++) { // iterate through timeSettings
		ST7735_DrawChar(current.x, current.y, current.num, current.fontColor, current.backColor, current.size);
	}
}		

void DrawDigit(TimeIndex s) {
	if(s > 5) { return; } // exceeds timeSetting array
	
	ST7735_DrawChar(timeSetting[s].x, timeSetting[s].y, timeSetting[s].num, timeSetting[s].fontColor, 
		timeSetting[s].backColor, timeSetting[s].size);
	
}

void DisplayHour(int32_t h){
	//display hour on lcd
	
	if(h == 10){
		timeSetting[tensH].num = '1';
		DrawDigit(tensH);
	} else if(h == 20) {
		timeSetting[tensH].num = '2';
		DrawDigit(tensH);		
	} else if(h == 1){
		timeSetting[tensH].num = '0';
		DrawDigit(tensH);
}
	h = h%10;
	timeSetting[onesH].num = h + '0';
	DrawDigit(onesH);
}

void DisplayMinute(int32_t m){
	//display minute on lcd
	
	if(m % 10 == 0){ // minutes is multiple of 10
		timeSetting[onesM].num = '0';
		timeSetting[tensM].num = m/10 + '0';
		DrawDigit(tensM);
		DrawDigit(onesM);		
	}
	else{
		m = m%10;
		timeSetting[onesM].num = m + '0';
		DrawDigit(onesM);
	}	
}

void DisplaySecond(int32_t s){
	//display second on lcd
	
	if(s % 10 == 0){ // seconds is multiple of 10
		timeSetting[onesS].num = '0';
		timeSetting[tensS].num = s/10 + '0';
		DrawDigit(tensS);
		DrawDigit(onesS);		
	}
	else{
		s = s%10;
		timeSetting[onesS].num = s + '0';
		DrawDigit(onesS);
	}	
}
