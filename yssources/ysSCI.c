/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "ysSCI.h"

void InitSCIB()
{
	ScibRegs.SCICCR.bit.STOPBITS = 1; // 1位停止位
	ScibRegs.SCICCR.bit.PARITY = 0; // 奇校验
	ScibRegs.SCICCR.bit.PARITYENA = 0; // 禁止奇偶校验
	ScibRegs.SCICCR.bit.LOOPBKENA = 0; // 屏蔽自测模式
	ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0; // 空闲线模式
	ScibRegs.SCICCR.bit.SCICHAR = 7; // 八位数据

	ScibRegs.SCICTL1.bit.RXERRINTENA = 0; // 屏蔽接受错误中断
	ScibRegs.SCICTL1.bit.TXWAKE = 0; // 不唤醒
	ScibRegs.SCICTL1.bit.SLEEP = 0; // 非睡眠状态
	ScibRegs.SCICTL1.bit.TXENA = 1; // 发送使能
	ScibRegs.SCICTL1.bit.RXENA = 1; // 接受使能

	//ScibRegs.SCIHBAUD = 0x0000;  // 115200 baud @LSPCLK = 37.5MHz.
	//ScibRegs.SCILBAUD = 0x0028;
	//ScibRegs.SCIHBAUD = 0x0000;  // 38400 baud @LSPCLK = 37.5MHz.
	//ScibRegs.SCILBAUD = 0x0079;
	//ScibRegs.SCIHBAUD = 0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
	//ScibRegs.SCILBAUD = 0x00E7;
	ScibRegs.SCIHBAUD = 0x0007;  // 2400 baud @LSPCLK = 37.5MHz.
	ScibRegs.SCILBAUD = 0x00A0;

	ScibRegs.SCICTL2.bit.RXBKINTENA = 0; // 禁止RXRDY\BRKDT中断
	ScibRegs.SCICTL2.bit.TXINTENA = 0; // 禁止TXRDY中断

	ScibRegs.SCIFFTX.bit.SCIFFENA = 1; // SCI FIFO打开
	ScibRegs.SCIFFTX.bit.SCIRST = 1; // SCI FIFO能继续发送接收
	ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1; // 重新使能发送FIFO
	ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1; // 清除TXFFINT标志位
	ScibRegs.SCIFFTX.bit.TXFFIENA = 0; // 禁止TX FIFO中断
	ScibRegs.SCIFFTX.bit.TXFFIL = 2; // 发送FIFO深度设为2

	ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1; // 清除RXFFOVF标志位
	ScibRegs.SCIFFRX.bit.RXFIFORESET = 1; // 重新使能接收FIFO
	ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1; // 清除RXFFINT标志位
	ScibRegs.SCIFFRX.bit.RXFFIENA = 0; // 禁止RX FIFO中断（采用查询方式）
	ScibRegs.SCIFFRX.bit.RXFFIL = 2; // 接收FIFO深度设为2

	ScibRegs.SCIFFCT.bit.ABD = 0; // 非自动检测
	ScibRegs.SCIFFCT.bit.CDC = 0; // 禁止波特率自动检测的校准
	ScibRegs.SCIFFCT.bit.FFTXDLY = 0; // FIFO发送延迟为0；

	ScibRegs.SCICTL1.bit.SWRESET = 1; // 取消软件复位状态
}

/* =================发送数据================== */
// 发送单个数据
int scib_tx(int a)
{
//    while (ScibRegs.SCIFFTX.bit.TXFFST == 16) {return 0;}
//    ScibRegs.SCITXBUF=a;
//    return 1;
	if(ScibRegs.SCICTL2.bit.TXRDY)
	{
		ScibRegs.SCITXBUF=a;
		return 1;
	}
	else
		return 0;
}

// 发送一组数据
void scib_str_tx(char * msg)
{
    int i = 0;
    int flag = 1;
    while(msg[i] != '\0')
    {
        flag = scib_tx(msg[i]);
        i++;
		if (flag == 0) break;
    }
}

void scib_num_tx(int msg[])
{
	int i = 0;
	int flag = 1;

	for (i = 0; i < SCINumSend; i++)
	{
		flag = scib_tx(msg[i]);
		if (flag == 0) break;
	}
}

/* =================接收数据================== */
int scib_rx(int *a)
{
//	if(ScibRegs.SCIRXST.bit.RXRDY)
//	{
//		*a = ScibRegs.SCIRXBUF.bit.RXDT;
//		return 1;
//	}
//	else
//		return 0;
	*a = ScibRegs.SCIRXBUF.bit.RXDT;
	return 1;
}
void scib_str_rx(char *msg)
{

}
void scib_num_rx(int msg[])
{

}
