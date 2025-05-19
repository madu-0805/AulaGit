#include <Arduino.h>

//*FORMAS DE ESCREVER PALAVRAS EM C
char palavra[10] = "ola mundo";

char palavra2[10] = {'O', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', '\0'};

String palavra3 = "HOJE eh QUINTA"; // objeto

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.println(palavra);
  Serial.println(palavra2);

  strcpy(palavra, "SENAI");

  if (strcpy(palavra, "SENAI") == 0) // SE FOR IGUAL RETONA ZERO
  {
    Serial.println("SAO IGUAIS");
  }
  if (strncmp(palavra2, "OLA", 3) == 0)
  {
    Serial.println("as primeiras letras da palavra e OLA");
  }
  if (strstr(palavra2, "MUNDO"))
  {
    Serial.println("palavra MUNDO detectada");
  }
  //********** */
  Serial.println(palavra3.length());         //* retorna o numero de letras do objeto da classe string
  Serial.println(palavra3.charAt(10));       //* retorna a oitava posicao da palavra
  Serial.println(palavra3.substring(8, 13)); //* retorna a 8 ate 13 da palavra
  Serial.println(palavra3.indexOf('U'));     //* retorna a posicao da primeira ocorrencia da letra procurada
  Serial.println(palavra3.lastIndexOf('E')); //* retorna a posicao da ultima ocorrencia da letra procurada
  if (palavra3.equals("HOJE eh QUINTA"))     //* retorna verdaderio se forma iguais
    Serial.println("SAO IGUAIS");

  if (palavra3.equalsIgnoreCase("hoje eh quinta") == 1) // retorna verdadeiro sew forma iguais ignorando lertras maiusculas
    Serial.println("sao iguais ");

  if (palavra3.startsWith("HOJE") == 1) // retorna verdadeiro se a palavra comecar com determinado texto
    Serial.println("comeca  com HOJE");

  if (palavra3.endsWith("INTA") == 1) // retorna verdadeiro se a palavra terminar com determinado texto
    Serial.println("termina com INTA");

  String valor = "123";
  int valorNumerico = valor.toInt(); // retorna o valor do texto em valor numerico de "123" pata 123 (numero)

  String valor2 = "10.5";
  float valorNumerico2 = valor2.toFloat();

  String mensagem = "Valor = 50";
  int tamanho = mensagem.length(); // medir o tamanho do texto

  String extracao = mensagem.substring(8,tamanho);// extrair o numero iniciando em uma conhecida ate o fim do

int numero= extracao.toInt(); // tranfome o conteudo extraido em um numero inteiro

Serial.println(numero*2);// utilize o numero sem moderacao 

///! continuando 
palavra3.toLowerCase();
Serial.println(palavra3);// alterar todas as letras para minusulas //toLowerCase alterar todas para maiusculas
palavra3.toUpperCase();
Serial.println(palavra3);



String textoLed= "led= ON";
Serial.println(textoLed);
textoLed.replace("on"," off" ); //substitui uma palavra no texto por outra
Serial.println(textoLed);//"Led = OFF"

String novaFrase= "Texto"; //varios espaca 
novaFrase.trim();// remove os espacos do fim do texto

novaFrase.concat("adicionado");// adiciona um texto a string
Serial.println(novaFrase);




//TODO trim(), concat()
void loop()
{
}
