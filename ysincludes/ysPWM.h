/******************************************************************************
| includes
|--------------------------------------------------------------------------------------------*/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/******************************************************************************
| defines
|--------------------------------------------------------------------------------------------*/
#define DABperiod				7500  // 20KHz��Ӧʱ������TBCLK = SYSCLKOUT
#define Flegperiod				30000  // 5KHz��Ӧʱ������TBCLK = SYSCLKOUT
//#define DABperiod				5000  // 3.33KHz��Ӧʱ������TBCLK = SYSCLKOUT
//#define Flegperiod				15000  // 10KHz��Ӧʱ������TBCLK = SYSCLKOUT
#define prediv				0  // Ԥ��Ƶ
#define DeadZone			100   // ����1.5us

/******************************************************************************
| variables
|--------------------------------------------------------------------------------------------*/
extern Uint16 PhaSft;

/******************************************************************************
| local functions prototypes
|--------------------------------------------------------------------------------------------*/
void InitPWM(void);