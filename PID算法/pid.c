#include "pid.h"
#include "usart.h"
/* ˽�����Ͷ��� --------------------------------------------------------------*/
//����PID�ṹ��

/* ˽�к궨�� ----------------------------------------------------------------*/
/*************************************/
//����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
/*************************************/
#define  P_DATA      30                                //P����
#define  I_DATA      1                                //I����
#define  D_DATA     0.5                              //D����

 PID sPID;
 PID *sptr = &sPID;
 PID sPID1;
 PID *sptr1 = &sPID1;


/**************PID������ʼ��********************************/
void IncPIDInit(double Proportion,double Integral,double Derivative) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=Proportion;      //�������� Proportional Const
    sptr->Integral=Integral;        //���ֳ���  Integral Const
    sptr->Derivative=Derivative;      //΢�ֳ��� Derivative Const
    //sptr->SetPoint=SetPoint;           //�趨Ŀ��Desired Value
	
}
/********************����ʽPID�������************************************/
int IncPIDCalc(int iError) 
{	
  int iIncpid;                                 //��ǰ���
	
  iIncpid=(int)((sptr->Proportion * iError)                 //E[k]��
              -(sptr->Integral * sptr->LastError)     //E[k-1]��
              +(sptr->Derivative * sptr->PrevError));  //E[k-2]��
              
  sptr->PrevError=sptr->LastError;                    //�洢�������´μ���
  sptr->LastError=iError;
  return (int)(iIncpid);                                    //��������ֵ
}
/********************λ��ʽ PID �������************************************/
int LocPIDCalc(int iError)
{
	send(0xF8,1,iError);
  int dError;
  sptr->SumError += iError; //����
  dError = iError - sptr->LastError; //΢��
  sptr->LastError = iError;
  return(sptr->Proportion * iError //������
  + sptr->Integral * sptr->SumError //������
  + sptr->Derivative * dError); //΢����
}



/**************PID������ʼ��********************************/
void IncPIDInit1(double Proportion,double Integral,double Derivative) 
{
    sptr1->LastError=0;            //Error[-1]
    sptr1->PrevError=0;            //Error[-2]
    sptr1->Proportion=Proportion;      //�������� Proportional Const
    sptr1->Integral=Integral;        //���ֳ���  Integral Const
    sptr1->Derivative=Derivative;      //΢�ֳ��� Derivative Const
   // sptr1->SetPoint=100;           //�趨Ŀ��Desired Value
	
}
/********************����ʽPID�������************************************/
int IncPIDCalc1(int iError) 
{
  int iIncpid;                                 //��ǰ���
  iIncpid=(sptr1->Proportion * iError)                 //E[k]��
              -(sptr1->Integral * sptr1->LastError)     //E[k-1]��
              +(sptr1->Derivative * sptr1->PrevError);  //E[k-2]��
              
  sptr1->PrevError=sptr1->LastError;                    //�洢�������´μ���
  sptr1->LastError=iError;
  return(iIncpid);                                    //��������ֵ
}
/********************λ��ʽ PID �������************************************/
int LocPIDCalc1(int iError)
{
  int dError;
	send (0xF9,1,iError);
  sptr1->SumError += iError; //����
  dError = iError - sptr1->LastError; //΢��
  sptr1->LastError = iError;
  return(sptr1->Proportion * iError //������
  + sptr1->Integral * sptr1->SumError //������
  + sptr1->Derivative * dError); //΢����
}

