# Introducción

Por necesidad y urgencia se decidió adquirir por Aliexpress un protector de sobretensiones transitorias SINOTIMER. Al ver que no se mencionaba ni en la ficha del producto ni en las instrucciones nada referente a si tiene memoria para guardar los ajustes que se establezcan, me decidí a crear un pequeño chip para que en caso de que se fuera la luz por completo, el aparato se reajustara automáticamente.

## Funcionamiento (Idea)

Se supuso ante el peor de los casos que el aparato no contaría con memoria interna, por lo que partí de que la propia alimentación continuada del dispositivo haría que mantuviese los ajustes (253V como máximo de sobretensión, un 10% por encima de la tensión nominal según reglamento de baja tensión, es decir, un 10% de 230V para España). 

Lo que se propone en este proyecto es crear un pequeño chip que se conecte como un pequeño vampiro a los botones del aparato SET y DOWN (ya que queremos bajar la que viene por defecto de 280V a 253V). Para ello se idea el siguiente circuito:

<div align="center">
	<img src="https://github.com/user-attachments/assets/c0d10671-a0d8-4080-a674-5a804480ca11">
</div>

Como podemos ver cuenta con 3 pines en la zona superior y dos en la inferior, las dos inferiores deberán ir al GND y a la salida de un regulador de voltaje del SINOTIMER que proporcione alimentación de 5V, por ejemplo uno que lo proporciona es el que alimenta el microcontrolador interno del aparato para comprobar las diferencias de tensión y activar relés. El chip aquí presentado es sencillo, consiste en dos optoacopladores que se activarán según una secuencia indicada por nuestro microcontrolador ATTINY13. Esta secuencia solo se ejecutará una única vez al alimentar el aparato (SINOTIMER), luego se bajará la alimentación para que el chip quede en un estado de consumo mínimo.
## Conexiones chip:
<div align="middle">
  <img src="https://github.com/user-attachments/assets/78dd3d2e-87bc-4c5f-9962-ad5c0ee2d4a8" />
</div>

### Esquemático circuito:
<div align="center">
  <img src="https://github.com/user-attachments/assets/8bd4044a-5b6c-461a-b799-559b531f3468" /> 
</div>

# Resultado
## Video
https://github.com/user-attachments/assets/58d54a43-12a8-4bbd-b895-d1b470230cda

## Resultado final una vez fabricada la pcb
Aunque es una versión anterior sin el tercer pin de arriba (común botones), funciona exactamente igual (va a común del aparato, que debe ser el mismo para todos, solo que al estar el chip aislado por los optoacpoladores, se optó por el nuevo diseño para tener el mínimo impacto en la pcb del microcontrolador del SINOTIMER, de esta manera, es como si pulsásemos los botones nosotros mismos.

https://github.com/user-attachments/assets/2a9f2775-4988-4b48-812e-7c7adac6edf6

# Moraleja de toda esta historia
Finalmente tras haber desarrollado este pequeño sistema, no fue necesario implementarlo, pues el SINOTIMER que recibí sí que cuenta con memoria en caso de que se quede totalmente sin alimentación. Aún así he decidido subir este proyecto pues podría ser muy útil para otros aparatos, por ejemplo un temporizador para una lavadora antigua, juguetes infantiles que cuenten con botonera, como pequeño interruptor para circuitos de mayor voltage (ya que los extremos de los octoacopladores están totalmente aislados del ATTINY13). En el caso del modelo P817 utilizado para este chip, soporta hasta 35V colector-emisor o 6V emisor-colector (y el aislamiento que aguantan entre Anodo/Catodo - Emisor/Colector es de 5000V por lo que no se estropearía el chip, solo los optoacopladores):

<div align="center">
  <img src="https://github.com/user-attachments/assets/4d0437a7-99ab-4fbe-bbfe-a2a3ec8163de" /> 
</div>

## Extra: Para mí lo más importante
Para el modo "deep sleep" no encontré mucha información en internet y lo poco que encontraba no me gustaba. Finalmente a partir del datasheet, adapté mi propio código para el ATTINY13A.
