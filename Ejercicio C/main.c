/*
 * File:   main.c
 * Author: Patricio Escalante
 *
 * Created on 1 de noviembre de 2021, 02:44 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdbool.h>
#include "configbits.h"
#include "duckylib.h"

#define _XTAL_FREQ 4000000

void main() {
    int var_1;
    ADCinit(13);

    
    LCD lcd = { &PORTD, 5, 4, 0, 1, 2, 3 }; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);
    LCD_Clear(); //LIMPIAR LCD
    
    while(1){
        var_1=analogRead(_AN1);
        
        
        if(var_1>=0 && var_1<20){
            LCD_Set_Cursor(1,6);
            LCD_putrs("Button A");
        }
        
        if(var_1>=492 && var_1<532){
            LCD_Set_Cursor(1,6);
            LCD_putrs("Button B");
        }
        
        if(var_1>=662 && var_1<702){
            LCD_Set_Cursor(1,6);
            LCD_putrs("Button C");
        }
        
        if(var_1>=747 && var_1<787){
            LCD_Set_Cursor(1,6);
            LCD_putrs("Button D");
        }
        
        if(var_1>=798 && var_1<828){
            LCD_Set_Cursor(1,6);
            LCD_putrs("Button E");
        }
        
        if(var_1>840){
            LCD_Set_Cursor(1,6);
            LCD_putrs("        ");
        }
        
        
        
        
        
        
        
    }
    
}
