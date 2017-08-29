/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "ysCAN.h"

void InitCANB()
{
	EALLOW;

	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up for GPIO16 (CANTXB)
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up for GPIO17 (CANRXB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch qual for GPIO17 (CANRXB)
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 2;  // Configure GPIO16 for CANTXB operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 2;  // Configure GPIO17 for CANRXB operation

	EDIS;

	/* Create a shadow register structure for the CAN control registers. This is
	 needed, since only 32-bit access is allowed to these registers. 16-bit access
	 to these registers could potentially corrupt the register contents or return
	 false data. This is especially true while writing to/reading from a bit
	 (or group of bits) among bits 16 - 31 */

	struct ECAN_REGS ECanbShadow;

    EALLOW;		// EALLOW enables access to protected bits

    /* Configure eCAN RX and TX pins for CAN operation using eCAN regs*/
	ECanbShadow.CANTIOC.all = ECanbRegs.CANTIOC.all;  // CANTX pin is used for the CAN transmit functions
	ECanbShadow.CANTIOC.bit.TXFUNC = 1;
	ECanbRegs.CANTIOC.all = ECanbShadow.CANTIOC.all;

	ECanbShadow.CANRIOC.all = ECanbRegs.CANRIOC.all;  // CANRX pin is used for the CAN receive functions
	ECanbShadow.CANRIOC.bit.RXFUNC = 1;
	ECanbRegs.CANRIOC.all = ECanbShadow.CANRIOC.all;

	/* Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31) */
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;  // Select eCAN mode rather than SCC mode
	ECanbShadow.CANMC.bit.SCB = 1;
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

	/* Initialize all bits of 'Master Control Field' to zero */
	// Some bits of MSGCTRL register come up in an unknown state. For proper operation,
	// all bits (including reserved bits) of MSGCTRL must be initialized to zero
    ECanbMboxes.MBOX0.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX1.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX2.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX3.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX4.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX5.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX6.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX7.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX8.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX9.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX10.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX11.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX12.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX13.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX14.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX15.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX16.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX17.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX18.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX19.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX20.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX21.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX22.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX23.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX24.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX25.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX26.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX27.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX28.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX29.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX30.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX31.MSGCTRL.all = 0x00000000;

	// TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
	//	as a matter of precaution.
	ECanbRegs.CANTA.all	= 0xFFFFFFFF;	/* Clear all TAn bits */

	ECanbRegs.CANRMP.all = 0xFFFFFFFF;	/* Clear all RMPn bits */

	ECanbRegs.CANGIF0.all = 0xFFFFFFFF;	/* Clear all interrupt flag bits */
	ECanbRegs.CANGIF1.all = 0xFFFFFFFF;

	/* Configure bit timing parameters for eCANB*/
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1, request write access to CANBTC
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

    ECanbShadow.CANES.all = ECanbRegs.CANES.all;

    do
	{
	    ECanbShadow.CANES.all = ECanbRegs.CANES.all;
	} while(ECanbShadow.CANES.bit.CCE != 1 ); 		// Wait for CCE bit to be  cleared..


    ECanbShadow.CANBTC.all = 0;

	/* The following block for all 150 MHz SYSCLKOUT (75 MHz CAN clock) - default. Bit rate = 1 Mbps
	   See Note at end of file */
	ECanbShadow.CANBTC.bit.BRPREG = 4;
	ECanbShadow.CANBTC.bit.TSEG2REG = 2;
	ECanbShadow.CANBTC.bit.TSEG1REG = 10;

    ECanbShadow.CANBTC.bit.SAM = 1;  // samples three times and make a majority decision
    ECanbRegs.CANBTC.all = ECanbShadow.CANBTC.all;

    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.CCR = 0 ;            // Set CCR = 0
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

    ECanbShadow.CANES.all = ECanbRegs.CANES.all;

    do
    {
        ECanbShadow.CANES.all = ECanbRegs.CANES.all;
    } while(ECanbShadow.CANES.bit.CCE != 0 ); 		// Wait for CCE bit to be  cleared..


    /* Disable all Mailboxes  */
 	ECanbRegs.CANME.all = 0;		// Required before writing the MSGIDs

    EDIS;

	/* Write to the MSGID field  */
	ECanbMboxes.MBOX0.MSGID.all = 0x15555555; // TX, Standard Identifier; IDE = 0, AME = 0, AAM = 0, ID = 0x15555555
	ECanbMboxes.MBOX1.MSGID.all = 0x05555555; // RX, Standard Identifier; IDE = 0, AME = 0, AAM = 0, ID = 0x05555555

	/* Configure Mailbox Direction */
	ECanbShadow.CANMD.all = ECanbRegs.CANMD.all;  // Mailbox25 is configured as a transmit mailbox
	ECanbShadow.CANMD.bit.MD0 = 0;  // TX
	ECanbShadow.CANMD.bit.MD1 = 1;  // RX
	ECanbRegs.CANMD.all = ECanbShadow.CANMD.all;

	/* Enable Mailbox */
	ECanbShadow.CANME.all = ECanbRegs.CANME.all;  // Mailbox25 is enabled for the CAN module
	ECanbShadow.CANME.bit.ME0 = 1;
	ECanbShadow.CANME.bit.ME1 = 1;
	ECanbRegs.CANME.all = ECanbShadow.CANME.all;

	/* Write to DLC field in Master Control reg */
	ECanbMboxes.MBOX0.MSGCTRL.bit.DLC = 8;

	/* Write to the mailbox RAM field */
	ECanbMboxes.MBOX0.MDL.all = 0x55555555;
	ECanbMboxes.MBOX0.MDH.all = 0x55555555;
}

// This function reads out the contents of the indicated
// by the Mailbox number (MBXnbr).
void mailbox_read(int16 MBXnbr, Uint32* MDL32, Uint32* MDH32, Uint32* MBID)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
   *MDL32 = Mailbox->MDL.all; // = 0x9555AAAn (n is the MBX number)
   *MDH32 = Mailbox->MDH.all; // = 0x89ABCDEF (a constant)
   *MBID = Mailbox->MSGID.all;// = 0x9555AAAn (n is the MBX number)
}
