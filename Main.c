/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *    
 * =====================================================================
 */
#include <stdint.h>
#include <stdio.h>
#include "2450addr.h"
#include "libc.h"
#include "option.h"

void __attribute__((interrupt("IRQ"))) RTC_TICK(void);

uint32_t tick = 0;

void RTC_Init(){
    rRTCCON = (0x1C0);

    rTICNT0 = (0x80);
    rTICNT1 = (0x1);
    rTICNT2 = (0x0);
}

void RTC_Tick_Init(){
    rINTMOD1 = (0x0);
    
    rINTMSK1 = BIT_ALLMSK;
    
    rSRCPND1 = (BIT_TICK);
    rINTPND1 = (BIT_TICK);

    rINTMSK1 = ~(BIT_TICK);

    pISR_TICK = (unsigned)RTC_TICK;
}

void Main(){
    Uart_Init(115200);
    
    RTC_Init();
    RTC_Tick_Init();

    while(1){
        
    }
}

void __attribute__((interrupt("IRQ"))) RTC_TICK(void){
    ClearPending1(BIT_TICK);
    Uart_Printf("%d seconds\t", ++tick);
}