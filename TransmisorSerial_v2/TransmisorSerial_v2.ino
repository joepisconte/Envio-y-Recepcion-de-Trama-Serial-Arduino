/* Programa de Test de envío de trama serial
 * La trama debe tener el formato: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 * Se sugiere que la cantidad de caracteres entre cada coma "," sea el 
 * mismo para mantener un orden(esto puede variar sin generar error en el progama).
 * En este ejemplo cada número consta de cinco caracteres, por lo cual
 * se pueden enviar números en el rango de -99.9 a 999.9
 * La trama enviada requiere de un dolar "$" para indicar el final de la trama
 */

float Humedad = 12.5;
float Temperatura = -15.6;
float Presion = 26.0;
float Proximidad = 132.5;
float Peso = 3.6;
float Torque = 27.1;

const int NUMERO_DE_DATOS = 6
String datos [NUMERO_DE_DATOS]; //almacenará los valores de las varibles flotantes en formato String. 

void setup()
{
  Serial.begin(9600);        // inicializa el puerto serial a 115200 baudios
}
void loop()
{
  ////////////////////////////////////////////////
  ///////// Conversion de Floar a String /////////           
  ////////////////////////////////////////////////
  
  char buffer1[7];
  dtostrf(Humedad, 7, 2, buffer1);  // Usar un buffer para convertir de float a string 
  datos[0] = buffer1;
            
  char buffer2[7];
  dtostrf(Temperatura, 7, 2, buffer2);  
  datos[1] = buffer2;
            
  char buffer3[7];
  dtostrf(Presion, 7, 2, buffer3);  
  datos[2] = buffer3;
            
  char buffer4[7];
  dtostrf(Proximidad, 7, 2, buffer4);  
  datos[3] = buffer4;
            
  char buffer5[7];
  dtostrf(Peso, 7, 2, buffer5);  
  datos[4] = buffer5;
            
  char buffer6[7];
  dtostrf(Torque, 7, 2, buffer6);  
  datos[5] = buffer6;

  ////////////////////////////////////////////////
  //////////////// Armado de Trama ///////////////           
  //////////////////  Opcion 1  //////////////////           
  Serial.print(datos[0]);
  Serial.print(",");
  Serial.print(datos[1]);
  Serial.print(",");
  Serial.print(datos[2]);
  Serial.print(",");
  Serial.print(datos[3]);
  Serial.print(",");
  Serial.print(datos[4]);
  Serial.print(",");
  Serial.print(datos[5]);
  Serial.print("$");
  /////////////////// - FIN - ////////////////////
  /*
  //////////////// Armado de Trama /////////////// 
  //////////////////  Opcion 2  ////////////////// 
  for (int i=0 ; i<NUMERO_DE_DATOS ; i++){
    Serial.print(datos[0]);
    if (i==NUMERO_DE_DATOS-1){
       Serial.print("$");  
    }else{
      Serial.print(",");  
    }
  }
  /////////////////// - FIN - ////////////////////
  */
  delay(10000);  //repetimos cada diez segundos
}
