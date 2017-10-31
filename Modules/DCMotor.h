#include "utils.h"
 

//Channel alignment left
#define CH0_LEFT_ALIGN     CLR_BITS(PWMCAE,PWMCAE_CAE0_MASK)
#define CH1_LEFT_ALIGN     CLR_BITS(PWMCAE,PWMCAE_CAE1_MASK)
#define CH2_LEFT_ALIGN     CLR_BITS(PWMCAE,PWMCAE_CAE2_MASK)
#define CH3_LEFT_ALIGN     CLR_BITS(PWMCAE,PWMCAE_CAE3_MASK)
#define CH4_LEFT_ALIGN     CLR_BITS(PWMCAE,PWMCAE_CAE4_MASK)
#define CH5_LEFT_ALIGN     CLR_BITS(PWMCAE,PWMCAE_CAE5_MASK)

//Channel alignment centre
#define CH0_CENTRE_ALIGN   SET_BITS(PWMCAE,PWMCAE_CAE0_MASK)
#define CH1_CENTRE_ALIGN   SET_BITS(PWMCAE,PWMCAE_CAE1_MASK)
#define CH2_CENTRE_ALIGN   SET_BITS(PWMCAE,PWMCAE_CAE2_MASK)
#define CH3_CENTRE_ALIGN   SET_BITS(PWMCAE,PWMCAE_CAE3_MASK)
#define CH4_CENTRE_ALIGN   SET_BITS(PWMCAE,PWMCAE_CAE4_MASK)
#define CH5_CENTRE_ALIGN   SET_BITS(PWMCAE,PWMCAE_CAE5_MASK)

//Channel high polarity
#define CH0_HIGH_POL      SET_BITS(PWMPOL,PWMPOL_PPOL0_MASK)
#define CH1_HIGH_POL      SET_BITS(PWMPOL,PWMPOL_PPOL1_MASK)
#define CH2_HIGH_POL      SET_BITS(PWMPOL,PWMPOL_PPOL2_MASK)
#define CH3_HIGH_POL      SET_BITS(PWMPOL,PWMPOL_PPOL3_MASK)
#define CH4_HIGH_POL      SET_BITS(PWMPOL,PWMPOL_PPOL4_MASK)
#define CH5_HIGH_POL      SET_BITS(PWMPOL,PWMPOL_PPOL5_MASK)

//Channel low polarity
#define CH0_LOW_POL       CLR_BITS(PWMPOL,PWMPOL_PPOL0_MASK)
#define CH1_LOW_POL       CLR_BITS(PWMPOL,PWMPOL_PPOL1_MASK)
#define CH2_LOW_POL       CLR_BITS(PWMPOL,PWMPOL_PPOL2_MASK)
#define CH3_LOW_POL       CLR_BITS(PWMPOL,PWMPOL_PPOL3_MASK)
#define CH4_LOW_POL       CLR_BITS(PWMPOL,PWMPOL_PPOL4_MASK)
#define CH5_LOW_POL       CLR_BITS(PWMPOL,PWMPOL_PPOL5_MASK)

//DC motor Channel config ignore SA
#define CH4_COUNT_CLK_DIRECTLY  CLR_BITS(PWMCLK,PWMCLK_PCLK4_MASK)
#define CH5_COUNT_CLK_DIRECTLY  CLR_BITS(PWMCLK,PWMCLK_PCLK5_MASK)


//Channels Enable Masks
#define CH0 PWME_PWME0_MASK
#define CH1 PWME_PWME1_MASK
#define CH2 PWME_PWME2_MASK
#define CH3 PWME_PWME3_MASK
#define CH4 PWME_PWME4_MASK
#define CH5 PWME_PWME5_MASK

 //Clock scale,counter,8bit mode
#define MODE_8BIT 0U
#define RESET     0U
#define NO_PSCALE 0U

//Period and frequency
#define _22Khz  182U
#define _70P    127U

//Channel Duty Cycle
#define CH0_DUTY PWMDTY0
#define CH1_DUTY PWMDTY1
#define CH2_DUTY PWMDTY2
#define CH3_DUTY PWMDTY3
#define CH4_DUTY PWMDTY4
#define CH5_DUTY PWMDTY5

//Speed
#define _60P 110U
#define _80P 146U
#define _40P 73U

//DC Motor mask and bus
#define MOT1_MASK 0x06
#define MOT2_MASK 0x09
#define MOTOR_DDR DDRB
#define MOTOR_BUS_MASK 0x0F
#define INIT_MOT_DDR SET_BITS(DDRB,MOTOR_BUS_MASK)

#define MOT1_BUS(data) FORCE_BITS(PORTB,MOT1_MASK,data)
#define MOT2_BUS(data) FORCE_BITS(PORTB,MOT2_MASK,data)


//Directions Motor 1

#define FWD1   0x04
#define BKD1   0x02
#define STOPH1 0x06
#define STOPL1 0x00



#define FWD2   0x08
#define BKD2   0x01
#define STOPH2 0x09
#define STOPL2 0x00


//Directions Motor 2


/*
#define FWD2   0x04
#define BKD2   0x08
#define STOPH2 0x0C
#define STOPL2 0x00*/


//Motor State
#define SPEED 0U
#define DIREC 1U

//Motor speed flag 
#define CH4S  0U
#define CH5S  1U


//Motor modifier flag
#define MOT1  0U
#define MOT2  1U

void initDCMotor(void);
void disableChannel(unsigned char channel);
void enableChannel(unsigned char channel);

void setMotor(unsigned char modifier, unsigned char specifier,volatile unsigned char attribute); 
//int setMotor(int num,...);


   














