#include "mbed.h"
SPI spi(D11, NC, D13);                  // mosi, miso, sclk
DigitalOut cs(D2);                      //set D2 pin as output to chip-select of the digital potentiometer
int cmd = 0x11;                         //set command byte to 0x11
int main()
{
  cs = 1;                               //set chip-select
  spi.format(8,3);                      //set spi format to 8-bit and mode 3
  spi.frequency(1000000);               //set spi frequency to 1MHz
  while(1) {
    
    for (int i = 0x00; i < 0xFF; i++) { //the resistance is increased in steps of 1 starting from 0 upto 255(0xFF)
      cs = 0;                           //reset chip-select 
      spi.write(cmd);                   //write the command byte onto spi bus
      spi.write(i);                     //set the spi data to i
      cs = 1;                           //set the chip-select
      wait(0.01);                       //wait for 0.01s
    }
    
    for (int i = 0xFF; i>=0x00; i--) {//the resistance is decreased in steps of 1 starting from 255(0xFF) upto 0
      cs = 0;                           //reset chip-select 
      spi.write(cmd);                   //write the command byte onto spi bus
      spi.write(i);                     //set the spi data to i
      cs = 1;                           //set the chip-select
      wait(0.01);                       //wait for 0.01s    }
  }
}
