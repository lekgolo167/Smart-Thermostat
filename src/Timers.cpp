#include "Timers.hpp"

void TC4_start_timer() {
	TC4->COUNT32.CTRLA.reg |= TC_CTRLA_ENABLE; //set the CTRLA register
	while (TC4_syncing()); //wait until snyc'd
}

void TC4_stop_timer() {
	TC4->COUNT32.CTRLA.reg &= ~TC_CTRLA_ENABLE;
	while (TC4_syncing());
}

void TC4_reset() {
	TC4->COUNT32.CTRLA.reg = TC_CTRLA_SWRST;
  while (TC4_syncing());
  while (TC4->COUNT32.CTRLA.bit.SWRST);
}

bool TC4_syncing() {
	return TC4->COUNT32.STATUS.reg & TC_STATUS_SYNCBUSY;
}

void TC4_configure(uint32_t sample_period_seconds, uint8_t priority) {
	// select the generic clock generator used as source to the generic clock multiplexer
	GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5)) ;
	while (GCLK->STATUS.bit.SYNCBUSY);

	TC4_reset(); //reset TC4

	// Set Timer counter 5 Mode to 16 bits, it will become a 16bit counter ('mode1' in the datasheet)
	TC4->COUNT32.CTRLA.reg |= TC_CTRLA_MODE_COUNT32;
	// Set TC4 waveform generation mode to 'match frequency'
	TC4->COUNT32.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
	//set prescaler
	//the clock normally counts at the GCLK_TC frequency, but we can set it to divide that frequency to slow it down
	//you can use different prescaler divisons here like TC_CTRLA_PRESCALER_DIV1 to get a different range
	TC4->COUNT32.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024 | TC_CTRLA_ENABLE; //it will divide GCLK_TC frequency by 1024
	//set the compare-capture register. 
	TC4->COUNT32.CC[0].reg = (u_int32_t) ((sample_period_seconds * SystemCoreClock) / 1024);
	while (TC4_syncing());

	// Configure interrupt request
	NVIC_DisableIRQ(TC4_IRQn);
	NVIC_ClearPendingIRQ(TC4_IRQn);
	NVIC_SetPriority(TC4_IRQn, priority);
	NVIC_EnableIRQ(TC4_IRQn);

	// Enable the TC4 interrupt request
	TC4->COUNT32.INTENSET.bit.MC0 = 1;
	while (TC4_syncing()); //wait until TC4 is done syncing 
}

void TC4_reconfigure(uint32_t sample_period_seconds) {
	TC4_stop_timer();

	TC4->COUNT32.CC[0].reg = (u_int32_t) ((sample_period_seconds * SystemCoreClock) / 1024);
 	while (TC4_syncing());

	 TC4_start_timer();
}