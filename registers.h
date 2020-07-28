#ifndef REGISTERS_H_INCLUDED
#define REGISTERS_H_INCLUDED

#include <pic16f877a.h>

/*
 * PORTx registers
 */

#define PORTA_DATA 	(PORTA)
#define PORTA_DIR  	(TRISA)


#define PORTB_DATA 	(PORTB)
#define PORTB_DIR  	(TRISB)

#define PORTC_DATA 	(PORTC)
#define PORTC_DIR  	(TRISC)


#define PORTD_DATA 	(PORTD)
#define PORTD_DIR  	(TRISD)

#define PORTE_DATA  (PORTE)
#define PORTE_DIR  	(TRISE)


#endif // REGISTERS_H_INCLUDED
