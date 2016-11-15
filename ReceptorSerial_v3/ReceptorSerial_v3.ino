/* Recepción de Trama Serial haciendo uso de interrupción por puerto serial.
 * Primero captura la trama serial en una variable tipo String y luego 
 * la analiza con la función AnalizarTramaSerial()
 * Se espera un mensaje en el formato:  12.50, -15.60,  26.00, 132.50,   3.60,  27.10$
 * Este programa requiere un $(dolar) para indicar el final de la trama
 * Interrupción por puerto Serial no es compatible con Arduino Leonardo, Esplora o Micro. 
 * Trama Serial de Prueba (240 caracteres --> 30 número tipo float):  
 *  87.89, -89.67, -57.54,  17.96, -28.13,  48.01,  75.33,  62.01,  -2.75, -18.97, -39.11,  16.52,  47.23,  65.26, -41.15,  -2.59, -82.25,  50.88, -97.30,  44.44,  70.12,  39.40,  47.11,  74.62, -97.52,  28.90, -92.81, -33.87, -22.03, -62.69$
 */

String Trama = ""; // almacenamos los caracteres recibidos en la variable Trama para liberar el buffer de recepción.
const int NUMERO_DE_DATOS = 30;    // numero de datos esperados (no considerar más de 30 datos, ya que la memoria dinámica del Arduino UNO es sólo de 2KB) 
float Datos_Recibidos[NUMERO_DE_DATOS];  //array de número tipo float
boolean datos_disponibles = false;
boolean final_de_trama = false;
                

void setup()
{
  Serial.begin(9600);       // inicializa el puerto serial a 9600 baudios
}

void loop()
{
 if (final_de_trama == true) {
    //Serial.println(Trama);
    AnalizarTramaSerial(Trama);
    if(datos_disponibles == true){
      // Procesamos los datos almacenados en Datos_Recibidos[]
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
 * con un formato del tipo:  12.50, -15.60,  26.00, 132.50,   3.60,  27.10$
 */
   const int TAMANO_DE_TRAMA = trama_serial.length();
   int fieldIndex = 0; // índice inicial de los campos recibidos.
   String Datos[NUMERO_DE_DATOS]; // array que contendrá los valores de cada uno de los campos
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
            Datos_Recibidos[i] = Datos[i].toFloat();
            Serial.println(Datos_Recibidos[i]);  // <---- comentar luego de realizar las pruebas
            //////////////////////////////////////////////////////////////////////////////////
            datos_disponibles = true;
            }
       }
     }
   }
}

