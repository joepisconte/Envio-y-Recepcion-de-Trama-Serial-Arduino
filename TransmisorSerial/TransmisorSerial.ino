/* Programa de Test de envío de trama serial
 * La trama debe tener el formato: -12.5, 15.6, -0.7, 26.0,  3.6, 27.1$
 * Se sugiere que la cantidad de caracteres entre cada coma "," sea el 
 * mismo para mantener un orden(esto puede variar sin generar error en el progama).
 * En este ejemplo cada número consta de cinco caracteres, por lo cual
 * se pueden enviar números en el rango de -99.9 a 999.9
 * La trama enviada requiere de un dolar "$" para indicar el final de la trama
 */
void setup()
{
  Serial.begin(9600);        // inicializa el puerto serial a 115200 baudios
}
void loop()
{
  Serial.println("-12.5, 15.0, -0.7, 26.1,132.9,-28.5$");
  delay(10000);  //repetimos cada diez segundos
}
