/*This program is used to test the PIR sensor function with the mbed board*/

#include "mbed.h"
DigitalIn pir(D7);          //data is collected at pin D7 of the mbed board from PIR sensor
DigitalOut myled(LED1);     //an indicator whether there is a motion or not

int main() {
  while(1) {
    if (pir == 1) {         //checks whether the motion of a person is true
      myled = 0;            //led glows if the condition is true
    }
    else if (pir == 0) {    //checks whether the motion of a person is false
      myled = 1;            //led goes off if the condition is true
    }
  }
}
