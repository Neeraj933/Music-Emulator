/*test program to check the performance of the potentiometer when the motion of the person is detected*/
#include "mbed.h"                          //include the mbed library
SPI spi(D11, NC, D13);                     // mosi, miso, sclk
DigitalIn pir(D3);                         //set D3 pin as input from PIR sensor
DigitalOut cs(D2);                         //set D2 pin as output to chip-select of the digital potentiometer
int cmd = 0x11;                            //set command byte to 0x11 which determines the IC operation
//a fucntion to adjust the potentiometer 
void pot(int level) {
  cs = 0;                                  //select the chip
  spi.write(cmd);                          //transfer the command byte to the potentiometer through SPI bus
  spi.write(level);                        //transfer the resistance value to be set in potentiometer
  cs = 1;                                  //deselect the chip
}
int main() {
  cs = 1;                                  //deselect the chip
  spi.format(8,3);                         //default information transfer format
  spi.frequency(1000000);                  //setting the frequency to 1MHz
  pot(0x00);                               //initializing the potentiometer wiper to have zero resistance
  while(1) {
    if (pir == 1) {                        //checking if the presence is true
      for (int i = 0x00; i <= 0xFF; i++) { //the resistance is increased in steps of 1 starting from 0 upto 255(0xFF)
        pot(i);                            //call the potentiometer function
        wait(0.01);                        //wait for 0.01s
      }
    }
    if (pir == 0) {                        //checking if the presence is false
      for (int i = 0xFF; i >= 0x00; i--) { //the resistance is decreased in steps of 1 starting from 255(0xFF) upto 0
        pot(i);                            //call the potentiometer function
        wait(0.01);                        //wait for 0.01s
      }
    }
  }
}
 
