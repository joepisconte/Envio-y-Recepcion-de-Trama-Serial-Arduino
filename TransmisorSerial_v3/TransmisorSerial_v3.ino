/* Programa de Test de envío de trama serial V3
 * Convierte número flotantes en cadenas de caracteres y los envía 
 * por el puerto serial armando una trama separada por comas.
 * Usa la función EnviarTramaSerial()
 * La trama debe tener el formato: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 * En este ejemplo cada número consta de siete caracteres, por lo cual
 * se pueden enviar números en el rango de -999.99 a 9999.99
 * La trama enviada requiere de un dolar "$" para indicar el final de la trama
 */

const int NUMERO_DE_DATOS = 6;
float datos [NUMERO_DE_DATOS];  //almacenará los valores de las variables tipo float.

void setup()
{
  Serial.begin(9600);  // inicializa el puerto serial a 115200 baudios
  datos[0] = 12.5;  // Humedad
  datos[1] = -15.6; // Temperatura
  datos[2] = 26.0;  // Presion
  datos[3] = 132.5; // Proximidad
  datos[4] = 3.6;   // Peso
  datos[5] = 27.1;  // Torque 
}
void loop()
{                                      
                       
  EnviarTramaSerial(datos,NUMERO_DE_DATOS); // datos, es un array del tipo float
                                            // y NUMERO_DE_DATOS es la cantidad de variables que vamos a transmitir.
  delay(10000);  //repetimos cada diez segundos
}

void EnviarTramaSerial(float flotantes[], int Num_Datos){
  for (int i=0 ; i < Num_Datos ; i++){
    char bufferr[7];
    dtostrf(flotantes[i], 7, 2, bufferr);  // Usar un buffer para convertir de float a string 
    Serial.print(bufferr);
    if (i == (Num_Datos - 1)){ // Si ... es el último dato ... entonces ... escribe un "$" para finalizar la trama
       Serial.print("$");      
    }else{                     // Caso contrario escribe una ","
      Serial.print(",");  
    }
  }
}

