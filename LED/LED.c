#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input

#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define sweep_delay() _delay_ms(50) // delay
#define line_delay() _delay_ms(700) // char delay


#define one (1 << PB3)
#define two (1 << PB4)
#define three (1 << PB2)



void right() {
    output(DDRB, one);
    output(DDRB, three);
    clear(PORTB, two);

    set(PORTB, one);
    clear(PORTB, three);
    sweep_delay();

    set(PORTB, three);
    clear(PORTB, one);
    sweep_delay();

    input(DDRB, one);
    input(DDRB, three);    
    output(DDRB, one);
    output(DDRB, two);
    clear(PORTB, three);


    set(PORTB, two);
    clear(PORTB, one);
    sweep_delay();

    set(PORTB, one);
    clear(PORTB, two);
    sweep_delay();


    input(DDRB, one);
    input(DDRB, two);
    output(DDRB, two);
    output(DDRB, three);
    clear(PORTB, one);

    set(PORTB, two);
    clear(PORTB, three);
    sweep_delay();

    set(PORTB, three);
    clear(PORTB, two);
    sweep_delay();

    input(DDRB, two);
    input(DDRB, three);

}


void left() {
    output(DDRB, two);
    output(DDRB, three);
    clear(PORTB, one);

    set(PORTB, three);
    clear(PORTB, two);
    sweep_delay();

    set(PORTB, two);
    clear(PORTB, three);
    sweep_delay();

    

    input(DDRB, two);
    input(DDRB, three);


    output(DDRB, one);
    output(DDRB, two);
    clear(PORTB, three);


    

    set(PORTB, one);
    clear(PORTB, two);
    sweep_delay();

    set(PORTB, two);
    clear(PORTB, one);
    sweep_delay();

    input(DDRB, one);
    input(DDRB, two);


    output(DDRB, one);
    output(DDRB, three);
    clear(PORTB, two);


    set(PORTB, three);
    clear(PORTB, one);
    sweep_delay();

    set(PORTB, one);
    clear(PORTB, three);
    sweep_delay();

    input(DDRB, one);
    input(DDRB, three); 

}





int main(void) {

   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize output pins
   //
    input(DDRB, one);
    input(DDRB, two);
    input(DDRB, three);
   //
   // main loop
   //
   while(1) {
       left();
       line_delay();

   }
}