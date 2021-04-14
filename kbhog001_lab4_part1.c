/*	Author: Karan Bhogal
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LA_States { LA_SMStart, LA_s1, LA_Wait } LA_State;

void LED_latch()
{
 switch(LA_State) {
   case LA_SMStart:
	//PORTB = 0x01;
	if (PINA == 0x00){
		LA_State = LA_SMStart;
	}
	else if (PINA == 0x01) {
		LA_State = LA_s1;
	}
	break;

   case LA_s1:
	//PORTB = 0x02;
	LA_State = LA_Wait;
	break;

   case LA_Wait:
	if (PINA == 0x00){
		LA_State = LA_Wait;
	}
	else if (PINA == 0x01){
		LA_State = LA_SMStart;
	}
	break;

   default:
	LA_State = LA_SMStart;
	break;
  } //transitions

  switch(LA_State){
   case LA_SMStart:
	PORTB = 0x01;
	break;

   case LA_s1:
	PORTB = 0x02;
	break;
   
   case LA_Wait:
	break;

   default:
	break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	
	LA_State = LA_SMStart;
    /* Insert your solution below */
    while (1) {
	LED_latch();
    }
    return 1;
}
