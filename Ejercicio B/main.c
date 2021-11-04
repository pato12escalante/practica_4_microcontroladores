/*
 * File:   main.c
 * Author: Patricio Escalante
 *
 * Created on 1 de noviembre de 2021, 12:14 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdbool.h>
#include "configbits.h"
#include "duckylib.h"

#define _XTAL_FREQ 4000000

void main() {
    int temp_analog, temp;
    ADCinit(1);
    
    LCD lcd = { &PORTD, 5, 4, 0, 1, 2, 3 }; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);
    LCD_Clear(); //LIMPIAR LCD
    LCD_Set_Cursor(0,0); 
    LCD_putrs("TEMP:");
    TRISBbits.RB3=0;
    
    
    while(1){
        temp_analog=analogRead(_AN0);
        
        temp=(temp_analog*10)/2.05;
        
        printNumber(temp);
        LCD_Set_Cursor(0,5);
        if(temp<100){
            LCD_putrs(""); //Escribir los millares
            LCD_putrs("");// Escribir las centenas
            LCD_putc(decenas); //Escribir las decenas
            LCD_putrs(".");
            LCD_putc(unidades); //Escribir las unidades
            LCD_putc(223);
            LCD_putrs("C");
        }else{
            if(temp>=100 && temp<1000){
                LCD_putrs(""); //Escribir los millares
                LCD_putc(centenas); // Escribir las centenas
                LCD_putc(decenas); //Escribir las decenas
                LCD_putrs(".");
                LCD_putc(unidades); //Escribir las unidades
                LCD_putc(223);
                LCD_putrs("C");
            }else{
                LCD_putc(milesimas); //Escribir los millares
                LCD_putc(centenas); // Escribir las centenas
                LCD_putc(decenas); //Escribir las decenas
                LCD_putrs(".");
                LCD_putc(unidades); //Escribir las unidades
                LCD_putc(223);
                LCD_putrs("C");
            }
        }
        
        
        
        
        
        LCD_Set_Cursor(1,0);
        if(temp<200){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<20;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=200 && temp<210){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<1;i++){
                LCD_putc(255);
            }
            for(int i=0; i<19;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=210 && temp<220){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<2;i++){
                LCD_putc(255);
            }
            for(int i=0; i<18;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=220 && temp<230){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<3;i++){
                LCD_putc(255);
            }
            for(int i=0; i<17;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=230 && temp<240){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<4;i++){
                LCD_putc(255);
            }
            for(int i=0; i<16;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=240 && temp<250){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<5;i++){
                LCD_putc(255);
            }
            for(int i=0; i<15;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=250 && temp<260){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<6;i++){
                LCD_putc(255);
            }
            for(int i=0; i<14;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=260 && temp<270){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<7;i++){
                LCD_putc(255);
            }
            for(int i=0; i<13;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=270 && temp<280){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<8;i++){
                LCD_putc(255);
            }
            for(int i=0; i<12;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=280 && temp<290){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<9;i++){
                LCD_putc(255);
            }
            for(int i=0; i<11;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=290 && temp<300){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<10;i++){
                LCD_putc(255);
            }
            for(int i=0; i<10;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=300 && temp<310){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<11;i++){
                LCD_putc(255);
            }
            for(int i=0; i<9;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=310 && temp<320){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<12;i++){
                LCD_putc(255);
            }
            for(int i=0; i<8;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=320 && temp<330){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<13;i++){
                LCD_putc(255);
            }
            for(int i=0; i<7;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=330 && temp<340){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<14;i++){
                LCD_putc(255);
            }
            for(int i=0; i<6;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=340 && temp<350){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<15;i++){
                LCD_putc(255);
            }
            for(int i=0; i<5;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=350 && temp<360){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<16;i++){
                LCD_putc(255);
            }
            for(int i=0; i<4;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=360 && temp<370){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<17;i++){
                LCD_putc(255);
            }
            for(int i=0; i<3;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=370 && temp<380){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<18;i++){
                LCD_putc(255);
            }
            for(int i=0; i<2;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=380 && temp<390){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<19;i++){
                LCD_putc(255);
            }
            for(int i=0; i<1;i++){
                LCD_putrs(" ");
            }
        }
        if(temp>=390 && temp<=1500){
            LCD_Set_Cursor(1,0);
            for(int i=0; i<20;i++){
                LCD_putc(255);
            }
            for(int i=0; i<0;i++){
                LCD_putrs(" ");
            }
        }
        
        
        if(temp>=350){
            LATBbits.LATB3=1;
        }else{
            LATBbits.LATB3=0;
        }
        
        
        if(temp>=390 && temp<=1500){
            LCD_Set_Cursor(2,7);
            LCD_putrs("ALERTA");
            LCD_Set_Cursor(3,5);
            LCD_putrs("TEMP. ALTA");
        }else{
            LCD_Set_Cursor(2,7);
            LCD_putrs("      ");
            LCD_Set_Cursor(3,5);
            LCD_putrs("          ");
        }
        
        

            

    }
    
    
}
