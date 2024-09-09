# Introducción

Por necesidad y urgencia se decidió adquirir por Aliexpress un protector de sobretensiones transitorias SINOTIMER. Al ver que no se mencionaba ni en la ficha del producto ni en las instrucciones nada referente a si tiene memoria para guardar los ajustes que se establezcan, me decidí a crear un pequeño chip para que en caso de que se fuera la luz por completo, el aparato se reajustara automáticamente.

## Funcionamiento (Idea)

Se supuso ante el peor de los casos que el aparato no contaría con memoria interna, por lo que partí de que la propia alimentación continuada del dispositivo haría que mantuviese los ajustes (253V como máximo de sobretensión, un 10% por encima de la tensión nominal según reglamento de baja tensión, es decir, un 10% de 230V para España). 

Lo que se propone en este proyecto es crear un pequeño chip que se conecte como un pequeño vampiro a los botones del aparato SET y DOWN (ya que queremos bajar la que viene por defecto de 280V a 253V). Para ello se idea el siguiente circuito:

INSERTAR IMAGEN SOBRETENSION.gif


Como podemos ver cuenta con 3 pines en la zona superior y dos en la inferior, las dos inferiores deberán ir al GND y a la salida de un regulador de voltaje del SINOTIMER que proporcione alimentación de 5V, por ejemplo uno que lo proporciona es el que alimenta el microcontrolador interno del aparato para comprobar las diferencias de tensión y activar relés. El chip aquí presentado es sencillo, consiste en dos optoacopladores que se activarán según una secuencia indicada por nuestro microcontrolador ATTINY13. Esta secuencia solo se ejecutará una única vez al alimentar el aparato (SINOTIMER), luego se bajará la alimentación para que el chip quede en un estado de consumo mínimo (ya que solo se debe ejecutar una sola vez).

INSERTAR CONEXIONES Y CIRUITO ESQUEMA Y SINOTIMER PUNTOS ALIMENTACIÓN

