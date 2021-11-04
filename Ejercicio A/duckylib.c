#define _XTAL_FREQ 4000000
#include <stdbool.h>
#include <xc.h>
#include "duckylib.h"


//-----LCD------
LCD lcd;
void LCD_Out ( char c ) {

 if ( c & 1 ){
 *(lcd.PORT) |= 1 << lcd.D4;
 }
 else {
 *(lcd.PORT) &= ~(1 << lcd.D4);
 }
 if ( c & 2 ) {
 *(lcd.PORT) |= 1 << lcd.D5;
 }
 else {
 *(lcd.PORT) &= ~(1 << lcd.D5);
 }
 if ( c & 4 ) {
 *(lcd.PORT) |= 1 << lcd.D6;
 }
 else {
 *(lcd.PORT) &= ~(1 << lcd.D6);
 }
 if ( c & 8 ) {
 *(lcd.PORT) |= 1 << lcd.D7;
 }
 else {
 *(lcd.PORT) &= ~(1 << lcd.D7);
 }
}
void LCD_Write ( unsigned char c ) {
 *(lcd.PORT) &= ~(1 << lcd.RS); // => RS = 0
 LCD_Out(c);
 *(lcd.PORT) |= 1 << lcd.EN; // => E = 1
 __delay_ms(4);
 *(lcd.PORT) &= ~(1 << lcd.EN); // => E = 0
}
bool LCD_Init ( LCD display ) {
 lcd = display;
 /*
 * TODO:
 * The function should clear only the appropriate bits, not the whole PORT
 *
 * TODO:
 * "#if defined" needs to support more microcontrollers that have PORTD and PORTE
 */
 if ( lcd.PORT == &PORTA ) {
 TRISA = 0x00;
 }
 else if ( lcd.PORT == &PORTB ) {
 TRISB = 0x00;
 }
 else if ( lcd.PORT == &PORTC ) {
 TRISC = 0x00;
 }
 // #if defined(_16F877) || defined(_16F877A)
 else if ( lcd.PORT == &PORTD ) {
 TRISD = 0x00;
 }
 else if ( lcd.PORT == &PORTE ) {
 TRISE = 0x00;
 }
 // #endif
 else {
 return false;
 }
 // Give some time to the LCD to start function properly
 __delay_ms(20);
 // Send reset signal to the LCD
 LCD_Write(0x03);
 __delay_ms(5);
 LCD_Write(0x03);
 __delay_ms(16);
 LCD_Write(0x03);
 // Specify the data lenght to 4 bits
 LCD_Write(0x02);
 // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
 LCD_Cmd(0x28);
 // Set cursor to move from left to right
 LCD_Cmd(0x06);
 LCD_Display(true, false, false); // Turn on display and set cursor off
 LCD_Clear();

 return true;
}
void LCD_putc ( char c ) {
 *(lcd.PORT) |= 1 << lcd.RS; // => RS = 1
 LCD_Out((c & 0xF0) >> 4); //Data transfer
 *(lcd.PORT) |= 1 << lcd.EN;
 __delay_us(40);
 *(lcd.PORT) &= ~(1 << lcd.EN);
 LCD_Out(c & 0x0F);
 *(lcd.PORT) |= 1 << lcd.EN;
 __delay_us(40);
 *(lcd.PORT) &= ~(1 << lcd.EN);
}
void LCD_puts ( char *a ) {
 for ( int i = 0; a[i] != '\0'; ++i ) {
 LCD_putc(a[i]);
 }
}
void LCD_putrs ( const char *a ) {
 for ( int i = 0; a[i] != '\0'; ++i ) {
 LCD_putc(a[i]);
 }
}

//-----PIN MODE----
void pinMode(char terminal, char mode){
    
    char aux0 = (terminal & 0xF0) >> 4; //identifica el puerto
    char aux1 = 1 << (terminal & 0x0F); //identifica la terminal
    
    volatile unsigned char *puerto;
    puerto = &TRISA + aux0;
    
    if (mode == OUTPUT){
        char aux2 = *puerto & (~aux1);
        *puerto = aux2;
    }
    else {
        char aux2 = *puerto | aux1;
        *puerto = aux2;
    }
    
    switch(terminal){
        case _PA0:
                ADCON1bits.PCFG = 0b1111;
                break;
        
        case _PA1:
            if (ADCON1bits.PCFG < 14){
                ADCON1bits.PCFG = 14;
            }
            break;
    }
}



