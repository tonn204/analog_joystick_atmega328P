/*
 * main.c
 *
 *  Created on: 14 Jun 2022
 *      Author: Laptop1
 */

#include <avr/io.h>
#include <util/delay.h>

#include "HD44780.h"

char buffer[33];
char buffer2[33];

int main()
{
	DDRB |= (1 << PB1);

	LCD_Initalize();

	ADMUX |= /*(1 << REFS1)*/  (1<< REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	while(1)
	{
		// For Y value
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		itoa(ADCW, buffer2, 10);

		// For X value
		ADMUX |= (1 << MUX0);
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		ADMUX &= ~(1 << MUX0);
		itoa(ADCW, buffer, 10);

		LCD_Clear();
		LCD_GoTo(0, 0);
		LCD_WriteText("X:");
		LCD_GoTo(3, 0);
		LCD_WriteText(buffer);
		LCD_GoTo(0, 1);
		LCD_WriteText("Y:");
		LCD_GoTo(3, 1);
		LCD_WriteText(buffer2);
		_delay_ms(200);
	}
}
