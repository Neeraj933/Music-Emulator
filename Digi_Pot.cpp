/*This is the program to interface Digital Potentiometer and Mbed board*/
/*The potentiometer IC used is MCP41010 which has Active LOW chip selector, serial clock and serial data pins*/
#include "mbed.h"
SPI spi(D11, NC, D13);                   // mosi, miso, sclk
DigitalOut cs(D2);                       //set D2 pin as output to chip-select of the digital potentiometer
int cmd = 0x11;                          //set command byte to 0x11 which determines the IC operation
//a function to adjust the potentiometer
void pot(int level) {
  cs = 0;                                //select the chip
  spi.write(cmd);                        //transfer the command byte to the potentiometer through SPI bus
  spi.write(level);                      //transfer the resistance value to be set in potentiometer
  cs = 1;                                //deselect the chip
}
int main() {
  cs = 1;                                //set chip-select pin such that it is deselected initially
  spi.format(8,3);                       //set spi format to 8-bit and mode 3
  spi.frequency(1000000);                //set spi frequency to 1MHz
  while(1) {
    for (int i = 0x00; i <= 0xFF; i++) { //the resistance is increased in steps of 1 starting from 0 upto 255(0xFF)
      pot(i);                            //call the potentiometer function
      wait(0.01);                        //wait for 0.01s
    }
    for (int i = 0xFF; i >= 0x00; i--) { //the resistance is decreased in steps of 1 starting from 255(0xFF) upto 0
      pot(i);                            //call the potentiometer function
      wait(0.01);                        //wait for 0.01s
    }
  }
}
