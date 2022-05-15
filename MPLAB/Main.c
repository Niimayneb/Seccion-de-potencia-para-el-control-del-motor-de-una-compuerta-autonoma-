/*
 * File:   Main.c
 * Author: Naren Benyamin Poveda Varon 
 *
 * Created on 5 de agosto de 2021, 02:59 PM
 */

//VARIABLES GLOBALES

#define FOSC 4000000    // Define la frecuencia de oscilacion del cristal.
#define PLL 8           // PLL x8
#define FCY FOSC*PLL/4  // Frecuencia de cada instruccion(8.000.000) (4 seciones de reloj)

//ARCHIVOS CABECERA

#include <p30F4011.h>
//DEFINIR MACROS (del archivo p30f4011 en los archivos del compilador)

_FOSC(XT_PLL8 & CSW_FSCM_OFF) //Frecuencia de Oscilación
_FWDT(WDT_OFF) //Whatchdog timer
_FBORPOR(PWRT_16 & BORV20 & MCLR_EN) //Reinicio
_FGS(CODE_PROT_OFF) //Seguridad
#include <libpic30.h>
#include <xc.h>
//#include "I2C.h"
#include "I2C.h"
#include "math.h"
////#include "ADC_Sensor_Driver.h"

//DELAYS!!
#ifndef __DELAY_H
#define delay_us(x) __delay32(((x*FCY)/1000000L)) //delay x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))    //delay x ms
#define __DELAY_H 1
#endif
char Dir = 20; //direccion
char temp = 0;
char dataout = 49; // del esclavo a lmaestro
char datain = 0; // del maestro al esclavo
char Buff_Int_to_String[21];
char Aux_Buff_IS[21];
int Volts_Bateria = 0; //RB3
int Corriente_Carga = 0; //RB4
int B = 0;

//void I2C_TX(char DATA) {
//    I2CTRN = DATA;
//    while (IFS0bits.MI2CIF == 0);
//}

void I2C_DATA(char *VIASCI) {
    while (*VIASCI) {
        I2C_TX(*VIASCI);
        VIASCI++;
    }
}

void I2C_ASCI(uint16_t NUMBER) {
    int i = 0, j = 0;
    while (NUMBER >= 0) {
        Buff_Int_to_String[i] = '0' + (NUMBER % 10); //guardo el ultimo numero 
        NUMBER /= 10; //quito el numero que ya se guardo 
        i++;
        if (NUMBER == 0) {
            break;
        }
    }
    // se organizan los datos 
    while (Buff_Int_to_String[i - 1] != '\0') {
        Aux_Buff_IS[j] = Buff_Int_to_String[i - 1]; // se guardan los datos de manera ordenada 
        j++;
        i--;
    }
    //    I2C_DATA(Aux_Buff_IS);
    //    for (i = 0; i < 21; i++) {
    //        Aux_Buff_IS[i] = 0;
    //        Buff_Int_to_String[i] = 0;
    //    }
}

void __attribute__((__interrupt__, __no_auto_psv__)) _SI2CInterrupt(void) {
    //UART1_Send_Command("INTER\n");
    if ((I2CSTATbits.R_W == 0) && (I2CSTATbits.D_A == 0)) // La direccion es correcta (escritura)
    {
        temp = I2CRCV;
        I2CCONbits.SCLREL = 1;

    } else if ((I2CSTATbits.R_W == 0) && (I2CSTATbits.D_A == 1)) //se mira data (escritura)
    {

        datain = I2CRCV;
        I2CCONbits.SCLREL = 1;
    } else if ((I2CSTATbits.R_W == 1) && (I2CSTATbits.D_A == 0)) // Device address matched (read)
    {
        if (Volts_Bateria >= 3000) {
            I2C_ASCI(28);
            temp = I2CRCV;
            //I2CTRN = '0'+1;
            //I2C_ASCI(Volts_Bateria);
            I2CTRN = Aux_Buff_IS[0];
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
            I2CTRN = Aux_Buff_IS[1];
            //I2CTRN = '0'+2;
            I2CCONbits.SCLREL = 1;
            int i = 0;
            for (i = 0; i < 21; i++) {
                Aux_Buff_IS[i] = 0;
                Buff_Int_to_String[i] = 0;
            }
            __delay_ms(100);
        } else if (Volts_Bateria < 3000) {
            I2C_ASCI(Volts_Bateria);
            temp = I2CRCV;
            //I2CTRN = '0'+1;
            //I2C_ASCI(Volts_Bateria);
            I2CTRN = Aux_Buff_IS[0];
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
            I2CTRN = Aux_Buff_IS[1];
            //I2CTRN = '0'+2;
            I2CCONbits.SCLREL = 1;
            int i = 0;
            for (i = 0; i < 21; i++) {
                Aux_Buff_IS[i] = 0;
                Buff_Int_to_String[i] = 0;
            }
            __delay_ms(100);
        }
        if (Corriente_Carga > 4500) {
            I2C_ASCI(Corriente_Carga);
            temp = I2CRCV;
            //I2CTRN = '0'+1;
            //I2C_ASCI(Volts_Bateria);
            I2CTRN = Aux_Buff_IS[0];
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
            I2CTRN = Aux_Buff_IS[1];
            //I2CTRN = '0'+2;
            I2CCONbits.SCLREL = 1;
            int i = 0;
            for (i = 0; i < 21; i++) {
                Aux_Buff_IS[i] = 0;
                Buff_Int_to_String[i] = 0;
            }
            __delay_ms(100);
        } else if (Corriente_Carga <= 4500) {
            I2C_ASCI(00);
            temp = I2CRCV;
            //I2CTRN = '0'+1;
            //I2C_ASCI(Volts_Bateria);
            I2CTRN = Aux_Buff_IS[0];
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
            I2CTRN = Aux_Buff_IS[1];
            //I2CTRN = '0'+2;
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
        } else {
            I2C_ASCI(01);
            temp = I2CRCV;
            //I2CTRN = '0'+1;
            //I2C_ASCI(Volts_Bateria);
            I2CTRN = Aux_Buff_IS[0];
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
            I2CTRN = Aux_Buff_IS[1];
            //I2CTRN = '0'+2;
            I2CCONbits.SCLREL = 1;
            __delay_ms(100);
        }

    } else if ((I2CSTATbits.R_W == 1) && (I2CSTATbits.D_A == 0)) {

        temp = I2CRCV;
        I2CTRN = '0' + 2;
        I2CCONbits.SCLREL = 1;


    }

    _SI2CIF = 0; //clear I2C1 Slave interrupt flag
    // Clear the interrupt flag status bit - the interrupt is handled
    //    IFS0bits.SI2CIF = 0;
    //    Dir = 1;  
}

