#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdbool.h>
#include "configbits.h"
#include "duckylib.h"

#define _XTAL_FREQ 4000000



void main() {
    int var_1, porcentaje;
    ADCinit(13);

    
    LCD lcd = { &PORTD, 5, 4, 0, 1, 2, 3 }; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);
    LCD_Clear(); //LIMPIAR LCD
    LCD_Set_Cursor(0,0); 
    LCD_putrs("Dato ADC:"); 
    LCD_Set_Cursor(2,0); 
    LCD_putrs("Porcentaje:"); 

    
    while(1){
        
        
        var_1=analogRead(_AN0);
        
        printNumber(var_1);


        LCD_Set_Cursor(0,13);
        LCD_putc(milesimas); //Escribir los millares
        LCD_putc(centenas); // Escribir las centenas
        LCD_putc(decenas); //Escribir las decenas 
        LCD_putc(unidades); //Escribir las unidades
        

        
        
      
        porcentaje=map(var_1, 0, 1023, 0, 100);
        printNumber(porcentaje);


        LCD_Set_Cursor(2,13);
        if(centenas==48){
            LCD_putc(""); //Escribir las decenas 
            LCD_putc(decenas); //Escribir las decenas 
            LCD_putc(unidades); //Escribir las unidades
        }else{
            LCD_putc(centenas); // Escribir las centenas
            LCD_putc(decenas); //Escribir las decenas 
            LCD_putc(unidades); //Escribir las unidades
        }
        
        
        LCD_Set_Cursor(2,16);
        LCD_putrs("%");
        

        
    }
    
}
