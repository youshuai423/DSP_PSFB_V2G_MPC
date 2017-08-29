/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/******************************************************************************
| defines
|----------------------------------------------------------------------------*/
//#pragma   DATA_SECTION(ramtest1,"ZONE7DATA1");
#define AD_ASTART		    ((Uint16 *)0x100000)						//片外AD的数据读取首地址
#define AD_BSTART		    ((Uint16 *)0x110000)					 	//片外AD的数据读取首地址
//#define Nospl  16
#define sRange  10.0  //量程为10V

/* 研旭 */
/*
#define AD7606_SCK_LOW					GpioDataRegs.GPACLEAR.bit.GPIO25=1
#define AD7606_SCK_HIGH					GpioDataRegs.GPASET.bit.GPIO25=1

#define AD7606_RST_LOW				    GpioDataRegs.GPACLEAR.bit.GPIO27=1
#define AD7606_RST_HIGH					GpioDataRegs.GPASET.bit.GPIO27=1

#define AD7606_CNVST_LOW				GpioDataRegs.GPACLEAR.bit.GPIO24=1
#define AD7606_CNVST_HIGH				GpioDataRegs.GPASET.bit.GPIO24=1

#define AD7606_SCS_LOW				    GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define AD7606_SCS_HIGH					GpioDataRegs.GPBSET.bit.GPIO61=1

#define AD7606_BUSY_READ                GpioDataRegs.GPADAT.bit.GPIO26
#define AD7606_DOUTA_READ               GpioDataRegs.GPBDAT.bit.GPIO60
#define AD7606_DOUTB_READ               GpioDataRegs.GPBDAT.bit.GPIO32
*/

/* Hellodsp */
#define AD7606_SCK_LOW					GpioDataRegs.GPACLEAR.bit.GPIO25=1
#define AD7606_SCK_HIGH					GpioDataRegs.GPASET.bit.GPIO25=1

#define AD7606_RST_LOW				    GpioDataRegs.GPBCLEAR.bit.GPIO60=1
#define AD7606_RST_HIGH					GpioDataRegs.GPBSET.bit.GPIO60=1

#define AD7606_CNVST_LOW				GpioDataRegs.GPACLEAR.bit.GPIO15=1
#define AD7606_CNVST_HIGH				GpioDataRegs.GPASET.bit.GPIO15=1

#define AD7606_BUSY_READ                GpioDataRegs.GPADAT.bit.GPIO14

#define AD7606_SCS_LOW				    GpioDataRegs.GPBCLEAR.bit.GPIO61=1
#define AD7606_SCS_HIGH					GpioDataRegs.GPBSET.bit.GPIO61=1
#define AD7606_DOUTA_READ               GpioDataRegs.GPBDAT.bit.GPIO60
#define AD7606_DOUTB_READ               GpioDataRegs.GPBDAT.bit.GPIO32

/******************************************************************************
| global variables
|----------------------------------------------------------------------------*/
//extern int conv_flg;  // 转换完成标志

/******************************************************************************
| local functions prototypes
|----------------------------------------------------------------------------*/

/******************************************************************************
| exported functions
|----------------------------------------------------------------------------*/
void InitADC(void);
void SerialRD(double * buf, Uint16 Nospl);
void ParallelRD(double * buf, Uint16 Nospl);
