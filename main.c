// main.c
// A simple blinky program for ATtiny85
// Connect red LED at pin 2 (PB3)

#include <avr/io.h>
#include <util/delay.h>
 
 
int main (void)
{
  // set PB3 to be output
  //DDRB = 0b00001000;
  //
  DDRB=(1<<DDB3)|(1<<DDB4);
  while (1) {

    PORTB = (1<<PB4)|(1<<PB3);
    _delay_ms(20);
    PORTB = 0b00000000;
    _delay_ms(200);
    //PORTB = (1>>PB4)|(1>>PB3);
  }

  return 1;
}
