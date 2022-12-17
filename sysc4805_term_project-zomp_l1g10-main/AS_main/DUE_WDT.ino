#define WDT_KEY (0xA5)
#define WDT_PERIOD_s 6
/* Slow clock is running at 32.768 kHz
  watchdog frequency is therefore 32768 / 128 = 256 Hz */
#define WDT_FREQ 256

void setupWDT()
{
  WDT->WDT_MR = WDT_MR_WDD(0xFFF) |
                WDT_MR_WDRSTEN |                     //  Triggers a reset once counter reaches 0
                WDT_MR_WDV(WDT_FREQ * WDT_PERIOD_s); // Watchdog triggers a reset after WDT_PERIOD_s seconds if underflow
}

void resetWDT()
{
  // Restart watchdog
  WDT->WDT_CR = WDT_CR_KEY(WDT_KEY) | WDT_CR_WDRSTT;
}

uint32_t getStatusWDT()
{
  uint32_t status = (RSTC->RSTC_SR & RSTC_SR_RSTTYP_Msk) >> RSTC_SR_RSTTYP_Pos /*8*/; // Get status from the last Reset
}
