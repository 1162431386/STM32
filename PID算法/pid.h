#ifndef _PID_H
#define _PID_H
#include "sys.h"
typedef struct 
{

  __IO double      SetPoint;                                 //�趨Ŀ�� Desired Value
  __IO double     SumError;                                 //����ۼ�
  __IO double   Proportion;                               //�������� Proportional Const
  __IO double   Integral;                                 //���ֳ��� Integral Const
  __IO double   Derivative;                               //΢�ֳ��� Derivative Const
  __IO double      LastError;                                //Error[-1]
  __IO double      PrevError;                                //Error[-2]
}PID;

void IncPIDInit(double Proportion,double Integral,double Derivative)  ;
int IncPIDCalc(int iError);
int LocPIDCalc(int iError);

void IncPIDInit1(double Proportion,double Integral,double Derivative)  ;
int IncPIDCalc1(int iError);
int LocPIDCalc1(int iError);
#endif
