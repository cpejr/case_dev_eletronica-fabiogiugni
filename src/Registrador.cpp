#include "Registrador.hpp"

//construtor

REGISTRADOR::REGISTRADOR(uint8_t _Data, uint8_t _Clk, uint8_t _Latch)
{
  datapin = _Data;
  srclkpin = _Clk;
  rclkpin = _Latch;
  initializePins();
}

//métodos privados
void REGISTRADOR::initializePins()
{
  pinMode(datapin, OUTPUT);
  pinMode(srclkpin, OUTPUT);
  pinMode(rclkpin, OUTPUT);

  digitalWrite(datapin, LOW);
  digitalWrite(srclkpin, LOW);
  digitalWrite(rclkpin, LOW);
}

void REGISTRADOR::clock()
{
  digitalWrite(srclkpin, HIGH);
  delayMicroseconds(500);
  digitalWrite(srclkpin, LOW);
  delayMicroseconds(500);
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
  // Vamos agora enviar todos os 16 bits para os dois registradores em série
  for (int i = 15; i >= 0; i--) // Percorre de 15 (MSB) até 0 (LSB)
  {
    digitalWrite(datapin, (dataRegister >> i) & 1); // Envia o bit mais significativo
    clock(); // Pulso de clock para mover o dado para o próximo flip-flop
  }
}

//métodos públicos

void REGISTRADOR::sendToShiftRegister(uint16_t data) // Recebe um uint16_t
{
  dataRegister = data; // Armazena o valor de 16 bits no registrador
  serialToParallel();  // Envia os 16 bits para os registradores em série
  store();             // Armazena os dados nos registradores
}

void REGISTRADOR::printData()
{
  Serial.println(dataRegister, BIN); // Imprime o valor do registrador em formato binário
}
