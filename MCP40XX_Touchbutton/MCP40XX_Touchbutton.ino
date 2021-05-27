/*
Aster electronica
Potenciometro MCP40XXT 502E
Prueba de funcionamiento
Abstract: En este código observamos el incremento gradual, en este caso hacemos la aritmética correspondiente para calcular
el valor estimado que tendrá el potenciometro en la terminal W, podemos comprobar el valor con el uso de un multimetro
puesto analógico
Por Julio Hernandez
Conexiones: 
VDD -> A VCC en 5V
VSS -> GND
SCL -> A5
SDA -> A4
A -> VCC
W -> A0
*/

//Se incluye la libreria para utilizar el protocolo i2c
 #include "Wire.h" 
 //Se define la direccion del potenciometro, misma para MCP4017/4018/4019
 uint8_t MCP_Address = 0b0101111; 
 //Se asigna una variable para el valor a enviar al pot de resolucion de 7 bits (0-128 steps)
 uint8_t STEP = 0;

 int analogPin = A0; //La terminal W del convertidor se conectara al pin A0
 float val = 0; //Se almacenara el valor leido de A0 en val 

 int inPin2 = 2; // Touchbutton conectado al pin digital 2 (aumento)
 int inPin3 = 3; // Touchbutton conectado al pin digital 3 (decremento)

void setup() {
  // put your setup code here, to run once:

  pinMode(inPin2, INPUT);    // sets the digital pin 7 as input
  pinMode(inPin3, INPUT);    // sets the digital pin 7 as input
   
  //Se inicia el bus I2C o TWI
  Wire.begin();
  //Se define la velocidad de transmision 100kHz Default
  //TWBR = 12; //400kHz
  //TWBR = 32; //200kHz
  //TWBR = 72; //100kHz

  //Se manda el valor del paso 0 al potenciometro
  Wire.beginTransmission(MCP_Address); //Se inicia la transmision con el MCP40XX
  Wire.write(STEP); //Se manda el Valor del paso
  Wire.endTransmission(); //Se finaliza la transmision

  //Se inicia puerto serial
  Serial.begin(9600);
  //Se muestra en el puerto serie el valor del primer paso
  val = analogRead(analogPin); //Se lee el valor del pin A0 y se hace la conversion a voltaje
  val = (val * 5)/(1024 - 1); //Se realiza la conversion a voltaje
  Serial.print("Voltaje = "); //Se muestra en el puerto serie el valor de voltaje 
  Serial.print(val); 
  Serial.println("[V]");
  
}

void loop() {
  // put your main code here, to run repeatedly:

    //Se leen las entradas digotales de entrada (aumneto y decremento)
    while(digitalRead(inPin2) == LOW && digitalRead(inPin3) == LOW); //Mientras no se aprieten no se hace nada
    //delay(50); Se genera un delay para el rebote en caso de ser pushbuttons
    if (digitalRead(inPin2) == HIGH) { //Se detecta si se presion la entrada 2 (aumento)
      while(digitalRead(inPin2) == HIGH); // mientras no se deje de presionar el touchbutton no se hace nada
      if (STEP < 127){ //Si el valor de STEP es menor al ultimo paso se entra al ciclo
        STEP++; //Se aumenta el valor de STEP
        MCP40XX(MCP_Address, STEP); //Se envia El valor de STEP al potenciometro 
        Imprimir(); //Se muestra en terminal el valor del pin A0
      }
    }
    else { //La entrada tres fue presionada (decremento)
      while(digitalRead(inPin3) == HIGH); // mientras no se deje de presionar el toucbutton no se hace nada
      if (STEP > 0){ //Si el valor de STEP es mayor al primer paso se entra al ciclo
        STEP--; //Se decrementa el valor de STEP
        MCP40XX(MCP_Address, STEP); //Se envia El valor de STEP al potenciometro 
        Imprimir(); //Se muestra en terminal el valor del pin A0
      }
    }
   
}

//Funcion para mandar enviar el paso al potenciometro
void MCP40XX(uint8_t MCP_Address, uint8_t STEP){
  Wire.beginTransmission(MCP_Address); //Se inicia la transmision con el MCP40XX
  Wire.write(STEP); //Se manda el Valor del paso
  Wire.endTransmission(); //Se finaliza la transmision
}

//Funcion para mostrar el valor del puerto analogico en la terminal
void Imprimir(){
  val = analogRead(analogPin); //Se lee el valor del pin A0 y se hace la conversion a voltaje
  val = (val * 5)/(1024 - 1); //Se realiza la conversion a voltaje
  Serial.print("Voltaje = "); //Se muestra en el puerto serie el valor de voltaje 
  Serial.print(val); 
  Serial.println("[V]");
}
