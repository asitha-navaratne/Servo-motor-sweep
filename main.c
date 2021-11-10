#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void PORT_INIT(void);
void TIMER_INIT(void);

int main(void){
	PORT_INIT();
	TIMER_INIT();
	
	while(1){
		for(uint8_t i=0;i<180;i++){
			OCR1A = 1000 + 24*i;				///< Set OCR1A with values mapped to generate PWM signals corresponding to 0 to 180 degrees.
			_delay_ms(20);
		}
		for(uint8_t i=180;i>0;i--){
			OCR1A = 1000 + 24*i;
			_delay_ms(20);
		}
	}
}

/*!
 *	@brief Initialize Ports.
 */

void PORT_INIT(void){
	DDRD |= (1<<PD5);						///< Set OC1A as output to generate PWM signal.
}

/*!
 *	@brief Initialize timer/counter1 to generate a 50 Hz Fast PWM signal at OC1A.
 */

void TIMER_INIT(void){
	TCCR1A = (1<<COM1A1)|(1<<WGM11);				///< Select Fast PWM mode with ICR1 as TOP. Clear OC1A on compare match and Set OC1A at BOTTOM (non-inverting mode).
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);			///< Select Fast PWM mode with ICR1 as TOP and set prescalar value of 8.
	ICR1 = 19999;							///< Set TOP value to determine frequency of the PWM signal.
}
