/*Maria Eduarda 
24/02/2025
Atividade: Exercicio Matematica
*/

  int numeroA = 500;
  int resultado = 0;
  int valor  = 0;
  int valor1 = 5;
  int valor2 = 2;
  float resultadoReal= 0;
    
 void setup()

    
{ 
    // ATIVIDADE 1
  
  Serial.begin (96000);
   
  resultado = map (500,0,1023,0,100);
  Serial.println(resultado);
  
  resultado = constrain(resultado, 20 ,80);
  Serial.println(resultado);
  
  
  // ATIVIDADE 2
  
  int valor  = 0;
  
  valor ++; 
  Serial.println(valor);
  valor ++; 
  Serial.println(valor);
  valor ++;
  Serial.println(valor);
  valor ++; 
  Serial.println(valor);
  valor ++; 
  Serial.println(valor); 
  valor ++; 
  Serial.println(valor);
  valor ++; 
  Serial.println(valor);
  valor ++; 
  Serial.println(valor);
  valor ++; 
  Serial.println(valor);
  valor ++; 
  Serial.println(valor);
   
   
  valor --;
  Serial.println(valor);
  valor --; 
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);
  valor --;
  Serial.println(valor);  
  
  
   //ATIVIDADE 3

    
  resultado = valor1 + valor2;
  Serial.println(resultado);
  
  resultado = resultado/2;
  Serial.println(resultado);
   
   resultado = valor1 + valor2;
   
    resultado = (float)resultado/(float)2;
  Serial.println(resultado);
   

  
}

void loop()
{
}