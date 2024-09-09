/* Código para autoconfigurar el ajustador de voltaje 
a 253V como tensión de sobrevoltaje, solo en caso 
de que se vaya completamente la luz en toda su zona
y el aparato se reinicie "perdiendo la configuración"
*/
#define BODCR _SFR_IO8(0x30) //Definimos la dirección de registro directamente de BODCR ya que en el core del ATTINY que estoy usando no lo han definido.

int botonpulsadotime = 300;                   //Tiempo que estará el botón en HIGH
int tiempoesperaentrepulsacion = 300;         //Tiempo delay() entre pulsación botón abajo y despúes de entrar al menú config
int valortensionsubidacorte = 253;            //Se cortará si sube la tensión a 253V ya que es la que se considera subida tensión en reglamento baja tensión (cambiar valor si se desea modificar)- 10% de 230V
int pinset = 1;                               //Indicamos el pin donde estará el set, PB1 (en el datasheet PIN 6)
int pinabajo = 3;                             //Indicamos el pin botón abajo, PB3 (en el datasheet PIN 2)

void setup() {
  //Inicializamos los pines a usar
  pinMode(pinset, OUTPUT); //Este irá al SET
  pinMode(pinabajo, OUTPUT); //Este irá al botón "abajo"


  ////INICIO DEL PROGRAMA - Código que ejecutaremos SOLO al inicio unos segundos después que se haya ido la luz
  delay(15000); //Tiempo que esperamos despúes de reestablecerse la luz para que el aparato esté encendido completamente: 10 segundos
    
  //Presionamos SET para entrar en el menú config
  pulsar(pinset, 4000); //Pasamos el PIN que va al botón SET y se le indica que el primer delay entre HIGH y LOW van a ser 4 segundos (4000ms)
  // Ya estaríamos en P01. Ajuste del valor de tensión por sobrevoltaje

  //Botón abajo
  for (int i = 0; i < 280 - valortensionsubidacorte; i++) { //A 280V que es como viene por defecto en el SINOTIMER se le resta valortensionsubidacorte y obtendremos las veces que tenemos que iterar botón abajo
    //Con este for vamos a simular que estamos pulsando el botón "abajo" para disminuir el valor de sobretensión
    pulsar(pinabajo, botonpulsadotime);
  } // Fin del for para botón "bajar"

  //Finalizamos la configuración pulsando SET hasta llegar a P13 END, por lo que habría que pulsar SET desde P01 que está hasta P13 + 1, es decir hay que pulsarlo 13 veces
  delay(1000);
  for (int i = 1; i <= 13; i++) {
    pulsar(pinset, botonpulsadotime);
  } //Fin for para FINALIZAR config (para llegar a P13)
  ////FIN DEL PROGRAMA

  power_down_mode(); //DORMIR - Dormimos chip con nuestra función
}

void loop() {
}


void pulsar(int PIN, int tiempo) { //Nota: la variable "tiempo" puede ser o un valor entero como 5000 ms o se le puede pasar la variable botonpulsadotime. NOta2: función pulsar(PIN output, tiempoprimerdelay)
  digitalWrite(PIN, HIGH);              // Pulsamos el botón indicado en la variable PIN y lo ponemos en HIGH
  delay(tiempo);                        // Esperamos el tiempo indicado en la variable tiempo
  digitalWrite(PIN, LOW);               // Aquí soltamos el botón indicado en la variable PIN (recuerda 6 para SET y 7 para botón "abajo")
  delay(tiempoesperaentrepulsacion);    // Como su nombre indica es el tiempo que tardaríamos entre pulsación y pulsación
}

void power_down_mode(){ //Función para poner ATTINY13 a dormir profundo para bajar consumo al mínimo (según DATASHEET)
  bitWrite(ACSR,ACD,1); //Deshabilitamos comparador analógico AC para ahorrar energía
  bitWrite(ADCSRA,ADEN,0); //Deshabilita el ADC
  BODCR = B00000010; //Desactiva el Brown-out Detector (BOD) para disminuir consumo
  
  //FUNCIÓN EN C obtenida del DATASHEET para apagar el WATCHDOG TIMER (es como un contador para interrupciones por software en segundos, esto consume energía)
  noInterrupts(); //DORMIR - Esto es para deshabilitar todas las interrupciones y poder deshabilitar el Watchdog timer
  asm("wdr"); //Reset Watchdog Timer
  /* Clear WDRF in MCUSR */
  MCUSR &= ~(1<<WDRF);
  /* Write logical one to WDCE and WDE */
  /* Keep old prescaler setting to prevent unintentional time-out */
  WDTCR |= (1<<WDCE) | (1<<WDE);
  /* Turn off WDT */
  WDTCR = 0x00;
  interrupts();
  //FIN función apagado Watchdog timer (WDT)

  MCUCR = B00110000; //Habilita el modo sleep y define el tipo (power down mode), en este modo el oscilador se para y solo funcionan el Watchdog Timer (si no lo hemos apagado) y las interrupciones externas
  asm("sleep"); //Pone el microcontrolador a dormir
}
