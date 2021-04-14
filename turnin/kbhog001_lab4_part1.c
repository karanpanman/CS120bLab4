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

enum LA_States { Start, S1, Wait, Finish } State;

void LED_latch()
{
 switch(State) {
   case Start:
	if (PINA == 0x00){
		State = Wait;
	}
	else {
		State = S1;
	}
	break;

   case S1:
	State = Finish;
	break;
  
   case Finish:
	if (PINA == 0x01){
		State = Finish;
	}
	else{ 
		State = Wait;
	}

   case Wait:
	if (PINA == 0x00){
		State = Wait;
	}
	else{
		State = S1;
	}
	break;

   default:
	State = Wait;
	break;
  } //transitions

  switch(State){
   case Start:
	PORTB = 0x01;
	break;

   case S1:
	if (PORTB == 0x01){
		PORTB = 0x02;
	}
	else {
		PORTB = 0x01;
	}
	break;
   
   case Wait:
	break;

   case Finish:
	break;

   default:
	break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	PORTB = 0x01;	
	State = Start;
    /* Insert your solution below */

    while (1) {
	LED_latch();
    }
    return 1;
}
