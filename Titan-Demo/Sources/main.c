#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "ADC.h"
#include "DCMotor.h"
#include "LCD.h"
#include "SCI.h"
#include "Servo.h"
#include "Stepper.h"
#include "TimerModule.h"



unsigned char motorSpeed = 60;
void main(void) {
  /* put your own code here */
  
 initDCMotor();
 setMotor(60,BKD1,MOT1);
 enableChannel(CH4|CH5);
 EnableInterrupts;


  for(;;) {
   setSpeed(motorSpeed,MOT1);
  } /* loop forever */
  /* please make sure that you never leave main */
}
