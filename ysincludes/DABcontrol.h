/******************************************************************************
| includes
|----------------------------------------------------------------------------*/
#include "math.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "ysPWM.h"

/******************************************************************************
| defines
|----------------------------------------------------------------------------*/
/* Motor parameters */
#define Rs 5  //4.4717
#define Rr 3.1407
#define Lm 0.42735
#define Lls 0.0173
#define Ls 0.44465
#define Llr 0.0173
#define Lr 0.44465
#define Tr 0.1415767
#define np 2

/* control period */
#define DAB_Ts 5e-5  // 20kHz
#define Fleg_Ts 2e-4  // 5kHz
//#define DAB_Ts 0.3333e-4  // 21kHz
//#define Fleg_Ts 1e-4  // 10kHz

/* PI parameters */
  // Ulcmd
//#define Kp_Ig 0.1
#define Ag 1.2542e-3
#define Bg 1.99355
#define Cg -0.99749
#define Uplim_Ig 1
#define Downlim_Ig -1

/* auxiliary */
#define pi 3.1415926
//#define IgRefRatio 0.2

/******************************************************************************
| types
|----------------------------------------------------------------------------*/
typedef struct
{
  double a, b, c;
} PHASE_ABC;

typedef struct
{
  double al, be;
} PHASE_ALBE;

typedef struct
{
  double d,q;
} PHASE_DQ;

/******************************************************************************
| global variables
|----------------------------------------------------------------------------*/
/* 观测值 */
  // 电压
extern double Ui;
extern double Ug;
  // 电流
extern double Ii;
extern double Ig;
extern double Ia;
extern double Ib;
extern double Ic;

/* 给定值 */
  // 电压
extern double Ug_cmd;
extern double Ua_cmd;
extern double Ub_cmd;
extern double Uc_cmd;
  // 电流
extern double IgRefRatio;
extern double IabcRefRatio;
extern double Ig_cmd;
extern double Ia_cmd;
extern double Ib_cmd;
extern double Ic_cmd;

/* PI 变量 */
extern double Kp_Ig, Kr_Ig;

extern double Ig_en, Ig_en1, Ig_en2;
extern double Ig_Rn, Ig_Rn1, Ig_Rn2;

extern double Ia_en, Ia_en1, Ia_en2;
extern double Ia_Rn, Ia_Rn1, Ia_Rn2;

extern double Ib_en, Ib_en1, Ib_en2;
extern double Ib_Rn, Ib_Rn1, Ib_Rn2;

extern double Ic_en, Ic_en1, Ic_en2;
extern double Ic_Rn, Ic_Rn1, Ic_Rn2;

/******************************************************************************
| local functions prototypes
|----------------------------------------------------------------------------*/

/******************************************************************************
| exported functions
|----------------------------------------------------------------------------*/
/* PI module */  
extern double PImodule(double Kp, double Ki, double err, double *intgrt, double Uplim, double Downlim, double Ts);
extern double PRmodule(double A, double B, double C, double Kr, double Kp, double en, double *en1, double *en2, \
		               double *Rn1, double *Rn2, double Uplim, double Downlim, double Ts);
extern double Integrator(double paramin, double sum, double ts);
extern double LPfilter(double x, double lasty, double wc, double ts);
extern double Dfilter(double *x);
