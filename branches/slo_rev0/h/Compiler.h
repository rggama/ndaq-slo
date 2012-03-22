/*********************************************************************
 *
 *                  Compiler specific defs.
 *
 *********************************************************************
 * FileName:        Compiler.h
 * Dependencies:    None
 * Processor:       PIC18
 * Complier:        MCC18 v1.00.50 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * Author               Date     Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     7/12/04  Rel 0.9
 ********************************************************************/
#ifndef COMPILER_H
#define COMPILER_H

#if defined(HI_TECH_C)
    #if defined(_MPC_)
        #define HITECH_C18
    #else
        #error "Unknown compiler is selected."
    #endif
#else
    #if !defined(_WIN32)
        #define MCHP_C18
    #endif
#endif

#if defined(MCHP_C18) && defined(HITECH_C18)
#error "Invalid Compiler selection."
#endif

#if !defined(MCHP_C18) && !defined(HITECH_C18) && !defined(_WIN32)
#error "Compiler not supported."
#endif

#if defined(MCHP_C18)
    #include <p18cxxx.h>    // p18cxxx.h must have current processor
                            // defined.
#endif

#if defined(HITECH_C18)
    #include <pic18.h>
    #include <stdio.h>
#endif

#include <stdlib.h>


#if defined(WIN32)
    #define ROM
#endif

#if defined(MCHP_C18)
    #define ROM                 rom

    #define DC                  STATUSbits.DC

    #define EEWR                EECON1bits.WR
    #define EEWREN              EECON1bits.WREN

    #define LATA0               LATAbits.LATA0
    #define LATA1               LATAbits.LATA1
    #define LATA2               LATAbits.LATA2
    #define LATA3               LATAbits.LATA3
    #define LATA4               LATAbits.LATA4
    #define LATA5               LATAbits.LATA5
    #define LATA6               LATAbits.LATA6
    #define LATA7               LATAbits.LATA7

    #define RB0                 PORTBbits.RB0
    #define RB1                 PORTBbits.RB1
    #define RB2                 PORTBbits.RB2
    #define RB3                 PORTBbits.RB3
    #define RB4                 PORTBbits.RB4
    #define RB5                 PORTBbits.RB5
    #define RB6                 PORTBbits.RB6
    #define RB7                 PORTBbits.RB7

    #define TRISB0              TRISBbits.TRISB0
    #define TRISB1              TRISBbits.TRISB1
    #define TRISB2              TRISBbits.TRISB2
    #define TRISB3              TRISBbits.TRISB3
    #define TRISB4              TRISBbits.TRISB4
    #define TRISB5              TRISBbits.TRISB5
    #define TRISB6              TRISBbits.TRISB6
    #define TRISB7              TRISBbits.TRISB7

    #define RA0                 PORTAbits.RA0
    #define RA1                 PORTAbits.RA1
    #define RA2                 PORTAbits.RA2
    #define RA3                 PORTAbits.RA3
    #define RA4                 PORTAbits.RA4
    #define RA5                 PORTAbits.RA5
    #define RA6                 PORTAbits.RA6
    #define RA7                 PORTAbits.RA7

    #define TRISA0              TRISAbits.TRISA0
    #define TRISA1              TRISAbits.TRISA1
    #define TRISA2              TRISAbits.TRISA2
    #define TRISA3              TRISAbits.TRISA3
    #define TRISA4              TRISAbits.TRISA4
    #define TRISA5              TRISAbits.TRISA5
    #define TRISA6              TRISAbits.TRISA6
    #define TRISA7              TRISAbits.TRISA7

    #define TRISC0              TRISCbits.TRISC0
    #define TRISC1              TRISCbits.TRISC1
    #define TRISC2              TRISCbits.TRISC2
    #define TRISC3              TRISCbits.TRISC3
    #define TRISC4              TRISCbits.TRISC4
    #define TRISC5              TRISCbits.TRISC5
    #define TRISC6              TRISCbits.TRISC6
    #define TRISC7              TRISCbits.TRISC7

    #define LATC0               LATCbits.LATC0
    #define LATC1               LATCbits.LATC1
    #define LATC2               LATCbits.LATC2
    #define LATC3               LATCbits.LATC3
    #define LATC4               LATCbits.LATC4
    #define LATC5               LATCbits.LATC5
    #define LATC6               LATCbits.LATC6
    #define LATC7               LATCbits.LATC7

    #define RC0                 PORTCbits.RC0
    #define RC1                 PORTCbits.RC1
    #define RC2                 PORTCbits.RC2
    #define RC3                 PORTCbits.RC3
    #define RC4                 PORTCbits.RC4
    #define RC5                 PORTCbits.RC5
    #define RC6                 PORTCbits.RC6
    #define RC7                 PORTCbits.RC7

    #define TRISD7              TRISDbits.TRISD7
    #define TRISD6              TRISDbits.TRISD6
    #define TRISD5              TRISDbits.TRISD5
    #define TRISD4              TRISDbits.TRISD4
    #define TRISD3              TRISDbits.TRISD3
    #define TRISD2              TRISDbits.TRISD2
    #define TRISD1              TRISDbits.TRISD1
    #define TRISD0              TRISDbits.TRISD0

    #define LATD0               LATDbits.LATD0
    #define LATD1               LATDbits.LATD1
    #define LATD2               LATDbits.LATD2
    #define LATD3               LATDbits.LATD3
    #define LATD4               LATDbits.LATD4
    #define LATD5               LATDbits.LATD5
    #define LATD6               LATDbits.LATD6
    #define LATD7               LATDbits.LATD7


    #define RD7                 PORTDbits.RD7
    #define RD6                 PORTDbits.RD6
    #define RD5                 PORTDbits.RD5
    #define RD4                 PORTDbits.RD4
    #define RD3                 PORTDbits.RD3
    #define RD2                 PORTDbits.RD2
    #define RD1                 PORTDbits.RD1
    #define RD0                 PORTDbits.RD0

    #define RE0                 PORTEbits.RE0
    #define RE1                 PORTEbits.RE1
    #define RE2                 PORTEbits.RE2
    #define RE3                 PORTEbits.RE3
    #define RE4                 PORTEbits.RE4
    #define RE5                 PORTEbits.RE5
    #define RE6                 PORTEbits.RE6
    #define RE7                 PORTEbits.RE7

    #define TMR0IE              INTCONbits.TMR0IE
    #define TMR0IF              INTCONbits.TMR0IF
    #define RBPU                INTCON2bits.RBPU
    #define RBIF                INTCONbits.RBIF
    #define RBIE                INTCONbits.RBIE

    #define INT2IE              INTCON3bits.INT2IE
    #define INT2IF              INTCON3bits.INT2IF

    #define TMR0ON              T0CONbits.TMR0ON

    #define TMR1ON              T1CONbits.TMR1ON

    #define WCOL                SSPCON1bits.WCOL

    #define SEN                 SSPCON2bits.SEN
    #define ACKSTAT             SSPCON2bits.ACKSTAT
    #define RSEN                SSPCON2bits.RSEN
    #define RCEN                SSPCON2bits.RCEN
    #define ACKEN               SSPCON2bits.ACKEN
    #define PEN                 SSPCON2bits.PEN
    #define ACKDT               SSPCON2bits.ACKDT

    #define SSPRW               SSPSTATbits.R_W
    #define SSPBF               SSPSTATbits.BF

    #define GIEH                INTCONbits.GIEH
    #define GIEL                INTCONbits.GIEL

    #define BCLIF               PIR2bits.BCLIF

    //#define TXIE                PIE1bits.TXIE
    //#define RCIE                PIE1bits.RCIE
    #define TMR1IE              PIE1bits.TMR1IE

    //#define RCIF                PIR1bits.RCIF
    //#define TXIF                PIR1bits.TXIF
    #define TMR1IF              PIR1bits.TMR1IF


    //#define TRMT                TXSTAbits.TRMT
    //#define BRGH                TXSTAbits.BRGH

    #define CREN                RCSTAbits.CREN

    #define ADGO                ADCON0bits.GO
    #define ADON                ADCON0bits.ADON

    #define RI                  RCONbits.RI
    #define TO                  RCONbits.TO
    #define PD                  RCONbits.PD
    #define POR                 RCONbits.POR
    #define BOR                 RCONbits.BOR

    #define STKOVF              STKPTRbits.STKFUL
    #define STKUNF              STKPTRbits.STKUNF

    #define NOP()               Nop()
    #define CLRWDT()            ClrWdt()
    #define RESET()             Reset()
    #define SLEEP()             Sleep()
    #define DISABLE_WDT()       (WDTCONbits.SWDTEN = 0)
    #define ENABLE_WDT()        (WDTCONbits.SWDTEN = 1)


