#include <main.h>
unsigned int16 bien_toc_do;

void main()
{
   set_tris_c(0x00);
   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_16, 249, 1);
   bien_toc_do = 800; // 80%
   set_pwm1_duty(bien_toc_do);
   while(TRUE);
}
// Tpwm = 0.8ms
// T = 1/20Mhz = 0.05us = 50ns
// PERIOD_PWM = [PR2+1] * 4 * Tocs * PVtmr2 = 0.8ms = 800.000ns
// 0 <= PR2 <= 255, PVtmr2 = 1,4,16
// [PR2+1] = PERIOD_PWM / (4*Tosc*PVtmr2) = 800.000 / (4*50ns*16) = 250
// PR2 = 249
// DUTY_CYCLE_max = PERIOD_pwm
//  Duty Cycle =(CCPR1L:CCP1CON<5:4>) * Tosc * PVtmr2
// (CCPR1L:CCP1CON<5:4>) = DUTY_CYCLEmax / Tosc * PVtmr2 = 800.000ns /50ns*16 = 1000
// 1000 * 10% = 100
