//
// hello.mag.45.c
//
// Hall effect magnetic sensing hello-world
//    9600 baud FTDI interface
//
// Neil Gershenfeld 11/3/13
// (c) Massachusetts Institute of Technology 2013
//
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all 
// liability.
//

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 100 // bit delay for 9600 with overhead
#define low_delay() _delay_us(bit_delay_time) // RS232 bit delay



#define bit0 (1 << PD3)
#define bit1 (1 << PD4)
#define bit2 (1 << PD5)
#define bit3 (1 << PD6)
#define bit4 (1 << PD7)
#define bit5 (1 << PB0)
#define bit6 (1 << PB1)
#define bit7 (1 << PB2)
#define bit8 (1 << PB3)
#define bit9 (1 << PB4)
#define clk (1 << PB5)


void write_byte(uint16_t adData) {
    //
    clear(PORTB, clk);
    low_delay();
    if ((512 & adData) != 0)     set(PORTB, bit9);
    if ((256 & adData) != 0)     set(PORTB, bit8);
    if ((128 & adData) != 0)     set(PORTB, bit7);
    if ((64 & adData) != 0)      set(PORTB, bit6);
    if ((32 & adData) != 0)      set(PORTB, bit5);
    if ((16 & adData) != 0)      set(PORTD, bit4);
    if ((8 & adData) != 0)       set(PORTD, bit3);
    if ((4 & adData) != 0)       set(PORTD, bit2);
    if ((2 & adData) != 0)       set(PORTD, bit1);
    if ((1 & adData) != 0)       set(PORTD, bit0);
    set(PORTB, clk);
}

int main(void) {
   //
   // main
   int i = 0;
   //
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize output pins
   //
   output(PORTB, 0xF8); // set upper 5 bits of port B to output
   output(PORTD, 0x3F); // set lower 6 bits of port D to output
   //
   // init A/D
   //
   ADMUX = (0 << REFS1) | (0 << REFS0) // Vcc ref
      | (0 << ADLAR) // right adjust
      | (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0); // ADC4
   ADCSRA = (1 << ADEN) // enable
      | (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // prescaler /16
   //
   // main loop
   //
   while (1) {
       for(i = 0; i < 4; i++) {
           ADCSRA |= (0 << ADEN); //disable ADC
           ADMUX &= (0xF0 | i);  //set input channel
           ADCSRA |= (1 << ADEN); //enable ADC
           ADCSRA |= (1 << ADSC);
           //
           // wait for completion
           while (ADCSRA & (1 << ADSC))
           ;
           //
           write_byte(ADC);
       }   
   }
}