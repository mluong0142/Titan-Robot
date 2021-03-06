#include "SCI.h"
#include <mc9s12c32.h>
#include <string.h>


volatile char rxBuffer[rxBufSize];
volatile unsigned char rxIndex = 0;
unsigned char msgCount = 0;
static unsigned StartFlag = 0;

char stringS []="1111111111";

/*************InitSCI()*******************************************************
Purpose: Initalize the SCI module
Input:   int baudRate - a divisor to get the desired baud rate
         int SCIData  - configures word length, parity
         int config    - configures interrupts and enables Receiver and Trasmitter
******************************************************************************/
void InitSCI(unsigned int baudRate,unsigned char SCIData,unsigned char config) 
{
  SCIBD = baudRate;// buad clock 9600,Parity disable, 
  SCICR1 = SCIData;// N81 data
  SCICR2 |= config;// turn on transmitter and receiver
 
}
/************putcSCI()*********************************************************
Purpose: Put a character to the Serial Port
Input:   char cx - character to be printed
******************************************************************************/
void putcSCI(char cx) 
{
  //Wait until transmit data register empty
  while(!(SCISR1&SCISR1_TDRE_MASK));
  SCIDRL = cx;
}
/************putsSCI()*********************************************************
Purpose: Put a string to the Serial Port
nput:   char *str - pointer to the printed string
******************************************************************************/
void putsSCI(char *str) 
{
  while(*str)
    putcSCI(*str++);
}

/************getcSCI()*********************************************************
Purpose: gets a character from the Serial Port
nput:   char cx - character read from the port
******************************************************************************/
/*
void getcSCI(char cx) 
{
  rxBuffer[rxIndex] = cx;
  rxIndex++; 
  rxIndex %= rxBufSize;// Ring buffer that trashes old data  
}*/
  
/************SCIHandler()*****************************************************
Purpose: Grab a character from the serial port on every interupt
******************************************************************************/


interrupt VectorNumber_Vsci void SCIHandler( void )
{
  // Wait until data is available on port
  if(SCISR1 & SCISR1_RDRF_MASK)
  {
    getcSCI(SCIDRL);
    // Clear indicator stating that there is data on the port
    CLR_BITS(SCISR1, SCISR1_RDRF_MASK);
  }
}

/************getcSCI()*********************************************************
Purpose: gets a character from the Serial Port
nput:   char cx - character read from the port
******************************************************************************/
void getcSCI(char cx) 
{
  if(cx == '>') 
  {
    msgCount++;
    StartFlag=STOP;
  } 
  else if (cx == '<') 
  {
    StartFlag = START;
    
  } 
  else if (StartFlag == START) 
  {
    rxBuffer[rxIndex]= cx;
    rxIndex++;
    rxIndex %= rxBufSize;
  }
}


/************get_cmdbuf()*********************************************************
Purpose:parses out the commands
input:   char argv1,argv2:These store the individual commands
******************************************************************************/
void get_cmdbuf(char argv1[],char argv2[],char *arg3)
{
  DisableInterrupts;
  (void)strncpy(&argv1[0],&rxBuffer[0],3);
  (void)strncpy(&argv2[0],&rxBuffer[3],3);
   *(arg3) =*(stringS+5);
  EnableInterrupts;
}
 