int main() {
    TRISB = 1; // Puerto B en entrada
    TRISE = 0; // Puerto D en salida
    //PWM
    PTCON = 0x8002; //0b1000000000000010
    PTPER = 0x018F; //0b0000000110001111
    PWMCON1 = 0x0000;
    PWMCON2 = 0x0000;
    DTCON1 = 62;
    PDC1 = 400;
    //ADC
    ADCON2 = 0x01A2; //0b0000000110100010
    ADCON3 = 0x1211; //ob0001001000010001
    ADCHS = 0x2424; //ob0010010000100100
    ADPCFG = 0xFFE7; // 0b1111111111100111  - 1 habilita los I/O digitales -
    ADCSSL = 0x0000;
    ADCON1 = 0x8000; //0b1000000000000000
    //  //Valores
    LATEbits.LATE2 = 0;
    LATEbits.LATE3 = 0;
    //const float Resolution_ADC = (5.0) / (1024); // (AVDD / 2^10bit)

    float Resolution_AD = 21.7;
    float Resolution_AC = 30;
    int k = 0;
    //UART
    //init_UART1();
    //  //ADC_Sensors_Driver_Init();
    //I2C
    Init_I2C();
    while (1) {
        //Sensor_Reading_ADC();
        //Sensores
        ADCON1bits.SAMP = 1;
        __delay_ms(100);
        ADCON1bits.SAMP = 0; //LATEbits.LATE1 = 1; //0b0000000000000010;
        Volts_Bateria = (ADCBUF3 * Resolution_AD);
        Corriente_Carga = (ADCBUF4 * Resolution_AC);

        //tranformacion a array 
        //Volts_Bateria   = Get_Volts_Sonar_1_ADC();
        //Corriente_Carga = Get_Volts_Sonar_2_ADC();
        //Serial_putUint32(Volts_Bateria * 357);
        //Serial_putUint32(Corriente_Carga * 357);
        //I2C
        //if (Dir == 1){
        //Dir = 0;
        //UART1_Send_Command("Texto\n");
        //I2C_TX(49);
        //}
        //MOSFET´s
        if (PORTBbits.RB1 == 1 && PORTBbits.RB2 == 0 && k != 1) {
            PWMCON1 = 0x0011;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 1;
            int16_t i = 0;
            for (i = 0; i <= 610; i++) {
                PDC1 = i;
                __delay_ms(4);
            }
            k = 1;
            //            PDC1 = 0;
            //            __delay_ms(500);
            //            PDC1 = 122;
            //            __delay_ms(500);
            //            PDC1 = 244;
            //            __delay_ms(500);
            //            PDC1 = 366;
            //            __delay_ms(500);
            //            PDC1 = 488;
            //            __delay_ms(500);
            //            PDC1 = 610;
            //            PDC1 += 10; 
            //            DTCON1 += 1;
            //            __delay_ms(500);
        }
        if (PORTBbits.RB2 == 1 && PORTBbits.RB1 == 0 && k != 2) {
            PWMCON1 = 0x0011;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 0;
            int16_t i = 0;
            for (i = 900; i >= 190; i--) {
                PDC1 = i;
                __delay_ms(4);
            }
            k = 2;
            //            PDC1 = 900;
            //            __delay_ms(500);
            //            PDC1 = 732;
            //            __delay_ms(500);
            //            PDC1 = 610;
            //            __delay_ms(500);
            //            PDC1 = 488;
            //            __delay_ms(500);
            //            PDC1 = 366;
            //            __delay_ms(500);
            //            PDC1 = 244;
            //            __delay_ms(500);
            //            PDC1 = 190;
            //PDC1 -= 10;
            //DTCON1 -= 1;
            //__delay_ms(500);
        }
        if (((PORTBbits.RB1 == 0) && (PORTBbits.RB2 == 0)) || ((PORTBbits.RB1 == 1) && (PORTBbits.RB2 == 1))) {
            //PDC1  -= 10;
            //DTCON1 += 10;
            PWMCON1 = 0x0000;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 0;
            k = 3;
            __delay_ms(10);
        }
    }
    return 0;
}


