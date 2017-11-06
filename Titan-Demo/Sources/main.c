#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "ADC.h"
#include "DCMotor.h"
#include "LCD.h"
#include "SCI.h"
#include "Servo.h"
#include "Stepper.h"
#include "TimerModule.h"




void main(void) {
  /* put your own code here */
  
 


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
