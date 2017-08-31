/******************************************************************************
| includes                          
|----------------------------------------------------------------------------*/
#include "PSFB_Control.h"

/******************************************************************************
| local variable definitions                          
|----------------------------------------------------------------------------*/

/******************************************************************************
| global variable definitions                          
|----------------------------------------------------------------------------*/
/* 观测值 */
  // 电压
extern double Ui = 0;
extern double Ug = 0;
  // 电流
extern double Ii = 0;
extern double Ig = 0;
extern double Ia = 0;
extern double Ib = 0;
extern double Ic = 0;

/* 给定值 */
  // 电压
extern double Ug_cmd = 0;
extern double Ua_cmd = 0;
extern double Ub_cmd = 0;
extern double Uc_cmd = 0;

  // 电流
extern double IgRefRatio = 0.06;
extern double IabcRefRatio = 0.02;
extern double Ig_cmd = 0;
extern double Ia_cmd = 0;
extern double Ib_cmd = 0;
extern double Ic_cmd = 0;

/* PI 变量 */
extern double Kp_Ig = 0.2, Kr_Ig = 2;

extern double Ig_en = 0, Ig_en1 = 0, Ig_en2 = 0;
extern double Ig_Rn = 0, Ig_Rn1 = 0, Ig_Rn2 = 0;

extern double Ia_en = 0, Ia_en1 = 0, Ia_en2 = 0;
extern double Ia_Rn = 0, Ia_Rn1 = 0, Ia_Rn2 = 0;

extern double Ib_en = 0, Ib_en1 = 0, Ib_en2 = 0;
extern double Ib_Rn = 0, Ib_Rn1 = 0, Ib_Rn2 = 0;

extern double Ic_en = 0, Ic_en1 = 0, Ic_en2 = 0;
extern double Ic_Rn = 0, Ic_Rn1 = 0, Ic_Rn2 = 0;

/******************************************************************************
@brief   PI Module 
******************************************************************************/
double PImodule(double Kp, double Ki, double err, double *intgrt, double Uplim, double Downlim, double Ts)
{
	double output = 0;

	*intgrt += Ki * Ts * err;
	if (*intgrt >= Uplim)
	{
		*intgrt = Uplim;
		return Uplim;
	}
	else if (*intgrt <= Downlim)
	{
		*intgrt = Downlim;
		return Downlim;
	}
	else
	{
		output = Kp * err + *intgrt;

		if (output >= Downlim && output <= Uplim)
			return output;
		else if (output > Uplim)
			return Uplim;
		else
			return Downlim;
	}
}

double PRmodule(double A, double B, double C, double Kr, double Kp, double en, double *en1, double *en2, \
		        double *Rn1, double *Rn2, double Uplim, double Downlim, double Ts)
{
	double Rn = 0, output = 0;

	Rn = Kr * A * (en - *en2) + B * (*Rn1) + C * (*Rn2);
	if (Rn >= Uplim)
	{
		Rn = Uplim;
		*Rn2 = *Rn1; *Rn1 = Rn;
		*en2 = *en1; *en1 = en;
		return Uplim;
	}
	else if (Rn <= Downlim)
	{
		Rn = Downlim;
		*Rn2 = *Rn1; *Rn1 = Rn;
		*en2 = *en1; *en1 = en;
		return Downlim;
	}
	else
	{
		*Rn2 = *Rn1; *Rn1 = Rn;
		*en2 = *en1; *en1 = en;

		output = Kp * en + Rn;

		if (output >= Downlim && output <= Uplim)
			return output;
		else if (output > Uplim)
			return Uplim;
		else
			return Downlim;
	}
}

double Integrator(double paramin, double sum, double ts)
{
  return paramin * ts + sum;
}

double LPfilter(double x, double lasty, double wc, double ts)
{
  return (lasty + ts * wc * x) / (1 + ts * wc);
}

double Dfilter(double *x)
{
	double max = *x, min = *x;
	double sum = *x;
	int i = 0;

	for (i = 1; i < 5; i++)
	{
		if(*(x + i) > max)
		{
			max = *(x + i);
		}
		else if(*(x + i) < min)
		{
			min = *(x + i);
		}

		sum += *(x + i);
	}

	return (sum - max - min) * 0.333333;  // num = 5
}
