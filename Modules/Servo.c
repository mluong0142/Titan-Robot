#include <stdio.h>
#include <stdlib.h>
#include "Servo.h"
#include "Timer.h"

unsigned int currentPosition;
unsigned char mode;
unsigned long msDelay;
unsigned char degree;


unsigned char PrevState = LOWSTATE;
void servoInit(void) 
{
  currentPosition = 600U;
  TSCR1=TSCR1_INIT;// enable TCNT, fast timer flag clear, freeze duting debbugging
  SET_TCNT_PRESCALE(TCNT_PRESCALE_8);// set prescale to 8
  MAKE_CHNL_OC(2);//Config channel 0
  SET_OC_ACTION(2,OC_GO_HI);
  TIMER_CHNL(2) = TCNT + (_20MS - currentPosition);
  ENABLE_CHNL_INTERRUPT(2);//enable TC0 channel interrupts
  mode = IDLE;
}                                




interrupt VectorNumber_Vtimch2 void TimerCh1Handler(void) 
{
  
  
  switch(mode) 
  {
    case DELAY:
    sweepServo();
    break;
    case FIXED:
    fixedServo();
    break;
    case IDLE:
    break;
  }
  
  switch(PrevState) 
  {
    case HIGHSTATE:
    TIMER_CHNL(2) += _20MS - currentPosition;//Duration of the low state
    SET_OC_ACTION(2,OC_GO_HI);
    PrevState = LOWSTATE;
    break;
    
    
    case LOWSTATE:
    TIMER_CHNL(2) += currentPosition;//Duration of the high state
    SET_OC_ACTION( 2, OC_GO_LOW);
    PrevState = HIGHSTATE;
    break;
  }
}

static unsigned int calculatePulse(void)
{
  static unsigned int result;
  result =(unsigned int) ((93086L*(degree)+5750000L)/10000U);
  return result;
}



static int sweepServo(void) 
{
  static unsigned char calcFlag = FALSE;
  static unsigned char direction;
  static unsigned long scaler;//ratio
  static unsigned int newPosition; 
  static unsigned int distance;//This removes statment
  static unsigned char state;

  if (calcFlag == FALSE)
  {
      
    newPosition = calculatePulse();
    if( newPosition > currentPosition) 
    {
      direction = RIGHT;
    } 
    else if (newPosition < currentPosition) 
    {
     direction = LEFT;
    } 
    else 
    {
      return ERROR; 
    }
       
    scaler = (10000L*20L)/msDelay;
    distance = abs(newPosition - currentPosition);
    distance = (unsigned int)(((unsigned long)(scaler*(distance)))/10000U);
    calcFlag = TRUE;
    state = PrevState;
  }
  
  
  if (PrevState == state)//This makes sure the calculation happens once a full cylce has completed 
  {
    
  
    if (direction == RIGHT) 
    {
      if((currentPosition + distance) <= newPosition)//Need to travel more 
      {                                                                                                                                                       
       currentPosition+= distance;
      } 
      else if (currentPosition == newPosition)//We are at our desired point Hooray!! 
      {
        mode = IDLE;
        calcFlag = FALSE;
      }
      
      else if( (currentPosition + distance) > newPosition)////The offset will cause overshoot our desired position, so take the differance  
      {
        currentPosition += abs(currentPosition-newPosition);
      } 
    
      
    } 
    else if (direction == LEFT) 
    {
      if((currentPosition - distance)>= newPosition)//Need to travel more 
      {
        currentPosition-= distance;
      } 
      else if(currentPosition == newPosition)//We are at our desired point Hooray!! 
      {
        mode = IDLE;
        calcFlag = FALSE;
      }
      
      else if((currentPosition - distance)<newPosition)//The offset will cause overshoot our desired position, so take the differance  
      {
        currentPosition -= abs(currentPosition-newPosition);
      } 
   
    }
  }
}

static void fixedServo(void) 
{
  currentPosition = calculatePulse();
  mode = IDLE;
}

void setModeServoV(unsigned char tMode, unsigned char tDegree, unsigned long tDelay) 
{
 
 if(tMode == FIXED) 
 {
  mode = tMode;
  degree =tDegree;
 } 
 else 
 {
   mode = tMode;
   degree =tDegree;
   msDelay = tDelay;
  
  }
}
  
//Not working as intended need to investigate
//va_args takes its arguments from the back for longs datatypes??

void setModeServo(unsigned long arg,...) 
{
  va_list modeList;
  va_start (modeList,arg);
  
  if (arg == 2) 
  {
    degree = (unsigned char)va_arg(modeList,unsigned long);
    mode = (unsigned char)va_arg(modeList,unsigned long);
  } 
  else if (arg == 3) 
  {
    msDelay = va_arg(modeList,unsigned long);
    degree = (unsigned char)va_arg(modeList,unsigned long);
    mode = (unsigned char)va_arg(modeList,unsigned long);
    
    
  }
  va_end(modeList);//Dead comment?????
}

/*void setModeServo(unsigned int arg,...) 
{
  va_list modeList;
  va_start (modeList,arg);
  
  if (arg == 2) 
  {
    mode = (unsigned char)va_arg(modeList,unsigned int);
    degree = (unsigned char)va_arg(modeList,unsigned int);
  } 
  else if (arg == 3) 
  {
    mode = (unsigned char)va_arg(modeList,unsigned int);
    degree = (unsigned char)va_arg(modeList,unsigned int);
    msDelay = va_arg(modeList,unsigned int);
  }
  va_end(modeList);//Dead comment?????
}*/
    
    
  









































  



 
  
  