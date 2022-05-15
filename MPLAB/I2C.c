/*
 * File:   I2C.c
 * Author: Oscar Daniel Rodriguez Gallego
 *
 * Created on 27 de septiembre de 2021, 06:42 PM
 */

/*
 * Esta libreria fue hecha de la explicacion de la familia dspic30f secion 21 
 */
#include <p30F4011.h>
#include "I2C.h"                                                                        

uint16_t setBaudRate(void)
{   
  /*
   * esta funcion calcula el baaud rate pag 562
   * FCY = frecuencia de ciclo de instruccion
   *  FSCL = Frecuencia requereida 
   */
    return  ((FCY/FSCL) - (FCY/1111111)) - 1;
}

void Init_I2C(void)
{
    //page 557
    //I2CADD = 0;
    I2CCONbits.SCLREL  = 0; // Enable clock stretching
    I2CCONbits.STREN   = 1; // Enable clock stretching
    I2CADD =20; // DIrección del esclavo
    I2CBRG = setBaudRate();    
    __delay_ms(1);
    I2CCONbits.I2CEN   = 1;
    INTCON1bits.NSTDIS = 0; // Permite interrupciones anidadas
    IPC3bits.SI2CIP = 0x05; // Prioridad de la interrupcion
    IFS0bits.SI2CIF = 0;    // limpia la interrupcion de tranferencia completa
    IEC0bits.SI2CIE = 1;
}

void I2C_Start(void)
{
    IFS0bits.MI2CIF = 0; // Se apaga la interruccion
    I2CCONbits.SEN = 1; /// se habilita la operacion del I2C e idica el comienzo 
    while( IFS0bits.MI2CIF == 0); // se convierte en 1 cuando se envio la condicion de START
}

void I2C_Stop(void)
{
    IFS0bits.MI2CIF = 0; // Se apaga la interruccion
    I2CCONbits.PEN = 1; /// se habilita la operacion del I2C e indca el final 
    while( IFS0bits.MI2CIF == 0); // se convierte en 1 cuando se envio la condicion de START
}
void I2C_Restart(void)
{
    I2CCONbits.RSEN = 1;
    while (I2CCONbits.RSEN == 1); 
}
void I2C_ACK(void)
{
    IFS0bits.MI2CIF = 0; // Se apaga la interruccion
    I2CCONbits.ACKEN = 1; // Iniciar la secuencia de reconocimiento en los pines SDA y SCL y transmitir el bit de datos ACKDT
    I2CCONbits.ACKDT = 0; // Enviar ACK durante el reconocimiento
    while( IFS0bits.MI2CIF == 0); // se convierte en 1 cuando se envio la condicion de START
}

void I2C_NACK(void)
{
    IFS0bits.MI2CIF = 0; // Se apaga la interruccion
    I2CCONbits.ACKEN = 1; // Iniciar la secuencia de reconocimiento en los pines SDA y SCL y transmitir el bit de datos ACKDT
    I2CCONbits.ACKDT = 1; // Enviar NACK durante el reconocimiento
    while( IFS0bits.MI2CIF == 0); // se convierte en 1 cuando se envio la condicion de START
}
void I2C_TX(char data)
{
    IFS0bits.MI2CIF = 0; // Se apaga la interruccion
    I2CTRN = data;
    while( IFS0bits.MI2CIF == 0); // se convierte en 1 cuando se envio la condicion de START 
}
char I2C_RX(void)
{
    IFS0bits.MI2CIF = 0; // Se apaga la interruccion
    I2CCONbits.RCEN = 1; // Habilita la recepcion de datos 
    while( IFS0bits.MI2CIF == 0); // se convierte en 1 cuando se envio la condicion de START 
    return I2CRCV;
}