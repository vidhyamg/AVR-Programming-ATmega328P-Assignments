/*
 * Q2_GPIO.c
 *
 * Created: 6/5/2026 9:59:56 PM
 * Author : deepu
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
#define BUTTON_PIN  PD2
#define RED_LED PB0
#define GREEN_LED PB1

int main(void) 
{
	// 1. Configure Pin Directions
	DDRB |= (1 << RED_LED) | (1 << GREEN_LED); // Set LED pins as outputs
	DDRD &= ~(1 << BUTTON_PIN);                // Set button pin as input
	
	// 2. Enable Internal Pull-up Resistor for the Button
	PORTD |= (1 << BUTTON_PIN);
	
	// 3. Set Initial LED States (Red ON, Green OFF)
	PORTB |= (1 << RED_LED);
	PORTB &= ~(1 << GREEN_LED);
	
	uint8_t button_pressed = 0; // check previous button condition

	while (1) {
		// Check if button is pressed (logic low because of pull-up resistor)
		
		if (!(PIND & (1 << BUTTON_PIN))) 
		{
			 _delay_ms(20);        // debounce delay 
			 
			 // Verify the button is still pressed and wasn't already registered
			 
			 if (!(PIND & (1 << BUTTON_PIN)) && !button_pressed)
			  {
				 
				 // Toggle the LEDs by flipping the bits in the output register
				 PORTB ^= (1 << RED_LED) | (1 << GREEN_LED);
				 
				 // Mark the press as registered so it doesn't repeat while held
				 button_pressed = 1;
			 }
	  } else {
			 // Button is released, reset button_pressed
			 button_pressed = 0;
		    }
		}
}


