/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "ysPWM.h"
#include "ysECAP.h"
#include "ysPORT.h"
#include "ysADC.h"
#include "ysDAC.h"
#include "ysSCI.h"
#include "ysSPI.h"
#include "PSFB_Control.h"

/******************************************************************************
| defines
|----------------------------------------------------------------------------*/
#define HallRatioVi  135.5  // 电压霍尔传感器变比1
#define HallRatioVg  135.0  // 电压霍尔传感器变比2
#define HallRatioIg   0.7407  // 电流霍尔传感器变比1
#define HallRatioIb   0.7407  // 电流霍尔传感器变比1
#define HallRatioIa   1.3333  // 电流霍尔传感器变比1
#define pi 3.1415926
#define wc 12000

/******************************************************************************
| variables
|----------------------------------------------------------------------------*/

/******************************************************************************
| local functions prototypes
|----------------------------------------------------------------------------*/
interrupt void epwm1_timer_isr(void);
interrupt void ISRTimer0(void);
