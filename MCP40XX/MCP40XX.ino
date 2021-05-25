/*
Aster electronica
Potenciometro MCP40XXT 502E
Prueba de funcionamiento
Abstract: En este código de configura la incialización del potenciometro, se le mandará una señal de incremento cada segundo, al alcanzar su valor máximo se reinician los valores
desde cero.
Por Julio Hernandez
Conexiones: 
VDD -> A VCC puede ser 5V o 3.3V
VSS -> GND
SCL -> A5
SDA -> A4
A -> VCC
W -> Es la terminal intermedia del potenciometro
*/

//Se incluye la libreria para utilizar el protocolo i2c
 #include "Wire.h"
 //Se define la direccion del potenciometro, misma para MCP4017/4018/4019
 uint8_t MCP_Adress = 0b0101111; 
 //Se asigna una variable para el valor a enviar al pot de resolucion de 7 bits (0-128 steps)
 uint8_t STEP = 0;
 

void setup() {
  // put your setup code here, to run once:
   
  //Se inicia el bus I2C o TWI
  Wire.begin();
  //Se define la velocidad de transmision 100kHz Default
  //TWBR = 12; //400kHz
  //TWBR = 32; //200kHz
  //TWBr = 72; //100kHz
}

void loop() {
  // put your main code here, to run repeatedly:

    Wire.beginTransmission(MCP_Adress); //Se inicia la transmision con el MCP40XX
    Wire.write(STEP); //Se manda el Valor del paso
    Wire.endTransmission(); //Se finaliza la transmision
    
    STEP++; //Se aumenta el valor del paso
    if (STEP == 127) { //Si se alcanza el ultimo paso 
      STEP = 0; //Se inicia de nuevo
    }

    delay(1000); //Se genera un delay de 1s para visualizar el cambio del valor de resistencia 

}
