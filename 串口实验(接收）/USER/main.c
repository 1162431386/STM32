#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "send_data.h"
/****************************
������send_data.c�ļ�
�����÷��뿴Դ�ļ�
����ʵ���õ��Ǵ���3
�ô������������ݡ�

****************************/
extern char data[20];
//extern PUartHandle pUartHandle;
int main(void)
{ 
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
  usart3_init(115200);
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
  //pUartHandle_init();
	while(1)
	{
     
  
   printf("%s\r\n", data);
   
   delay_us(1);
  }
} 


