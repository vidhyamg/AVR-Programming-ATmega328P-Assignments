/*
 * Q14_ADC_motot driver.c
 *program to regulate the rotational speed of a DC motor by mapping an analog input signal to a Pulse Width Modulation (PWM) output.
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

//-------------------------------------------------
// ADC Initialization
//-------------------------------------------------
void ADC_Init(void)
{
	ADMUX = (1 << REFS0);                  // AVCC reference, ADC0 selected
	ADCSRA = (1 << ADEN) |                 // Enable ADC
	(1 << ADPS2) |
	(1 << ADPS1) |
	(1 << ADPS0);                 // Prescaler = 128
}

//-------------------------------------------------
// Read ADC Channel 0 (10-bit)
//-------------------------------------------------
uint16_t ADC_Read(void)
{
	ADMUX = (ADMUX & 0xF0);                // Select ADC0

	ADCSRA |= (1 << ADSC);                 // Start conversion

	while (ADCSRA & (1 << ADSC));          // Wait until complete

	return ADC;
}

//-------------------------------------------------
// PWM Initialization (Timer0 Fast PWM)
// Output: OC0A -> PD6
//-------------------------------------------------
void PWM_Init(void)
{
	DDRD |= (1 << PD6);                    // PD6 as output

	TCCR0A = (1 << COM0A1) |               // Non-inverting mode
	(1 << WGM01) |
	(1 << WGM00);                 // Fast PWM

	TCCR0B = (1 << CS01) |
	(1 << CS00);                  // Prescaler = 64

	OCR0A = 0;
}

//-------------------------------------------------
// Convert 10-bit ADC value to 8-bit PWM value
//-------------------------------------------------
uint8_t convert_ADC_to_PWM(uint16_t adcValue)
{
	return (adcValue >> 2);                // 0-1023 ? 0-255
}

//-------------------------------------------------
// Main Program
//-------------------------------------------------
int main(void)
{
	uint16_t adcValue;
	uint8_t pwmValue;

	ADC_Init();
	PWM_Init();

	while (1)
	{
		adcValue = ADC_Read();             // Read potentiometer

		pwmValue = convert_ADC_to_PWM(adcValue);

		OCR0A = pwmValue;                  // Update PWM duty cycle

		_delay_ms(10);
	}
}
