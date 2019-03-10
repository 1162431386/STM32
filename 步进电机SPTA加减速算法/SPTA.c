
#include "SPTA.h"
#include "led.h"
#include "usart.h"
#include <stdlib.h>
#include "test.h"
#include "pid.h"
#include "delay.h"
  extern int pid; 
  int VelAccumulator=0; 		
  int ActualAcceleration=0;	
  int VelAdd=0; 				
  int ActualVelocity=0;		
  int PosAccumulator=0;  //λ���ۼ�
  int PosAdd=0;           //λ������ֵ
  int ActualPosition=0;    //ʵ��λ��
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
          ActualAcceleration=pid;	
       if (ActualAcceleration!=0) 
			 {				 
         VelAccumulator+=ActualAcceleration;    
         VelAdd = VelAccumulator >> 13; 
          VelAccumulator -= VelAdd << 13;   //???????????  				 
            if(VelAdd>0)
							 ActualVelocity++;
						else if(VelAdd<0)
							 ActualVelocity--;
			if(ActualVelocity>5000)
			  	 ActualVelocity=5000;
			 if(ActualVelocity<-5000)
				  ActualVelocity=-5000;
					}
			  else
				{
				VelAccumulator=0;
				VelAdd =0;	
				ActualVelocity=0;	
				}
				PosAccumulator+=ActualVelocity;   //ActualVelocity; 
			  	PosAdd = PosAccumulator >> 13;    //?????????????
			    PosAccumulator -= PosAdd << 13;   //???????????
				if(PosAdd!=0) 
			{	 
       if(PosAdd>0)				
			 {
				 PBout(4)=0;
         	ActualPosition++;	
           if(ActualPosition>500)
            ActualPosition=500;  						 
			 }
			 else
			 {
			   PBout(4)=1; 
				 ActualPosition--;
        if(ActualPosition<-500)
            ActualPosition=-500;  				 
			 }
			  PBout(5)=~PBout(5);
		 }
				if (PosAdd==0)
					 ActualPosition=0;

}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ

}
