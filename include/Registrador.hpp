#ifndef REGISTRADOR_H
#define REGISTRADOR_H
#include <Arduino.h>

class REGISTRADOR
{
  private:
    uint8_t srclkpin = 0;    // srclk (clock) pin
    uint8_t datapin = 0;     // data pin
    uint8_t rclkpin = 0;     // rclk (latch) pin
    uint16_t dataRegister = 0;

    void initializePins();
    void clock();
    void store();
    void serialToParallel();

  public:
    REGISTRADOR(uint8_t _Data, uint8_t _Clk, uint8_t _Latch);
    void sendToShiftRegister(uint16_t data);
    void printData(); //para ver se ta printando o numero certo em binário
};

#endif
