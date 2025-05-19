/*Maria Eduarda Silva
14/03/2025
ATIVIDADE: entradas analogicas
aula 37
*/

void setup()
{
  Serial.begin(96000);
}

void loop()
{
  int temperatura = analogRead(A0);
 
  // licao 1 
   
  /*   int bateria = analogRead(A0);
  bateria = map(bateria, 0, 1023,0,100);
  Serial.println(bateria);
  */
  
  if (temperatura <=164)
   Serial.println("muito Frio");
  
  else if(temperatura > 164 && temperatura <= 348)
   Serial.println("frio");
    
  else if (temperatura > 348 && temperatura <=696)
    Serial.println("normal");
 
    else if(temperatura >696 && temperatura <= 859)
   Serial.println("quente");
  
    else
    Serial.println("muito quente");
    
  
  
}