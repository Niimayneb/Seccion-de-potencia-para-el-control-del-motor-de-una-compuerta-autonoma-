# Sección de potencia para el control del motor de una compuerta autónoma
Repositorio de códigos, archivos de diseño y simulaciones del sistema.
<p align='center'>
    <img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/Modelos%203D/Acondicionamiento_3D.gif" alt="drawing" width="400"/>
    <img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/Modelos%203D/Potencia_3D.gif" alt="drawing" width="400"/>
</p>

# **Índice**   
- 1 [Diseño PCB en PROTEUS](#id1)
- 2 [Simulación PSIM](#id2)
- 3 [Resultados](#id3)

# Diseño PCB en PROTEUS <a name="id1"></a>
El diseño de las PCB de acondicionamiento y potencia se realizaron utilizando el software ARES de [PROTEUS](https://www.labcenter.com/) versión 8.6.
En la placa de acondicionamiento se incorporan los drivers IR2110, los transductores de Voltaje y corriente y el dsPIC30f4011 como se muestra en la imagen.
<p align='center'>
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/PCB/Acondicionamiento.PNG">
</p>

A continuacion los modelos 3D de la parte de acondicionamiento
<p align='center'>
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/Modelos%203D/Acondicionamiento_3D.PNG" width="400">
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/Modelos%203D/Acondicionamiento_3D_NC.PNG" width="400">
</p>

En la placa de potencia se muestran los mosfet's con sus respectivos filtros.
<p align='center'>
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/PCB/Potencia.PNG">
</p>

A continuacion los modelos 3D de la parte de potencia
<p align='center'>
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/Modelos%203D/Potencia_3D.PNG" width="411">
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PROTEUS/Modelos%203D/Potencia_3D_NC.PNG" width="389">
</p>

# Simulación PSIM <a name="id2"></a>
La simulacion de funcionamiento del sistema de puente completo tipo buck se realizó utilizando el sofware [PSIM](https://powersimtech.com/products/psim/capabilities-applications/) versión 9.1.

En la siguiente imagen se muestra el esquema para la simulacion en PSIM de funcionamiento del puente completo.
<p align='center'>
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PSIM/Im%C3%A1genes/PSIM_C.PNG">
</p>

Las siguientes dos imagenes muestan la señal de salida del sistema funcionando con un PWM del 70%, las imagenes muestran la señal al realizar el movimiento del motor a la izquierda y a la derecha respectivamente.
<p align='center'>
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PSIM/Im%C3%A1genes/PSIM_SP.PNG" width="404">
<img src="https://github.com/Niimayneb/seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/PSIM/Im%C3%A1genes/PSIM_SN.PNG" width="396">
</p>

# Resultados <a name="id3"></a>
En esta seccion se mostraran imagenes de los resultados obtenidos del proyecto con un PWM del 75%.

En las siguientes imagenes se muestran las salidas PWM del PIC para las dos direcciones de movimiento del motor
<p align='center'>
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/Salida%20pic%2070%25.png" width="400">
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/Salida%20pic%2070%25-complementairo.png" width="400">
</p>

En las siguientes imagenes se muestran las salidas PWM de los opto-acopladores utilizados para aislar el dsPIC
<p align='center'>
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/Salida%20opto%2070%25.png" width="400">
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/Salida%20opto%2070%25complementario.png" width="400">
</p>

En las siguientes imagenes se muestran las salidas PWM de los drivers para el control de los MOSFETs
<p align='center'>
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/salida%20drivers%2075%25.png" width="400">
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/salida%20drivers%2075%25complementario.png" width="400">
</p>

En las siguientes imagenes se muestra una comparacion de la salida del puente completo con una caraga de reostato con 2 Ohms y 35 Ohms respectivamente
<p align='center'>
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/PWM%20Salida%20Reostato%202%20Ohms.png" width="400">
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/PWM%20salida%20Reostao%2035Ohms.png" width="400">
</p>

En la siguientes imagenes se muestra una comparacion de la salida del puente completo con el motor pero utilizando panel con bateias y una fuente respectivamente  
<p align='center'>
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/PWM%20salida%20Motor%20y%20bateria.png" width="400">
<img src="https://github.com/Niimayneb/Seccion-de-potencia-para-el-control-del-motor-de-una-compuerta-autonoma-/blob/main/Resultados/salida%20motor%2075%25.png" width="400">
</p>
