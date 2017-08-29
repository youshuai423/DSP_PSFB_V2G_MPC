/******************************************************************************
| includes
|-------------------------------------------------------------------------------------------*/
#include "ysPWM.h"

/******************************************************************************
| variables
|--------------------------------------------------------------------------------------------*/
extern Uint16 PhaSft = DABperiod * 0.08;  // 相移时钟数 > 0.08（4us, 28.8度）？

/******************************************************************************
| functions
|-------------------------------------------------------------------------------------------*/
void InitPWM()
{
	/* ======== DAB ======== */
	// ----------------EPwm1---------------------
	EPwm1Regs.TBPHS.half.TBPHS = 0;  // 时基周期寄存器
	EPwm1Regs.TBCTR = 0;  // 时基计数寄存器置零
	EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm1Regs.TBCTL.bit.CLKDIV = prediv;  // 时钟预分频
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
	EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	EPwm1Regs.CMPA.half.CMPA = 0; // duty_cycle = 0.5
	EPwm1Regs.CMPB = DABperiod * 0.5;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // TBCTR = 0时装载
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm1Regs.AQCTLA.bit.CBU = AQ_CLEAR;

	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;  // A不翻转，B翻转
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm1Regs.DBRED = DeadZone; // Deadzone
	EPwm1Regs.DBFED = DeadZone;

	EPwm1Regs.ETSEL.bit.INTEN = 1;  // 使能EPwm1中断
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;  // TBCTR = 0触发中断
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;  // 每次中断都响应

	// ----------------EPwm2---------------------
	EPwm2Regs.TBPHS.half.TBPHS = 0;  // 时基周期寄存器
	EPwm2Regs.TBCTR = 0;  // 时基计数寄存器置零
	EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm2Regs.TBCTL.bit.CLKDIV = prediv;  // 时钟预分频
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	EPwm2Regs.CMPA.half.CMPA = PhaSft; // duty_cycle = 0.5
	EPwm2Regs.CMPB = DABperiod * 0.5 + PhaSft;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // TBCTR = 0时装载
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;  // 和另一桥臂相反
	EPwm2Regs.AQCTLA.bit.CBU = AQ_SET;

	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;  // A不翻转，B翻转
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm2Regs.DBRED = DeadZone; // Deadzone
	EPwm2Regs.DBFED = DeadZone;

	/* ======== 4th Leg ======== */
	// ----------------EPwm3---------------------
	EPwm3Regs.TBPHS.half.TBPHS = DABperiod - 0.6 * PhaSft;  // 时基周期寄存器
	EPwm3Regs.TBCTR = 0;  // 时基计数寄存器置零
	EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm3Regs.TBCTL.bit.CLKDIV = prediv;  // 时钟预分频
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	EPwm3Regs.CMPA.half.CMPA = DABperiod * 0.7; // duty_cycle = 0.5
	EPwm3Regs.CMPB = DABperiod * 0.5;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // TBCTR = 0时装载
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;

	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;  // A不翻转，B翻转
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm3Regs.DBRED = DeadZone; // Deadzone
	EPwm3Regs.DBFED = DeadZone;

	/* ======== 1-3 Leg ======== */
	// ----------------EPwm4---------------------
	EPwm4Regs.TBPHS.half.TBPHS = DABperiod - 0.6 * PhaSft;  // 时基周期寄存器
	EPwm4Regs.TBCTR = 0;  // 时基计数寄存器置零
	EPwm4Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm4Regs.TBCTL.bit.CLKDIV = prediv;  // 时钟预分频
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	EPwm4Regs.CMPA.half.CMPA = DABperiod * 0.7; // 周期为7kHz， duty_cycle = 0.5
	EPwm4Regs.CMPB = DABperiod * 0.5;
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // TBCTR = 0时装载
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;


	EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;  // A不翻转，B翻转
	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm4Regs.DBRED = DeadZone; // Deadzone
	EPwm4Regs.DBFED = DeadZone;

	// ----------------EPwm5---------------------
	EPwm5Regs.TBPHS.half.TBPHS = DABperiod - 0.6 * PhaSft;  // 时基周期寄存器
	EPwm5Regs.TBCTR = 0;  // 时基计数寄存器置零
	EPwm5Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm5Regs.TBCTL.bit.CLKDIV = prediv;  // 时钟预分频
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	EPwm5Regs.CMPA.half.CMPA = DABperiod * 0.7; // duty_cycle = 0.5
	EPwm5Regs.CMPB = DABperiod * 0.5;
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // TBCTR = 0时装载
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;  // TBCTR = 0时装载

	EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;

	EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;  // A不翻转，B翻转
	EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm5Regs.DBRED = DeadZone; // Deadzone
	EPwm5Regs.DBFED = DeadZone;

	// ----------------EPwm6---------------------
	EPwm6Regs.TBPHS.half.TBPHS = DABperiod - 0.6 * PhaSft;  // 时基周期寄存器
	EPwm6Regs.TBCTR = 0;  // 时基计数寄存器置零
	EPwm6Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm6Regs.TBCTL.bit.CLKDIV = prediv;  // 时钟预分频
	EPwm6Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;

	EPwm6Regs.CMPA.half.CMPA = DABperiod * 0.7; // duty_cycle = 0.5
	EPwm6Regs.CMPB = DABperiod * 0.5;
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // TBCTR = 0时装载
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;  // TBCTR = 0时装载

	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;

	//EPwm6Regs.DBCTL.bit.IN_MODE = DBB_RED_DBA_FED;
	EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;  // A不翻转，B翻转
	EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm6Regs.DBRED = DeadZone; // Deadzone
	EPwm6Regs.DBFED = DeadZone;

	// ----------------开始计时---------------------
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;  // 向上计数
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;

	EPwm1Regs.TBPRD = DABperiod;  // 周期设置
	EPwm2Regs.TBPRD = DABperiod;
	EPwm3Regs.TBPRD = DABperiod;
	EPwm4Regs.TBPRD = DABperiod;
	EPwm5Regs.TBPRD = DABperiod;
	EPwm6Regs.TBPRD = DABperiod;
}
