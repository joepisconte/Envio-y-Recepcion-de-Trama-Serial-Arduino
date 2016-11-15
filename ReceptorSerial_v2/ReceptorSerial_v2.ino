/* Recepción de Trama Serial haciendo uso de interrupción por puerto serial.
 * Interrupción por puerto Serial no es compatible con Arduino Leonardo, Esplora o Micro. 
 * Se espera un mensaje en el formato: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 * Este programa requiere un $(dolar) para indicar el final de la trama
 */

const int NUMERO_DE_DATOS = 6;    // numero de datos esperados
int fieldIndex = 0;               // el actual campo que está siendo recibido
String values[NUMERO_DE_DATOS];   // array que contiene los valores de todos los datos en formato String

float Datos_Recibidos[NUMERO_DE_DATOS];
boolean datos_disponibles = false;

void setup()
{
  Serial.begin(9600);       // inicializa el puerto serial a 9600 baudios
  pinMode(13,OUTPUT);       // Seteamos el PIN 13 como salida
}

void loop()
{
 if(datos_disponibles == true){
   digitalWrite(13,HIGH);  // encendemos el led del pin 13 para indicar que hemos recibido datos
   delay(250);
   digitalWrite(13,LOW);  // apagamos el led
   datos_disponibles == false; 
 }
}

void serialEvent() {  // Interrupción del puerto Serial. Función que es llama dentro del loop cuando
                      // nuevos caracteres por el puerto serial.
  while (Serial.available()) {
    char ch = Serial.read(); // Lee un caracter el buffer del puerto serial
    if(ch >= '0' && ch <= '9' || ch == '-' || ch == '.' || ch == ' ')    
    // Si ... el dato el caracter esta entre el '0' - '9' y o es '-','.' o ' ' ... entonces  
    {
     values[fieldIndex] = values[fieldIndex] + ch;  // acumula el valor en el campo respectivo
    }else 
         if (ch == ',') // si ... detecta coma ...entonces
         {
             if(fieldIndex < NUMERO_DE_DATOS-1)
               fieldIndex++; // incrementa el índice del siguiente campo, siempre que, fieldIndex sea menor que 29
             }
         else
         { 
           //cualquier caracter diferente (a un número, punto o coma) termina la adquisición
           //ese caracter sería el "$"
           for(int i=0; i <= fieldIndex; i++)
           { 
            //////////////////////////////////////////////////////////////////////////////////
            //////////  Convierte los caracteres recibidos en variables tipo float ///////////
            //////////////////////////////////////////////////////////////////////////////////
            Datos_Recibidos[i] = values[i].toFloat();
            //////////////////////////////////////////////////////////////////////////////////
            datos_disponibles = true;
            values[i] = '0'; // setea los valores a 0 para almacenar nuevo dato
           }
           fieldIndex = 0; // listo para empezar de nuevo
         }
       
  }
}
