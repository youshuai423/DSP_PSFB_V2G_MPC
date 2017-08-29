/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "ysSPI.h"

void InitSPI()
{
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;  //数据在上升沿输出，下降沿输入
	SpiaRegs.SPICCR.bit.SPILBK = 0;  // 禁止自测试
	SpiaRegs.SPICCR.bit.SPICHAR = 15;  // 16位数据

	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0;  // 禁止接收溢出中断
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0;  // 正常SPI时钟
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;  // MASTER模式
	SpiaRegs.SPICTL.bit.TALK = 1;  // 使能发送
	SpiaRegs.SPICTL.bit.SPIINTENA = 0;  // 禁止中断

	SpiaRegs.SPIBRR = 127;  // 波特率 = LSPCLK/128 = 293K

	SpiaRegs.SPIFFTX.bit.SPIRST = 1;  // 重新开始FIFO发送接收
	SpiaRegs.SPIFFTX.bit.SPIFFENA = 1;  // FIFO增强使能
	SpiaRegs.SPIFFTX.bit.TXFIFO = 1;  // 重新使能发送FIFO操作
	SpiaRegs.SPIFFTX.bit.TXFFIENA = 0;  // 禁止匹配中断
	SpiaRegs.SPIFFTX.bit.TXFFIL = 16;  // 16级缓冲

	SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;  // 重新使能发送FIFO
	SpiaRegs.SPIFFRX.bit.RXFFIENA = 0;  // 禁止匹配中断
	SpiaRegs.SPIFFRX.bit.RXFFIL = 16;  // 16级缓冲

	SpiaRegs.SPIFFCT.bit.TXDLY = 0;  // 0发送延迟

	SpiaRegs.SPIPRI.bit.SOFT = 1;  // 发送完数据停止
	SpiaRegs.SPIPRI.bit.FREE = 0;

	SpiaRegs.SPICCR.bit.SPISWRESET = 1; // 取消软件复位状态
}

// 发送单个数据
void spiSend(Uint16 a)
{
    SpiaRegs.SPITXBUF=a;
}
