#include "mbed.h"
SPI spi(D11, NC, D13);
DigitalIn pir1(D4);
DigitalIn pir2(D5);
DigitalOut cs1(D2);
DigitalOut cs2(D3)
int cmd = 0x11;
void pot1(int level1) {
  cs2 = 1;
  cs1 = 0;
  spi.write(cmd);
  spi.write(level1);
  cs1 = 1;
}
void pot2(int level2) {
  cs1 = 1;
  cs2 = 0;
  spi.write(cmd);
  spi.write(level2);
  cs2 = 1;
}
int main() {
  cs1 = 1;
  cs2 = 1;
  spi.format(8,3);
  spi.frequency(1000000);
  pot1(0x00);
  pot2(0xFF);
  while(1) {
    if (pir1 == 1) {
      int i=0x00;
      int j=0xFF;
      while(i<=0xFF && j>=0x00) {
        pot1(i);
        pot2(j);
        wait(0.01);
        i++;
        j--;
      }
    }
    if (pir2 == 1) {
      int i=0xFF;
      int j=0x00;
      while(i>=0x00 && j<=0xFF) {
        pot1(i);
        pot2(j);
        wait(0.01);
        i--;
        j++;
      }
    }
  }
}
