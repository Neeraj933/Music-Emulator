/*main program for the music emulator system*/
#include "mbed.h"                     //include the mbed library
SPI spi(D11, NC, D13);                // mosi, miso, sclk
DigitalIn pir1(D4);                   //set D4 pin as input from PIR sensor 1 placed in room 1
DigitalIn pir2(D5);                   //set D5 pin as input from PIR sensor 2 placed in room 2
DigitalOut cs1(D2);                   //set D2 pin as output to chip-select of the digital potentiometer 1
DigitalOut cs2(D3);                   //set D3 pin as output to chip-select of the digital potentiometer 2
int cmd = 0x11;                       //set command byte to 0x11 which determines the IC operation
int count1 = 0;                       //assuming, no presence is detected in room 1
int count2 = 1;                       //assuming, presence is detected in room 2
//function to control potentiometer 1
void pot1(int level1) {
  cs2 = 1;                            //disable the chip 2
  cs1 = 0;                            //enable the chip 1
  spi.write(cmd);                     //transfer the command byte to the potentiometer 1
  spi.write(level1);                  //transfer the resistance value to be set in potentiometer 1
  cs1 = 1;                            //disable chip 1
}
//function to control potentiometer 2
void pot2(int level2) {
  cs1 = 1;                            //disable chip 1
  cs2 = 0;                            //enable chip 1
  spi.write(cmd);                     //transfer the command byte to the potentiometer 2
  spi.write(level2);                  //transfer the resistance value to be set in potentiometer 2
  cs2 = 1;                            //disable chip 2
}
int main() {
  cs1 = 1;                            //disable chip 1
  cs2 = 1;                            //disable chip 2
  spi.format(8,3);                    //default information transfer format
  spi.frequency(1000000);             //set the transfer frequency to 1MHz
  pot1(0x00);                         //initializing the potentiometer wiper to have zero resistance in room 1
  pot2(0xFF);                         //initializing the potentiometer wiper to have maximum resistance in room 2
  while(1) {
    if (pir1 == 1 && count1 == 0) {   //checking if the presence in room 1 is true and also if the detection is first time
      int i=0x00;                     //resistance value to be set in potentiometer 1
      int j=0xFF;                     //resistance value to be set in potentiometer 2
      while(i<=0xFF && j>=0x00) {     //increasing and decreasing values in potentiometer
        pot1(i);                      //call the function for potentiometer 1
        pot2(j);                      //call the function for potentiometer 2
        wait(0.01);                   //delay of 0.01s
        i++;                          //increment i by 1
        j--;                          //decrement j by 1
      }
      count1 = 1;                     //set the detection count in room 1
      count2 = 0;                     //reset the detection count in room 2
    }
    if (pir2 == 1 && count2 == 0) {
      int i=0xFF;                     //resistance value to be set in potentiometer 1
      int j=0x00;                     //resistance value to be set in potentiometer 2
      while(i>=0x00 && j<=0xFF) {     //decreasing and increasing values in potentiometer
        pot1(i);                      //call the function for potentiometer 1
        pot2(j);                      //call the function for potentiometer 2
        wait(0.01);                   //delay of 0.01s
        i--;                          //decrement j by 1
        j++;                          //increment i by 1
      }
      count1 = 0;                     //reset the detection count in room 1
      count2 = 1;                     //set the detection count in room 2
    }
  }
}
