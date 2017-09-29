#include "mbed.h"
SPI spi(D11, NC, D13); // mosi, miso, sclk
DigitalOut cs(D2);
int cmd = 0x11;
int main()
{
  cs = 1;
  spi.format(8,3);
  spi.frequency(1000000);
  while(1) {
    for (int i = 0x00; i < 0xFF; i++) {
      cs = 0;
      spi.write(cmd);
      spi.write(i);
      cs = 1;
    }
    for (int i = 0xFF; i>=0x00; i--) {
      cs = 0;
      spi.write(cmd);
      spi.write(i);
      cs = 1;
    }
  }
}