//-----ANALOG---
void ADCinit(int Canal){
    ADCON2 = 0b10000100; //Justificación a la derecha / Reloj de conversión FOSC/4
    
    switch(Canal){
        case 1:
            ADCON1bits.PCFG= 0b1110;
            TRISAbits.TRISA0=1;
            break;
        case 2:
            ADCON1bits.PCFG= 0b1101;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            break;
        case 3:
            ADCON1bits.PCFG= 0b1100;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            break;
        case 4:
            ADCON1bits.PCFG= 0b1011;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            break;
        case 5:
            ADCON1bits.PCFG= 0b1010;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            break;
        case 6:
            ADCON1bits.PCFG= 0b1001;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            break;
        case 7:
            ADCON1bits.PCFG= 0b1000;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            break;
        case 8:
            ADCON1bits.PCFG= 0b0111;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            TRISEbits.TRISE2=1;
            break;
        case 9:
            ADCON1bits.PCFG= 0b0110;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            TRISEbits.TRISE2=1;
            TRISBbits.TRISB2=1;
            break;
        case 10:
            ADCON1bits.PCFG= 0b0101;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            TRISEbits.TRISE2=1;
            TRISBbits.TRISB2=1;
            TRISBbits.TRISB3=1;
            break;
        case 11:
            ADCON1bits.PCFG= 0b0100;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            TRISEbits.TRISE2=1;
            TRISBbits.TRISB2=1;
            TRISBbits.TRISB3=1;
            TRISBbits.TRISB1=1;
            break;
        case 12:
            ADCON1bits.PCFG= 0b0011;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            TRISEbits.TRISE2=1;
            TRISBbits.TRISB2=1;
            TRISBbits.TRISB3=1;
            TRISBbits.TRISB1=1;
            TRISBbits.TRISB4=1;
            break;
        case 13:
            ADCON1bits.PCFG= 0b0010;
            TRISAbits.TRISA0=1;
            TRISAbits.TRISA1=1;
            TRISAbits.TRISA2=1;
            TRISAbits.TRISA3=1;
            TRISAbits.TRISA5=1;
            TRISEbits.TRISE0=1;
            TRISEbits.TRISE1=1;
            TRISEbits.TRISE2=1;
            TRISBbits.TRISB2=1;
            TRISBbits.TRISB3=1;
            TRISBbits.TRISB1=1;
            TRISBbits.TRISB4=1;
            TRISBbits.TRISB0=1;
            break;   
            
    }
    
    ADCON0bits.ADON = 1; //Convertidor AD encendido
    
}
int analogRead(int Canal){
    unsigned int dato=0;
    switch (Canal){
        case _AN0:
            ADCON0bits.CHS=0b0000;
            break;
        case _AN1:
           ADCON0bits.CHS=0b0001;
           break;
        case _AN2:
            ADCON0bits.CHS=0b0010;
            break;
        case _AN3:
           ADCON0bits.CHS=0b0011;
           break;
        case _AN4:
            ADCON0bits.CHS=0b0100;
            break;
        case _AN5:
           ADCON0bits.CHS=0b0101;
           break;
        case _AN6:
            ADCON0bits.CHS=0b0110;
            break;
        case _AN7:
           ADCON0bits.CHS=0b0111;
           break;
        case _AN8:
            ADCON0bits.CHS=0b1000;
            break;
        case _AN9:
           ADCON0bits.CHS=0b1001;
           break;
        case _AN10:
            ADCON0bits.CHS=0b1010;
            break;
        case _AN11:
           ADCON0bits.CHS=0b1011;
           break;
        case _AN12:
            ADCON0bits.CHS=0b1100;
            break;
    }
    
    
        ADCON0bits.GODONE = 1; 
        while (ADCON0bits.GODONE == 1){     
    }   
    dato = ADRESH << 8; 
    dato |= ADRESL; 
    
        return(dato);
    }


//----DIGITAL----
void digitalWrite(char terminal, char mode){
    char aux0 = (terminal & 0xF0) >> 4; //identifica el puerto
    char aux1 = 1 << (terminal & 0x0F); //identifica la terminal
    
    volatile unsigned char *puerto;
    puerto = &LATA + aux0;
    
     if (mode == LOW){
        char aux2 = *puerto & (~aux1);
        *puerto = aux2;
    }
    else {
        char aux2 = *puerto | aux1;
        *puerto = aux2;
    }
    
    
}
char digitalRead(char terminal){
    char resultado = 0;
    char aux0 = (terminal & 0xF0) >> 4; //identifica el puerto
    char aux1 = 1 << (terminal & 0x0F); //identifica la terminal
    
    volatile unsigned char *puerto;
    puerto = &PORTA + aux0;
    
    char aux2 = *puerto & aux1;
    if (aux2 > 0){
        resultado = 1;
    }
    else {
        resultado = 0;
    }
    
    return resultado;

}



