//Nome: Gabriel Jun Ito
//Matrícula: 201901462
#include "balanca.h"
#include <pic18f4520.h>
#include "config.h" 
#include "bits.h" 
#include "ssd.h" 
#include "keypad.h"
#include "lcd.h"
#include "pwm.h"

int peso = 0;
int altura = 0;
int imc = 0;

void menu(void) {
    char str[6];
    float fImc = 0;
    lcdCommand(L_CLR);
    
    //mostra no lcd o peso
    lcdPosition(1, 0);
    lcd_str("Peso:");
    itoa(peso * 10, str);
    lcdData(str[1]);
    lcdData(str[2]);
    lcdData(',');
    lcdData(str[3]);
    lcd_str("kg");
    
    //mostra no lcd a altura
    lcdPosition(2, 0);
    lcd_str("Altura:");
    itoa(altura * 10, str);
    lcdData(str[1]);
    lcdData(',');
    lcdData(str[2]);
    lcdData(str[3]);
    lcd_str("m");
    
    //mostra no lcd o imc
    lcdPosition(3, 0);
    lcd_str("IMC:");
    itoa(imc, str);
    lcdData(str[1]);
    lcdData(str[2]);
    lcdData(',');
    lcdData(str[3]);
    lcdData(str[4]);
    lcdData(str[5]);
    //mostra o grau do imc pelo lcd e pelo cooler
    if(imc != 0){
        fImc = imc/100;
        if(fImc < 17){
           lcdPosition(4, 0); 
           pwmSet1(40);
           lcd_str("Mt abaixoDoPeso");
        }
        if(fImc >= 17 && fImc < 18.5){
           lcdPosition(4, 0); 
           pwmSet1(65);
           lcd_str("Abaixo do peso");
        }
        if(fImc >= 18.5 && fImc < 25){
           lcdPosition(4, 0); 
           pwmSet1(99);
           lcd_str("Peso normal");
        }
        if(fImc >= 25 && fImc < 30){
           lcdPosition(4, 0); 
           pwmSet1(65);
           lcd_str("Acima do peso");
        }
        if(fImc >= 30 && fImc < 35){
           lcdPosition(4, 0); 
           pwmSet1(40);
           lcd_str("Obesidade I");
        }
        if(fImc >= 35 && fImc < 40){
           lcdPosition(4, 0); 
           pwmSet1(25);
           lcd_str("Obesidade II");
        }
        if(fImc > 40){
           lcdPosition(4, 0); 
           pwmSet1(10);
           lcd_str("Obesidade III");
        }
    }
}

//calcula o imc
void setIMC(int p, int a){
    float aux = (float)p / ((float) a*(float)a);
    imc = roundNo(aux*100000);
}

//arrendonda um float para int
int roundNo(float num){
    return num < 0 ? num - 0.5 : num + 0.5;
}

//mede o peso do usuario
void medidorPeso(int p) {
    peso = p;
    volatile unsigned int tempo;
    int cont;
    int cont2;
    ledp();
    ssdInit();
    for (;;) {
        cont++;
        ssdDigit(((cont / 100) % 10), 0);
        ssdDigit(((cont / 90) % 10), 1);
        ssdDigit(((cont / 50) % 10), 2);
        ssdDigit(((cont / 25) % 10), 3);
        ssdUpdate();
        for (tempo = 0; tempo < 1000; tempo++);
        if (cont >= p) {
            break;
        }
    }
    for (cont2 = 0; cont2 < 750; cont2++) {
        ssdDigit(((p / 100) % 10), 0);
        ssdDigit(((p / 10) % 10), 1);
        ssdDigit(((p / 1) % 10), 2);
        ssdDigit(((p / 1) % 10), 3);
        ssdUpdate();
        for (tempo = 0; tempo < 1000; tempo++);
    }
    ledp();
    bitClr(PORTA, 2);
    bitClr(PORTA, 3);
    bitClr(PORTA, 4);
    bitClr(PORTA, 5);
}

//mede a altura do usuario
void medidorAltura(int a) {
    altura = a;
    volatile unsigned int tempo;
    int cont;
    int cont2;
    ledp();
    ssdInit();
    for (;;) {
        cont++;
        ssdDigit(((cont / 100) % 10), 0);
        ssdDigit(((cont / 80) % 10), 1);
        ssdDigit(((cont / 50) % 10), 2);
        ssdDigit(((cont / 25) % 10), 3);
        ssdUpdate();
        for (tempo = 0; tempo < 1000; tempo++);
        if (cont >= a) {
            break;
        }
    }
    for (cont2 = 0; cont2 < 750; cont2++) {
        ssdDigit(((a / 100) % 10), 0);
        ssdDigit(((a / 10) % 10), 1);
        ssdDigit(((a / 1) % 10), 2);
        ssdDigit(((a / 1) % 10), 3);
        ssdUpdate();
        for (tempo = 0; tempo < 1000; tempo++);
    }
    ledp();
    bitClr(PORTA, 2);
    bitClr(PORTA, 3);
    bitClr(PORTA, 4);
    bitClr(PORTA, 5);
}

//converte um uint para char*
void itoa(unsigned int val, char* str) {
    str[0] = (val / 10000) + 0x30;
    str[1] = ((val % 10000) / 1000) + 0x30;
    str[2] = ((val % 1000) / 100) + 0x30;
    str[3] = ((val % 100) / 10) + 0x30;
    str[4] = (val % 10) + 0x30;
    str[5] = 0;
}

//faz os led`s piscarem
void ledp(void) {
    TRISD = 0x00;
    PORTD = 0x00;
    float i;
    for (i = 0; i < 1000; i++);
    PORTD = 0b00000001;
    for (i = 0; i < 1000; i++);
    PORTD = 0b00000010;
    for (i = 0; i < 1000; i++);
    PORTD = 0b00000100;
    for (i = 0; i < 1000; i++);
    PORTD = 0b00001000;
    for (i = 0; i < 1000; i++);
    PORTD = 0b00010000;
    for (i = 0; i < 1000; i++);
    PORTD = 0b00100000;
    for (i = 0; i < 1000; i++);
    PORTD = 0b01000000;
    for (i = 0; i < 1000; i++);
    PORTD = 0b10000000;
    for (i = 0; i < 1000; i++);
}