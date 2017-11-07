#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "ADC.h"
#include "DCMotor.h"
#include "LCD.h"
#include "SCI.h"
#include "Servo.h"
#include "Stepper.h"
#include "TimerModule.h"

char message[]="Hello";
char lx;

char argv1[3];
char argv2[3];
char el = 'A';

extern unsigned char msgCount;



unsigned char motorSpeed = 60;
void main(void) {
  /* put your own code here */
  
  
  
 initDCMotor();
 InitSCI(52U,0,SCICR2_RE_MASK | SCICR2_TE_MASK|SCICR2_RIE_MASK);
 setMotor(60,BKD1,MOT1);
 enableChannel(CH4|CH5);
 EnableInterrupts;


  for(;;) {
  
  if(msgCount>0) 
  {
   
   //asm("nop");
   //asm("nop");
   get_cmdbuf(argv1,argv2,&el);
   //asm("nop");
   //asm("nop");
  
  
  }
    
  
   //setSpeed(motorSpeed,MOT1);
  } /* loop forever */
  /* please make sure that you never leave main */
}



  