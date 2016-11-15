/* Recepción de Trama Serial haciendo uso de interrupción por puerto serial.
 * Primero captura la trama serial en una variable tipo String y luego 
 * la analiza con la función AnalizarTramaSerial()
 * Se espera un mensaje en el formato: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 * Este programa requiere un $(dolar) para indicar el final de la trama
 * Interrupción por puerto Serial no es compatible con Arduino Leonardo, Esplora o Micro. 
 */

const int NUMERO_DE_DATOS = 6;    // numero de datos esperados
int fieldIndex = 0;               // el actual campo que está siendo recibido
String values[NUMERO_DE_DATOS];   // array que contiene los valores de todos los datos en formato String

float Datos_Recibidos[NUMERO_DE_DATOS];
boolean datos_disponibles = false;

boolean final_de_trama = false;
String Trama = "";

void setup()
{
  Serial.begin(9600);       // inicializa el puerto serial a 9600 baudios
  pinMode(13,OUTPUT);       // Seteamos el PIN 13 como salida
}

void loop()
{
 if (final_de_trama == true) {
    //Serial.println(Trama);
    AnalizarTramaSerial(Trama);
    if(datos_disponibles == true){
      digitalWrite(13,HIGH);  // encendemos el led del pin 13 para indicar que hemos recibido datos
      delay(250);
      digitalWrite(13,LOW);  // apagamos el led
      datos_disponibles == false; 
    }
    Trama = "";
    final_de_trama = false;
 } 
}

void serialEvent() {  // Interrupción del puerto Serial. Función que es llamada dentro del loop cuando
                      // ingresan nuevos caracteres por el puerto serial.
  while (Serial.available()) {
    char inChar = (char)Serial.read(); // captura el nuevo byte
    Trama += inChar; // lo agrega al String Trama
    if (inChar == '$') { // Si el caracter de entrada es un "$" (dólar) activa un flag
       final_de_trama = true;
    }
    
  }
}

void AnalizarTramaSerial(String trama_serial){
/* Función que captura los datos de tipo float dentro de una trama separada por comas
 * con un formato del tipo: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 */
   const int TAMANO_DE_TRAMA = trama_serial.length();
   int fieldIndex = 0; // índice inicial de los campos recibidos.
   char Datos[NUMERO_DE_DATOS]; // array que contendrá los valores de cada uno de los campos
   char ch;
   
   char Trama[TAMANO_DE_TRAMA];
   trama_serial.toCharArray(Trama,TAMANO_DE_TRAMA);
   
   for (int i=0;i<TAMANO_DE_TRAMA;i++){
     ch = Trama[i];
     if(ch >= '0' && ch <= '9' || ch == '-' || ch == '.' || ch == ' '){ // Si ... el caracter recibido está entre 0 y 9 - .  ... entonces
       Datos[fieldIndex] = Datos[fieldIndex] + ch; //almacena el número recibido.
     } else{ 
       if (ch == ',') // Si ... detecta coma ... entonces 
       {
         if(fieldIndex < NUMERO_DE_DATOS-1){ 
          fieldIndex++; // Incrementa el índice de campo.
         }
       }
       else{ 
         //cualquier caracter diferente (a un número o coma) termina la adquisición, ese caracter sería el "$"
         for(int i=0; i <= fieldIndex; i++)
            { 
            //////////////////////////////////////////////////////////////////////////////////
            //////////  Convierte los caracteres recibidos en variables tipo float ///////////
            //////////////////////////////////////////////////////////////////////////////////
            Datos_Recibidos[i] = values[i].toFloat();
            //////////////////////////////////////////////////////////////////////////////////
            datos_disponibles = true;
            }
       }
     }
   }
}

