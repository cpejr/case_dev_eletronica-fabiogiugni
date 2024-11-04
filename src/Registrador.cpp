#include "Registrador.hpp"

//construtor

REGISTRADOR::REGISTRADOR(uint8_t _Data, uint8_t _Clk, uint8_t _Latch)
{
  datapin = _Data;
  srclkpin = _Clk;
  rclkpin = _Latch;

  pinMode(datapin, OUTPUT);
  pinMode(srclkpin, OUTPUT);
  pinMode(rclkpin, OUTPUT);

  digitalWrite(datapin, LOW);
  digitalWrite(srclkpin, LOW);
  digitalWrite(rclkpin, LOW);
}

//métodos privados

void REGISTRADOR::clock()
{
  digitalWrite(srclkpin, HIGH); //pulso clock
  delay(1);
  digitalWrite(srclkpin, LOW);
  delay(1);
}

void REGISTRADOR::store()
{
  digitalWrite(rclkpin, HIGH); //armazena o dado no registrador (pulso latch)
  delay(5);
  digitalWrite(rclkpin, LOW);
  delay(5);
}

void REGISTRADOR::serialToParallel()
{
  //envia todos os 16 bits para os dois registradores em série
  for (int i = 15; i >= 0; i--)
  {
    digitalWrite(datapin, (dataRegister >> i) & 1); // envia o bit mais significativo
    clock(); // pulso de clock para mover o dado para o próximo flip-flop
  }
}

//métodos públicos

void REGISTRADOR::sendToShiftRegister(uint16_t data) 
{
  dataRegister = data; // armazena o valor de 16 bits no registrador
  serialToParallel();  // envia os 16 bits para os registradores em série
  store();             // armazena os dados nos registradores
}

void REGISTRADOR::printData()
{
  Serial.println(dataRegister, BIN); // imprime o valor do registrador em formato binário
}
