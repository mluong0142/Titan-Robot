#include <stdio.h>
#include <stdlib.h>


#include "Stepper.h"

unsigned char stepPattern [] = { 0x80,0xA0,0x20,0x60,0x40,0x50,0x10,0x90};

unsigned char stepType;
unsigned char mode;
int MaxStep= 0;
int numStep = 0;
int position;
unsigned char index = 0;





volatile unsigned char switchStatus;
volatile unsigned char direction;



void initRTI(void) 
{
 
  direction = RIGHT;
  
  DDRA_SWR_INIT;
  SET_SWR_INPUT_EN;//Extra intialization because of PORTA
  DDRT_STEPPER_INIT;
  COPCTL |= COPCTL_RSBCK_MASK;  // freeze RTI during BDM active
  CRGFLG = CRGFLG_RTIF_MASK;    // clear any possibly pending RTI interrupts
}


int setMode(int num,...)
{
   va_list modeList;
   va_start (modeList,num);
   
   if (num == 1)
   {
       mode = (unsigned char)va_arg(modeList,int);
       
   } 
   else if (num == 2) 
   {
      mode =(unsigned char) va_arg(modeList,int);
      position = va_arg(modeList,int);
      
   }
   else if (num == 3) 
   {
      mode = (unsigned char) va_arg(modeList,int);
      stepType = (unsigned char)va_arg(modeList,int);
      position = va_arg(modeList,int);
      
   }
    
   else 
   {
     va_end(modeList);
     return ERROR;
   }
   
   va_end(modeList);
   CRGINT |= CRGINT_RTIE_MASK; 
   return 1;
 } 

void seekSwitch(void) 
{
    
    if (direction == LEFT )
    {
      switchStatus =  CHECK_LEFT_SWITCH_ON;
      MaxStep++;
      //Case for the left limit is triggered
      if (switchStatus ==  L_SWR_ON_MASK) 
      { 
        direction= RIGHT;
        mode = HOME;
        //CLR_BITS(CRGINT,CRGINT_RTIE_MASK);//Disable Interrupt
      } 
      else if (switchStatus != L_SWR_ON_MASK) 
      {
        index--;
        index&=STEPPER_MOD_7;
        
      }
         
    } 
    else if (direction == RIGHT) 
    {
       switchStatus =  CHECK_RIGHT_SWITCH_ON;
       
       //Case for the right limit is triggered
       if(switchStatus == R_SWR_ON_MASK) 
       {
          direction = LEFT;
          index--;
          index&=STEPPER_MOD_7;
          MaxStep++;
          
       } 
       else if (switchStatus != R_SWR_ON_MASK) 
       {
          index++;
          index&=STEPPER_MOD_7; 
       }
        
     }
    
    STEPPER_BUS(stepPattern[index]);
}


void home(void) 
{
   
   if(numStep == MaxStep/2) 
   {
     CLR_BITS(CRGINT,CRGINT_RTIE_MASK);//Disable Interrupt
     mode = READY;
   }
   else
   {
      numStep++;
      index++;
      index&=STEPPER_MOD_7;
      STEPPER_BUS(stepPattern[index]);
   }
   
}

int calculatePosition(int angle) 
{
  static int calcPosition;
  calcPosition = (int)( ( (21444L)*(angle) + 10000L )/10000L);
  return calcPosition;
}

void continuous (int userPosition) 
{
   static unsigned char calcFlag = FALSE;
   
   if (calcFlag != TRUE) 
   {
      MaxStep = numStep - (calculatePosition (userPosition));
      calcFlag = TRUE;
      if ( MaxStep > 0)  
      {
        direction = RIGHT;
        MaxStep = MaxStep/stepType;
      } 
      else if (MaxStep < 0) 
      {
         direction = LEFT;
         MaxStep = abs(MaxStep)/stepType;
      }
   }
   
   
   if (direction == RIGHT && 0!= MaxStep) 
   {
    
     index+=stepType;
     MaxStep--;
     numStep-=stepType;
     index &=STEPPER_MOD_7; 
   } 
   else if (direction == LEFT && 0!= MaxStep) 
   {
      index -=stepType;
      MaxStep--;
      numStep+=stepType;
      index&=STEPPER_MOD_7; 
   }
   else 
   {
    calcFlag = FALSE;// Ready for the next calculations 
    CLR_BITS(CRGINT,CRGINT_RTIE_MASK);//Disable Interrupt
   }
   STEPPER_BUS(stepPattern[index]);
}
 
void relative(int userPosition) 
{ 
   static unsigned char calcFlag = FALSE;
   
   if (calcFlag != TRUE) 
   {
      MaxStep =  (calculatePosition (userPosition));
      calcFlag = TRUE;
      if ( MaxStep > 0)  
      {
        direction = LEFT;
        MaxStep = MaxStep/stepType;
      } 
      else if (MaxStep < 0) 
      {
         direction = RIGHT;
         MaxStep = abs(MaxStep)/stepType;
      }
   }
   
   if (direction == RIGHT && 0!= MaxStep) 
   {
     
     index+=stepType;
     MaxStep--;
     numStep-=stepType;
     index &=STEPPER_MOD_7; 
      
   } 
   else if (direction == LEFT && 0!= MaxStep) 
   {
      
      index -=stepType;
      MaxStep--;
      numStep+=stepType;
      index&=STEPPER_MOD_7;  
   }
   else 
   {
    calcFlag = FALSE;// Ready for the next calculations 
    CLR_BITS(CRGINT,CRGINT_RTIE_MASK);//Disable Interrupt
   }
   STEPPER_BUS(stepPattern[index]);
}
 
 
void initStepper(void) 
{
  while(mode == SEEK || mode == HOME);
}


  
interrupt 7 void RTIhandler( void )
{
   
   CRGFLG = CRGFLG_RTIF_MASK;
   switch(mode) 
   {
    case SEEK:
    seekSwitch();
    break;
    case HOME:
    home();
    break;
    case FIXED:
    continuous(position);
    break;
    case RELAT:
    relative(position);
    break;
   }
}

unsigned int Status(void)
{
  return mode;
}

void speed(unsigned char speed) 
{
  RTICTL = speed;// set RTI period
}
  
  

  


  
  


