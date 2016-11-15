/* Recepción de Trama Serial de datos separados por comas
 * Se espera un mensaje en el formato: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 * Este programa requiere un $(dolar) para indicar el final de la trama
 */
const int NUMERO_DE_DATOS = 30;   // numero de campos esperados
int fieldIndex = 0;               // el actual campo siendo reciBido
String values[NUMERO_DE_DATOS];   // array conteniendo los valores de todos los campos
void setup()
{
 Serial.begin(9600);        // inicializa el puerto serial a 115200 baudios
}
void loop()
{
 if( Serial.available())
 {
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
        Serial.println("Datos Recibidos por el Puerto Serial:");
        for(int i=0; i <= fieldIndex; i++)
        { 
         //----- Imprime los datos ----
         Serial.println(values[i]);  //reemplazar por lo que se desee hacer con cada unos de los datos
         //----------------------------
         values[i] = '0'; // setea los valores a 0 para almacenar nuevo dato
        }
        fieldIndex = 0; // listo para empezar de nuevo
      }
 }
}
