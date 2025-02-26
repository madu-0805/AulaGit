/* Maria Eduarda
26/02/2025
Estruturas de Decisão
*/

int Valor1 = 50;
float Valor2 = 1.50;
float resultado = 0;

  

void setup()
{
 Serial.begin(9600);

  resultado = (float) Valor2 * (float) Valor2;
  Serial.print("o valor dos pesos multiplicados eh: ") ;
  Serial.println(resultado);
  
  resultado= Valor1 / resultado;
  Serial.print("a divisao desse valores eh: ");
  Serial.println(resultado);

     
     if(resultado <=  18 ){
     Serial.println("esta no peso normal");
       
       
     }else if(resultado >= 18.5 && resultado <= 24.9){
       Serial.println("peso normal");
     }else if(resultado >= 25.0&& resultado <= 29.9){
      Serial.println("excesso de peso");
     }else if ( resultado >= 30.0 && resultado <= 34.9){
        Serial.println("obesidade classe 2");
     }else if (resultado >= 35.0 && resultado <= 39.9){
        Serial.println("obesidade classe 3");
     }else {
     Serial.println(resultado);
}

  

 
}

void loop()
{
}
 