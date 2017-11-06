#include "ADC.h"

unsigned int atdValue1;
unsigned int atdValue2;

/********************initADC()***********************************************
Purpose:initialize ADC Registers (no interrupts,1 channel,one conversion)
Input: None
*****************************************************************************/ 
void initADC(void) 
{
  //ATDCTL2 Config
  SET_BITS(ATDCTL2,ADC_POWER|ADC_FAST_CLR|HALT_WAI);// Turn on ADC,stop conversation on wait mode and Fast clear flag
  asm("nop"); 
 
  //ATDCTL3 Config
  ADC_NUM_CONV(0x01);//One conversion
  ADC_CONV_SETTINGS(0x02);//finish current conversion and halt
  FIFO_OFF;
   
  //ATCTL4 Config
  SET_PRESCALER(0x01);// prescaler of 2 (20Mhz-5Mhz)
  SAMPLE_SEL(0x02);// 4 A/D conversation clock period and 10bit mode
}

/********************initADCV2()************************************************
Purpose:initialize ADC Registers (uses interrupts,2 channel,continous conversion)
Input: unsigned char - channel 0-7U
********************************************************************************/ 
void initADCV2(unsigned char inputChannel) 
{
  
  //ATDCTL2
  SET_BITS(ATDCTL2,ADC_POWER|HALT_WAI|ADC_INTERRUPT); // Turn on ADC,stop conversation on wait mode,No Fast clear flag and conversation completed interrupt on
  asm ("nop");
  
  //ATDCTL3 Config
 
  ADC_NUM_CONV(0x02);//Two conversion
  ADC_CONV_SETTINGS(0x02);//finish current conversion and halt
  FIFO_OFF;
  
  //ATCTL4 Config
  SET_PRESCALER(0x01);// prescaler of 2 (20Mhz-5Mhz)
  SAMPLE_SEL(0x02);// 4 A/D conversation clock period and 10bit mode
  
  //ATCTL5 Config
  ATDCTL5 = ATDCTL5INIT3;//Right justified data unsigned,continous converstion, multi channel
  SELECT_CHNL(inputChannel);

}

/********************readChannel()************************************************
Purpose:Set which Channel to begin reading (Use only for with intterupts configured)
Input:unsigned char - channel:0-7U
********************************************************************************/ 
int readChannel(unsigned char channel) 
{
   static unsigned int result; 
    
   ATDCTL5 = ATDCTL5INIT;//Result right justified,unsigned result,single conversion sequence, sample one channel.
   SELECT_CHNL(channel);//Read channel 4
    
   DisableInterrupts;
   while (!(ATDSTAT0 & SCF)); //Atomic Instruction
   EnableInterrupts;
   return (result = ATDDR0);
}

/********************ATDhandler()************************************************
Purpose:Read ATD value once ready to read
Input:None
********************************************************************************/ 
interrupt VectorNumber_Vatd0 void ATDhandler (void) 
{
   atdValue1 = ATDDR0;
   atdValue2 = ATDDR1;
   CLR_SCF;
}
  
  


  
  
  
  