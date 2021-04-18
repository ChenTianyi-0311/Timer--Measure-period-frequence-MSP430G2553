#include <msp430.h>
unsigned int memo_capt=0;
unsigned int capt;
unsigned int diff_capt;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  TA0CTL |= TASSEL_2 + MC_2; // source horloge SMCLK + mode continu
  TA0CCTL0 |= CM_1 + CCIS_0; // front montant + CCI0A
  TA0CCTL0 |= CAP + CCIE; // mode capture + autorisation interruption
  P1DIR |= BIT0; // P1.0 (LED rouge) en sortie
  P1DIR &= ~BIT1; // P1.1 en entree
  P1SEL |= BIT1; // fonction entree capture sur P1.1 (TA0.CCI0A)
  P1SEL2 &= ~BIT1; // fonction entree capture sur P1.1 (TA0.CCI0A)
  __enable_interrupt();
  while(1);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void ma_capture(void)
{
  capt = TA0CCR0;
  diff_capt = capt - memo_capt;
  memo_capt = capt;
  if(diff_capt > 100)
  {
  P1OUT |= BIT0;
  }
  else
  {
  P1OUT &= ~BIT0;
  }
}
