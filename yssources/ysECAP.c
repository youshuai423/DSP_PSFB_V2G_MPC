/******************************************************************************
| includes
|-------------------------------------------------------------------------------------------*/
#include "ysECAP.h"

/******************************************************************************
| variables
|--------------------------------------------------------------------------------------------*/

/******************************************************************************
| functions
|-------------------------------------------------------------------------------------------*/
void InitECAP()
{
	// ECAP module 1 config
	ECap1Regs.ECCTL2.bit.CAP_APWM = 1;
	ECap1Regs.CAP1 = DABperiod; // Set period value
	ECap1Regs.CAP2 = 0.5 * (DABperiod); // Set Duty cycle
	ECap1Regs.CTRPHS = 0; //
	ECap1Regs.ECCTL2.bit.APWMPOL = 0;
	ECap1Regs.ECCTL2.bit.SYNCI_EN = 1; // Enable sync in
	ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0; // EPWM sync in sync out

	// ECAP module 2 config
	ECap2Regs.ECCTL2.bit.CAP_APWM = 1;
	ECap2Regs.CAP1 = DABperiod; // Set period value
	ECap2Regs.CAP2 = 0.5 * DABperiod; // Set Duty cycle
	//ECap2Regs.CAP2 = 0; // Set Duty cycle
	ECap2Regs.CTRPHS = DABperiod - 0.5*PhaSft; //
	ECap2Regs.ECCTL2.bit.APWMPOL = 0;
	ECap2Regs.ECCTL2.bit.SYNCI_EN = 1; // Enable sync in
	ECap2Regs.ECCTL2.bit.SYNCO_SEL = 0; // Enable sync out

	// ECAP module 3 config
	ECap3Regs.ECCTL2.bit.CAP_APWM = 1;
	ECap3Regs.CAP1 = 0.5 * DABperiod; // Set period value
	ECap3Regs.CAP2 = 0.5 * DABperiod - PhaSft - 200; // Set Duty cycle
	ECap3Regs.CTRPHS = 0.5 * DABperiod - PhaSft - 200; //
	ECap3Regs.ECCTL2.bit.APWMPOL = 0;
	ECap3Regs.ECCTL2.bit.SYNCI_EN = 1; // Enable sync in
	ECap3Regs.ECCTL2.bit.SYNCO_SEL = 2; // Disable sync out

	// Allow TSCTR to run
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;
	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;
	ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;
}
