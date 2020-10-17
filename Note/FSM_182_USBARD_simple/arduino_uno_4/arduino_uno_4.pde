#include<avr/io.h>
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define BufSize 127
#define C 0
#define B 1

int getnum(char *x);
int SerialRead(char *state);

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  DDRC=B11000000;
  PORTC=B00111111;
  DDRB=B00111111;
  PORTB=B00000000;
  
}
//begin

void loop()
{
  
  uint8_t Entry[2];
  uint8_t Hist[2];
  char State[BufSize];
  uint8_t flag;
  
  Serial.flush();
  Serial.println(EOF,DEC);
  //INIC
  for( Hist[C]=0,Hist[B]=0; TRUE; Hist[C] = Entry[C], Hist[B] = Entry[B]){  
    //ENTRADA Pinos
    Entry[C]=PINC;
    //ENTRADA Serial
    if(Serial.available()){
      SerialRead(State);
      Entry[B] = getnum(State);
    }
      
    if((Entry[C] == Hist[C]) && (Entry[B] == Hist[B]))
      continue;
    //if(Entry[C] != Hist[C])  
      Serial.println(Entry[C],DEC);
    PORTB = Entry[B];
  }
}
//have to press reset in learning mode always.
/***FUNCTIONS***/
int getnum(char* x)
{
  int num;
  if(sscanf(x,"%d",&num)){
    if (num == NULL)
      num = 0;
    return num;
    
  }else{
    return 0;
    
  }
  
}
/********/
int SerialRead(char *State)
{
  uint8_t i=0;
  char IncomingByte;
  delay(25);//wait for incoming data.
  for(i = 0; IncomingByte = Serial.read(); i++){
    if((IncomingByte == '\r') || (IncomingByte == '\n')){
      State[i] = '\0';
      Serial.flush();
      break;
    }else{
      State[i]=IncomingByte;
    }
  }
  return 0;
}
//char *X, X is a variable that stores a fisical
//address with a cast type char.
//getnum works with string terminating with only NULL or '\0'
//my style
//Lesson always be flexible and except and obey the good practices,
// without any desobidience, and for extra culture if desired try to 
// clarify the why things are as they are. Never be stuborn.
//must flush buffer in the PC side.

