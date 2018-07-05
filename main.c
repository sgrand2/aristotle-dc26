// main.c
// Aristotles Head Defcon26 using ATtiny85
// LED @ PIN2 (PB3) and PIN3 (PB4)

#include <avr/io.h>
#include <util/delay.h>
 
void State0();
void State1();
void State6();
void State7();

int main (void)
{
  //             Port Number
  //             5 4 3 2 1 0
  //PORTB = 0b00|0|0|0|0|0|0;

  //Set Pin 3 and Pin 4 as OutPuts
  //DDRB=(1<<DDB3)|(1<<DDB4);
  //DDRB=0b00011000;
  //
  
  int StateToggle = 0;
  int Toggle = PINB1;


  while (1)
  {
    PORTB |= (1 << PB1);
    DDRB=0b00011000;
    Toggle = PINB1;
    //Switch Between Different Routines

    if(Toggle == 0)
    { 
      if(StateToggle < 8)
        StateToggle++;
      else
        StateToggle = 0;
    }

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


//Turn off and on
void State0()
{
       PORTB = (1<<PB4)|(1<<PB3);
       _delay_ms(20);
       PORTB = 0b00000000;
       _delay_ms(200);
}

//All On
void State1()
{
       PORTB = (1<<PB4)|(1<<PB3);
}

//Wink
void State6()
{
  int wink = 0;
  while(wink < 10)
  {
    PORTB = 0b00010000;
    _delay_ms(20);
    PORTB = 0b00011000;
    _delay_ms(90);
    wink++;
  }
  PORTB = 0b00000000;
  _delay_ms(200);
}

//All Off
void State7()
{
       PORTB = 0b00000000;
}
