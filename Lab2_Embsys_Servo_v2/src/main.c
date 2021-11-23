#include <asf.h>
#include <stdio.h>
#include <ioport.h>
#include <board.h>

void PWM_Init(void)
{
	/* Set output */
	PORTC.DIR |= PIN0_bm;

	/* Set Register */
	TCC0.CTRLA = (PIN2_bm) | (PIN0_bm);
	TCC0.CTRLB = (PIN4_bm) | (PIN2_bm) | (PIN1_bm);
	
	/* Set Period */
	TCC0.PER = 16000;
}


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	PWM_Init();
	#define IOPORT_PIN_LED LED0_GPIO
	#define IOPORT_PIN_BTN GPIO_PUSH_BUTTON_0
	while(1)
	{
		
		if (ioport_pin_is_low(IOPORT_PIN_BTN)) {
			ioport_set_pin_low(IOPORT_PIN_LED);
			ioport_set_pin_high(LED1_GPIO); // Button pressed
			TCC0.CCA = 2000;
			}else{
			ioport_set_pin_high(IOPORT_PIN_LED); // Button released
			ioport_set_pin_low(LED1_GPIO);
			TCC0.CCA = 8000;
		}
	}

	/* Insert application code here, after the board has been initialized. */
}