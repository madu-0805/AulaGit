#include <Arduino.h>
#include <TFT_eSPI.h>
#include "imagem.h"
TFT_eSPI tft;

void setup()
{
    tft.init();                          // inicia o dispaly
    tft.setRotation(2);                  // rotaciona o conteudo do dispaly
                                         /*CORES PADROES
                                         //*BLACK
                                         //*BLUE
                                         //*RED
                                         //* GREEN
                                         //* CYAN
                                         //*MAGENTA
                                         //* WHITE
                                         //* ORGANGE
                                         //* PINK
                                         //* PURPLE
                                         //* GREY
                                          */
    tft.fillScreen(TFT_SKYBLUE);         //* altera a cor de fundo
    tft.setTextColor(TFT_BLACK);         //* Cor do texto
    tft.setTextFont(2);                  //* Seleciona a Font
    tft.drawString("Ola Mundo", 10, 10); //* "Texto", posicao x , posicao y

    tft.setCursor(10, 40);
    int idade = 18;
    tft.printf("idade = %d", idade);

    //! RETANGULOS
    //! Desenho (x1,y1,x2, y2, cor)
    // tft.drawRect(10, 50, 100, 10, TFT_RED);// desenha um retagulo (apenas  linha)
    // tft.fillRect(10, 50, 100, 10, TFT_RED); // desenha um retagulo preenchido
    //  tft.drawRoundRect(10, 70, 200, 50, 10, TFT_RED); //* (x1,y1,x2,y2, raio, cor)
    //  tft.fillRoundRect(10, 70, 200, 50, 10, TFT_RED); //* (x1,y1,x2,y2, raio, cor)

    //! CIRCULOS
    // tft.drawCircle(120, 120, 30, TFT_GOLD);// (x,y,raio, cor)
    //  tft.drawCircle(120, 120, 30, TFT_GOLD);// (x,y,raio, cor)

    //! TRIANGULO

    // tft.drawTriangle(10, 200, 200, 200, 100, 100, TFT_GREEN);

    // tft.drawTriangle(10, 200, 200, 200, 100, 100, TFT_GREEN);
     tft.pushImage(0, 0, 240, 240, gato);
}

void loop()
{
}
