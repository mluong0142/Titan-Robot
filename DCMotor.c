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
  PWMPER4 = _22VKhz;
  PWMPER5 = _22VKhz;
  
  //Duty cycle
  PWMDTY4 =_22Khz;
  PWMDTY5 =_22VKhz;
  
   
}

void enableChannel(unsigned char channel) 
{
   SET_BITS(PWME,channel);
}

void disableChannel(unsigned char channel) 
{
  CLR_BITS(PWME,channel);
}



//Note: Motor doesnt turn until speed value of 55 
void setMotor(unsigned char speed, unsigned char direction, unsigned char motor) 
{

 //Calculate speed in terms of pwm duty cycle
 unsigned char pwm = (unsigned char)((231U*(speed)+2369U+50)/100U); //+50 to round up the answer
 switch(motor)
  {
    case MOT1:
    MOT1_BUS(direction);
    PWMDTY4 = pwm;
    break;
  
    case MOT2:
    MOT2_BUS(direction);
    PWMDTY5 = pwm;
    break;
 }
}


void setMoterAlternate(unsigned directionM1,unsigned directionM2) 
{
  MOT1_BUS(directionM1);
  MOT2_BUS(directionM2);
}
  


void setSpeed(unsigned char speed,unsigned char motor) 
{
  unsigned char pwm = (unsigned char)((231U*(speed)+2369U+50)/100U); //+50 to round up the answer
 
  switch(motor)
  {
    case MOT1:
    PWMDTY4 = pwm;
    break;
  
    case MOT2:
    PWMDTY5 = pwm;
    break;
  } 
}

/***************Old functions**********************
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
  
}*/

  
  
  


        
    
    






  





