#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

#define clock_status 0
#define alarm_status 1
#define timer_status 2
#define stopwatch_status 3


unsigned char status = 0;
signed char edit_status = -1;

void showClock();
void showAlarm();
void showTimer();
void showStopwatch();
void checkAlarm();
void read_rtc();
void activate_buzzer();

int main() {
  InitLCD(0);
  GICR |= (1<<INT0) | (INT1);
  MCUCR |= (1<<ISC11) | (1<<ISC01);
  sei();
  while(1){
    if(status == clock_status){
      showClock();
    } else if (status == alarm_status) {
      showAlarm();
    } else if (status == timer_status) {
      showTimer();
    } else if (status == stopwatch_status) {
      showStopwatch();
    }
    if (checkAlarm()){
      //buzz
    }
  }
  return 0;
}
ISR(INT0_VECT) {
  status = (status + 1) % 4;
}
ISR(INT1_VECT) {
  if(status == clock_status){
    //edit clock
  } else if(status == alarm_status) {
    //edit alarm
  } else if(status == timer_status) {
    //edit timer
  } else if(status == stopwatch_status) {
    //edit timer
  }
}
