#include "derivative.h"      
#include "TimerModule.h"
#include "utils.h"


/**************msDELAY()*******************************************************
Purpose: ms Delay
Input:   int k - number of milliseconds
**Currently Uses a prescaler of 8**
******************************************************************************/
void msDELAY(int k) 
{
  int ix;
  
  TC0 = TCNT + msDELAY_TICKS;  // Preset TC0 for first OC event
  
  MAKE_CHNL_OC( 0 );  // Set channel as OC
  for(ix = 0; ix < k; ix++)
  {
    while(!(TFLG1 & TFLG1_C0F_MASK));
      TC0 += msDELAY_TICKS;  
  }
  
  TIOS &= LOW(~TIOS_IOS0_MASK);  // Turn off OC
}