//-----PRINT NUMBER-----
char unidades;
char decenas;
char centenas;
char milesimas;
void printNumber(unsigned int num){
     unidades=48;
     decenas=48;
     centenas=48;
     milesimas=48;

    for(num=num; num>999;num=num-1000){
        milesimas++;
    }
    
    for(num=num; num>99;num=num-100){
        centenas++;
    }
    
    for(num=num; num>9;num=num-10){
        decenas++;
    }
    
    for(num=num; num>0;num=num-1){
        unidades++;
    }
    
}



    

char Timer=0;
char salida=0; 


//------MATRIX KEYBOARD-----
char valor[4][4]={{0,0,0,0},
                      {0,0,0,0},
                      {0,0,0,0},
                      {0,0,0,0}};
char tecla[4][4]={ {7,8,9,119},
                   {4,5,6,124},
                   {1,2,3,57},
                   {94,0,121,113}};
char keypadread(){
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            __delay_ms(5);
            valor [0][0] = PORTBbits.RB4;
            valor [0][1] = PORTBbits.RB5;
            valor [0][2] = PORTBbits.RB6;
            valor [0][3] = PORTBbits.RB7;


            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
              __delay_ms(5);
            valor [1][0] = PORTBbits.RB4;
            valor [1][1] = PORTBbits.RB5;
            valor [1][2] = PORTBbits.RB6;
            valor [1][3] = PORTBbits.RB7;


            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 1;
            LATBbits.LATB3 = 0;
             __delay_ms(5);
            valor [2][0] = PORTBbits.RB4;
            valor [2][1] = PORTBbits.RB5;
            valor [2][2] = PORTBbits.RB6;
            valor [2][3] = PORTBbits.RB7;


            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 1;
             __delay_ms(5);
            valor [3][0] = PORTBbits.RB4;
            valor [3][1] = PORTBbits.RB5;
            valor [3][2] = PORTBbits.RB6;
            valor [3][3] = PORTBbits.RB7;


            
            for(char i=0; i<4; i++){
                for (char j=0; j<4; j++){
                    if(valor[i][j] > 0){
                        salida = tecla[i][j];
                    }
                }
            }
            LATD= salida;
            return(salida);
        }



//-----TIMER----
void tmr0init(char x) {
   

    INTCONbits.GIE = 1; // habilitar las interrupciones globales (configurar PEIE = 0)
    INTCONbits.PEIE = 0; // Deshablitar Interrupciones de periféricos.
    INTCONbits.TMR0IE = 1; //Habilitar interrupción por desbordamiento de TMR0
    INTCONbits.INT0IE = 0; // Deshabilitar interrupciones externas.
    INTCONbits.RBIE = 0; //Deshabilitar interrupción por puerto RB
    INTCONbits.TMR0IF =0; // Limpiar la bandera de desbordamiento de TMR0
    RCONbits.IPEN = 0; // Deshabilitar prioridades en las interrupciones
    T0CONbits.TMR0ON = 1; // Habilitar tmr0
    T0CONbits.T08BIT = 1; //Configurar timer a 8 bits (puede ser de 16 bits)
    T0CONbits.T0CS = 0; // Seleccionar que el timer0 se incrementa por ciclo de reloj interno
    T0CONbits.PSA = 0; // Utilizar un prescaler (para hacer más largo el timpo de cuenta de timer).
//Los siguientes 3 bits controlan el preescaler, en este caso 1:256
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 1; 
    Timer= 256-((x*.001)/(256*.000001));

}
//void __interrupt() ISR(void) { //Siempre usamos este nombre
//  
// INTCONbits.TMR0IF =0;
// TMR0L=F;//Para interrupciones de 1ms
//} 



//-----PWM-----
void PWMinit(){
    CCP1CON=0b00001100;
    TRISCbits.RC2=0;
}
void pwmON(int freq, char ciclot){
    int aux=0;  
    char Presc=16;
    aux=(1000000/(freq*Presc))-1;
    if(aux<256){
    PR2=aux;        
    }
    else{
        int Presc=4;
        aux=(1000000/(freq*Presc))-1;
        if (aux<256){
            PR2=aux;           
          }
        else{
        int Presc=1;
        aux=(1000000/(freq*Presc))-1;
        if (aux<256){
         PR2=aux;            
            }
        else{
            aux=62;
            Presc=16;
            }
        }
        
    }
    PR2=aux;
    switch(Presc)
    {
        case 16:
            T2CONbits.T2CKPS=0b11;
            break;
        case 4:
            T2CONbits.T2CKPS=0b01;
            break;
        case 1:
            T2CONbits.T2CKPS=0b00;
            break;
    }
    aux=(40000*ciclot)/(freq*Presc);
    CCPR1L = aux >> 2;
    CCP1CONbits.DC1B = aux & 3;
    T2CONbits.TMR2ON = 1;
    return;
    
}
void pwmOFF(){
    T2CONbits.TMR2ON = 0;
}



//----MAP----
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}