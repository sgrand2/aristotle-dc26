// main.c
// Aristotles Head Defcon26 using ATtiny85
// LED @ PIN2 (PB3) and PIN3 (PB4)
// Push Button Pin6/PB1

//1Mhz clock speed
//#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
static inline void initInterrupt(void);
void State0();
void State1();
void State2();
void State3();
void State4();
void State5();
void State6();
void State7();

//Global Var for ISR/Interrupt
volatile uint8_t StateToggle = 0;

//Global Debounce
uint8_t previousReading= 1;
uint8_t buttonPressed = 1;

int main (void)
{
  //             Port Number
  //             5 4 3 2 1 0
  //PORTB = 0b00|0|0|0|0|0|0;

  //Set Pin 3 and Pin 4 as OutPuts
  //DDRB=0b00011000;
  DDRB=(1<<DDB3)|(1<<DDB4);
  //Enable pullup on PB1
  PORTB |= (1 << PB1);

  //Initialize Interrupts for Pin6/PB1
  initInterrupt();
  
  while (1)
  {
    //Switch Between Different Routines
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
      case 2:
        State2();
        break;
      case 3:
        State3();
        break;
      case 4:
        State4();
        break;
      case 5:
        State5();
        break;
      case 6:
        State6();
        break;
      case 7:
        State7();
        break;
      default:
        State7();
    }



  }

  return 1;
}
static inline void initInterrupt(void)
{
  GIMSK |= (1 << PCIE); //Interrupt Enable on PIN Change
  PCMSK |= (1 << PCINT1); //Enable Interrupt for PCINT1/Pin6/PB1
  sei();

}

ISR(PCINT0_vect)
{
  if ((PINB & (1 << PB1)) != previousReading)
  {
    if(!buttonPressed)
    {
    //StateToggle
    int x = 0;
    while(x < 5)
    {
      PORTB = (1<<PB4)|(1<<PB3);
      _delay_ms(10);
      PORTB = 0b00000000;
      _delay_ms(10);
      x++;
    }
    if(StateToggle < 8)
      StateToggle++;
    else
      StateToggle = 0;

    //EndToggle
      PORTB = StateToggle | (1 << PB1);
      buttonPressed = 1;
    }
    else
      buttonPressed = 0;
  }
  previousReading = (PINB & (1 << PB1));
}

//All On
//
void State0()
{
       PORTB = (1<<PB4)|(1<<PB3);
}

//Blink Slow
//
void State1()
{
       PORTB = (1<<PB4)|(1<<PB3);
       _delay_ms(20);
       PORTB = 0b00000000;
       _delay_ms(200);
}

//Blink Fast
//
void State2()
{
       PORTB = (1<<PB4)|(1<<PB3);
       _delay_ms(20);
       PORTB = 0b00000000;
       _delay_ms(50);
}

//
//
void State3()
{
       PORTB = (1<<PB4)|(1<<PB3);
}

//
//
void State4()
{
       PORTB = (1<<PB4)|(1<<PB3);
}

//Alternate Blink
//
void State5()
{
    PORTB = 0b00010000;
    _delay_ms(20);
    PORTB = 0b00001000;
    _delay_ms(20);
}

//Wink
//
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
//
void State7()
{
       PORTB = 0b00000000;
}
