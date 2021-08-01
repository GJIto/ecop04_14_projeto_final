//Nome: Gabriel Jun Ito
//Matrícula: 201901462
#include <pic18f4520.h>
#include "bits.h"
#include "config.h"
#include "io.h"
#include "keypad.h"
#include "lcd.h"
#include "pwm.h"
#include "ssd.h"
#include "balanca.h"
#include "adc.h"
#include "atraso.h"

void main(void) {
    //Inicializacao de variaveis e funcionalidades
    int peso = 743;   //74,3kg
    int altura = 180; //1,80m
    TRISA = 0xC3;
    TRISB = 0x03;
    TRISC = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1 = 0x06;
    TRISB = 0x03;
    kpInit();
    lcdInit();
    pwmInit();
    adc_init();
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0; 
    PORTB = 0;
    
    //Menu de inicio
    lcdPosition(1, 0);
    lcd_str("Balanca  Digital");
    lcdPosition(2, 3);
    lcd_str("Aperte RB1");
    lcdPosition(3, 3);
    lcd_str("para ligar");
    while (bitTst(PORTB, 1)); // Botao que inicia o programa

    //peso do usuario
    lcdCommand(L_CLR);
    lcdPosition(4, 0);
    lcd_str("Pesando...");
    medidorPeso(peso);
    ledp();
    atraso_ms(2000); 
    
    //altura do usuario
    lcdCommand(L_CLR);
    menu();
    lcdPosition(4, 0);
    lcd_str("Medindo altura..");
    medidorAltura(altura);
    ledp();
    atraso_ms(2000);
    
    //imc do usuario
    lcdCommand(L_CLR);
    menu();
    lcdPosition(4, 0);
    lcd_str("Calculando IMC...");
    setIMC(peso, altura);
   // pwmSet1(99);
    atraso_ms(3000);
    ledp();
    menu();
   // pwmSet1(0);

    for (;;) {
        ledp();
    }
}