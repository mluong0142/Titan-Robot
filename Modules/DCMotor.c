#include "DCMotor.h"
#include <mc9s12c32.h>
#include <stdarg.h>


void initDCMotor() 
{
  
  INIT_MOT_DDR;
    
  PWMCTL = MODE_8BIT;
  PWMPRCLK = NO_PSCALE;
  
  CH5_HIGH_POL;
  CH4_HIGH_POL;
  CH4_CENTRE_ALIGN;
  CH5_CENTRE_ALIGN;
  
  //Skip SA 
  CH5_COUNT_CLK_DIRECTLY;
  CH4_COUNT_CLK_DIRECTLY;
  
  //Period
  PWMPER4 = _22Khz;
  PWMPER5 = _22Khz;
  
  //Duty cycle
  PWMDTY4 =_70P;
  PWMDTY5 =_70P;
  
   
}

void enableChannel(unsigned char channel) 
{
   SET_BITS(PWME,channel);
}

void disableChannel(unsigned char channel) 
{
  CLR_BITS(PWME,channel);
}



void setMotor(unsigned char modifier, unsigned char specifier,volatile unsigned char attribute) 
{

  if (modifier == SPEED) 
  {
      switch(specifier) 
      {
        case CH4S:
        PWMDTY4 = attribute;
        break;
        case CH5S:
        PWMDTY5 = attribute;
        break;
      }
  } 
  else if (modifier == DIREC) 
  {
      switch(specifier) 
      {
        case MOT1:
        MOT1_BUS(attribute);
        break;
        case MOT2:
        MOT2_BUS(attribute);
        break;
      }
  }
  
}
        
    
    






  





/*
int setMotor(int num,...) 
{
 unsigned char modifier;//Speed or Direction
 unsigned char specifier;//DutyChannel or Motor Direction
 
 va_list motorState;
 va_start (motorState,num);
 
 modifier = (unsigned char)va_arg(motorState,int);
 
 //Changing the speed of one motor
 if (num == 3 && modifier == SPEED ) 
 {
    specifier = (unsigned char)va_arg(motorState,int);
    
    switch(specifier)//Choose which channel to modify 
    {
      case CH4S:
      PWMDTY4 = (unsigned char)va_arg(motorState,int);
      break;
      case CH5S:
      PWMDTY5 = (unsigned char)va_arg(motorState,int);
      break;
    }
 } 
 
 //Changing the direction of one motor
 else if (num == 3 && modifier == DIREC) 
 {
   specifier = (unsigned char)va_arg(motorState,int);
   
   switch(specifier) 
   {
    case MOT1:
    MOT1_BUS((unsigned char)va_arg(motorState,int));
    break;
    case MOT2:
    MOT2_BUS((unsigned char)va_arg(motorState,int));
    break;
   }
 }
 //Changing the Direction two motors
 else if (num ==5 && modifier == DIREC) 
 {
    specifier = (unsigned char)va_arg(motorState,int);
    switch(specifier) 
    {
      case MOT1:
      MOT1_BUS((unsigned char)va_arg(motorState,int));
      break;
      case MOT2:
      MOT2_BUS((unsigned char)va_arg(motorState,int));
      break;
    }
    
    specifier = (unsigned char)va_arg(motorState,int);
    switch(specifier) 
    {
      case MOT1:
      MOT1_BUS((unsigned char)va_arg(motorState,int));
      break;
      case MOT2:
      MOT2_BUS((unsigned char)va_arg(motorState,int));
      break;
    }
 } 
 else 
 {
    va_end(motorState);
    return ERROR;
 }
 return 1;
}*/
  
