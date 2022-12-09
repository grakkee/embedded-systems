/*
 * Program to Echo Characters from the Keyboard to the Arduino Serial Terminal.
 * CPE 301 Lab 6 
 * Professor Lancaster
 * 
 * Conducted by Larson Rivera and Grace Meredith
 * October 8th 2021.
 * 
 * This program contains code and comments written by Professor D. Egbert.
 * Reutilization permission granted by Lab instructors.
 */
 
 #define RDA 0x80
 #define TBE 0x20  
 volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
 volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
 volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
 volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
 volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;

 #define PRESCALAR 1
unsigned char in_char = 'q';
unsigned int ticks = 0;

// Define Port B Register Pointers
volatile unsigned char* port_b = (unsigned char*) 0x25; 
volatile unsigned char* ddr_b  = (unsigned char*) 0x24; 
volatile unsigned char* pin_b  = (unsigned char*) 0x23; 

void setup()
{
 // initialize the serial port on USART0:
 U0init(9600);
 *ddr_b |= (1 << 6);
  PORTB &= (1 << 6);
}
void loop()
{
  unsigned char cs1;
  while (U0kbhit()==0){}; // wait for RDA = true
  cs1 = U0getchar();    // read character

  switch(cs1) {
    case 'a':
      ticks = HzToTicks(440);
      break;

    case 'b':
      ticks = HzToTicks(494);
      break;

    case 'c':
      ticks = HzToTicks(523);
      break;

    case 'd':
      ticks = HzToTicks(587);
      break;

    case 'e':
      ticks = HzToTicks(659);
      break;

    case 'f':
      ticks = HzToTicks(698);
      break;

    case 'g':
      ticks = HzToTicks(784);
      break;

    default:
      break;
  }

  if (in_char != 'q') {
    *port_b |= (1 << 6);
    delayHz(ticks);
    *port_b &= (0 << 6);
    delayHz(ticks);
  }
}

void delayHz(unsigned int ticks) {
  TCCR1B = 0xF8;
  TCNT1 = (unsigned int) 65536 - ticks;
  TCCR1B |= 0b00000001;
  while ((TIFR1 & 1) == 0);
  TCCR1B &= (1 << 7);
  TIFR1 |= 1;
}

unsigned int HzToTicks(unsigned int hz) {
  float HzPeriod = 1/ ((float) hz);
  HzPeriod = HzPeriod / 2.0;
  float clockPeriod = 1 / ((float)(16000000/PRESCALAR));

  return (unsigned int)(HzPeriod/clockPeriod);
}

void U0init(unsigned long U0baud)
{
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 // Same as (FCPU / (16 * U0baud)) - 1;
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}

unsigned char U0kbhit()
{
  if (*myUCSR0A & (1 << 7)) return 1;  // if bit 7 is set to a 1, the receive is complete and there is data to read
  else return 0;
}

unsigned char U0getchar()
{
  return *myUDR0; // Reads UDR0, which returns receive buffer contents
}

void U0putchar(unsigned char U0pdata)
{
  while (!(*myUCSR0A & (1 << 5)));  // wait for buffer to accept new data
  *myUDR0 = U0pdata;  // write data 
  while (!(*myUCSR0A & (1 << 6))); // wait for the data to be transmitted out.  
}
