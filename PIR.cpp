#include "mbed.h"
DigitalIn pir(D7);
DigitalOut myled(LED1);

int main() {
  while(1) {
    if (pir == 1) {
      myled = 0;
    }
    else if (pir == 0) {
      myled = 1;
    }
  }
}
