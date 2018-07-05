// main.c
// A simple blinky program for ATtiny85
// Connect red LED at pin 2 (PB3)

#include <avr/io.h>
#include <util/delay.h>
 
 
void State0();
void State1();
void State7();
int main (void)
{

  //Push-Button States
  //0 - Fully On
  //1 - Blink Slow (200ms)
  //2 - Blink Fast (20ms)
  //3 - PWM (Slow Blink)
  //4 - PWM (Quick Blink)
  //5 - Alternate Eyes
  //6 - Wink (Eye On/Eye Off)
  //7 - LEDS OFF
  //
  //             Port Number
  //             5 4 3 2 1 0
  //PORTB = 0b00|0|0|0|0|0|0;

  int StateToggle = 0;
  int Toggle = PINB1;

  //Set Pin 3 and Pin 4 as OutPuts
  DDRB=(1<<DDB3)|(1<<DDB4);

  while (1)
  {
    //Switch Between Different Routines

    if(((!(Toggle)) && StateToggle < 8))
    { 
      StateToggle++;
    }else
    {
      StateToggle = 0;
    }

    switch(StateToggle)
    {
      case 0:
        State0();
        break;
      case 1:
        State1();
        break;
      default:
        State7();
    }



  }

  return 1;
}

void State0()
{
       PORTB = (1<<PB4)|(1<<PB3);
       _delay_ms(20);
       PORTB = 0b00000000;
       _delay_ms(200);
    //PORTB = (1>>PB4)|(1>>PB3);
}

void State1()
{
       PORTB = (1<<PB4)|(1<<PB3);
}

void State7()
{
       PORTB = 0b00000000;
}
