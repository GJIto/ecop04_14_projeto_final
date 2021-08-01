//Nome: Gabriel Jun Ito
//Matrícula: 201901462
#ifndef BALANCA_H
#define	BALANCA_H

#include "balanca.h"
#include <pic18f4520.h>
#include "config.h" 
#include "bits.h" 
#include "ssd.h" 
#include "keypad.h"
#include "lcd.h"
#include "pwm.h"

void menu (void);

void setIMC(int, int);

void medidorPeso(int);

void medidorAltura(int);

void itoa(unsigned int, char*);

int roundNo(float num);

void ledp (void);
#endif	/* BALANCA_H */

