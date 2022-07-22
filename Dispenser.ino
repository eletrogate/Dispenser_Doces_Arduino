/*
 * Dispenser de doces com arduino
 * Autor: Miguel Sena
 * blog.eletrogate.com
 */

#include <Stepper.h> //Inclusão da biblioteca

byte estoque = 7; //Define a capacidade
const int spr = 500; //Define a quantidade de passos por rotação do motor
Stepper mot(spr, 8, 10, 9, 11); //Cria o objeto do motor, de acordo com os parâmetros

void setup() {
  mot.setSpeed(60); //Defien a velocidade do motor
  pinMode(2, OUTPUT); //Define os leds como saída
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP); //Define o botão como entrada
  acende_leds(estoque); //Chama a função que controla os leds
}

void loop() {
  byte estado = digitalRead(7); //Lê o estado do botão

  if (!estado) {  //Caso o botão seja pressionado e o estoque for maior que 0:
    if (estoque > 0) {
      mot.step(-256); //Move o motor
      estoque--; //Diminui uma unidade do estoque
      acende_leds(estoque); //Chama a função dos leds
      delay(1000);  //Atraso de 1 segundo
    }
  }
}

void acende_leds(byte estoque) { //Função dos leds, recebe um número como parâmetro
  byte capacidade_leds[] = {1, 2, 3, 3, 4, 4, 5, 5}; //Quantos leds serão acesos ao depender da quantidade de doces no estoque (o estoque varia de 0 a 7)
  byte entradas_leds[] = {2, 3, 4, 5, 6}; //Pinos onde estão os leds

  for (byte x = 0; x <= 6; x++) { //Desliga todos os leds
    digitalWrite(entradas_leds[x], LOW);
  }

  for (byte i = 0; i < capacidade_leds[estoque]; i++) { //Liga os leds de acordo com o valor da capacidade atual
    digitalWrite(entradas_leds[i], HIGH);
  }
}