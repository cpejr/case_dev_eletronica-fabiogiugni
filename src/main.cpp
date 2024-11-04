#include <Arduino.h>
#include "Registrador.hpp"

#define DATA 23
#define CLOCK 18
#define LATCH 12

#define BOTAO 25

//construtor registrador
REGISTRADOR r1(DATA,CLOCK,LATCH);
//todos leds acesos no início: 1111111111111111 em binário
uint16_t padraoLeds=65535;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(BOTAO, INPUT);
  r1.sendToShiftRegister(padraoLeds);
  delay(500);
}

void loop() {
  padraoLeds  = padraoLeds << 1; // move 1 bit pra frente (multiplica por 2)
  padraoLeds = (padraoLeds & 0xFFFE) | (digitalRead(BOTAO) & 0x01); //o ultimo bit vira o digital read do botão, que foi programado como INPUT
  r1.sendToShiftRegister(padraoLeds);
  r1.printData();
  delay(1000); // this speeds up the simulation
}