#endif

#if defined(HITECH_C18)
    #define ROM                 const

    #define memcmppgm2ram(a, b, c)      memcmp(a, b, c)
    #define memcpypgm2ram(a, b, c)      mymemcpy(a, b, c)
    #define itoa(val, string)           sprintf(string, "%u", val)

    extern void *mymemcpy(void * d1, const void * s1, unsigned char n);
    extern char *strupr(char*);

    /* Fix for HITECH C */
    #define TXREG       _TXREG
    static volatile near unsigned char       _TXREG       @ 0xFAD;


    #define LATA0               LA0
    #define LATA1               LA1
    #define LATA2               LA2
    #define LATA3               LA3
    #define LATA4               LA4
    #define LATA5               LA5
    #define LATA6               LA6
    #define LATA7               LA7

    #define LATD0               LD0
    #define LATD1               LD1
    #define LATD2               LD2
    #define LATD3               LD3
    #define LATD4               LD4
    #define LATD5               LD5
    #define LATD6               LD6
    #define LATD7               LD7


    #define TRISA2              TRISA2
    #define TRISA5              TRISA5

    #define SSPRW               RW
    #define SSPBF               BF

    #define ADGO                GODONE

    #define DISABLE_WDT()       (SWDTEN = 0)
    #define ENABLE_WDT()        (SWDTEN = 1)


#endif

#if defined(WIN32)
    #define memcpypgm2ram(d, s, c)  memcpy(d, s, c)
#endif

#endif
