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

enum LA_States { Start, Wait, Check, S1, Lock } State;

void LED_latch()
{
 switch(State) {
   case Start:

	if (PINA == 0x80){
		State = Lock;
	}
	else if (PINA == 0x04) {
		State = Wait;	
	}
	else {
		State = Start;
	}
	break;
  
   case Lock:
	State = Start;
	break;

   case Wait:
	if (PINA == 0x04){
		State = Wait;
	}
	else if (PINA == 0x80){
                State = Lock;
        }
	else if (PINA == 0x00){
		State = Check;
	}
	else {
		State = Start;
	}
	break;

   case Check:
	if (PINA == 0x02){
                State = S1;
        }
	else if (PINA == 0x80){
                State = Lock;
        }
        else if (PINA == 0x00){
                State = Check;
        }
	else {
		State = Start;
	}
	break;

   case S1:
	 if (PINA == 0x80){
                State = Lock;
        }
	else {
		State = Start;
	}
	break;

   default:
	State = Start;
	break;
  } //transitions

  switch(State){
   case Start:
	break;

   case Lock:
	PORTB = 0x00;
	break;

   case Wait:
	break;

   case Check:
	break;
   
   case S1:
	PORTB = 0x01;
	break;

   default:
	break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	PORTB = 0x00;	
	State = Start;
    /* Insert your solution below */

    while (1) {
	LED_latch();
    }
    return 1;
}
