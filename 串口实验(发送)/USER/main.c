#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
/**********************************
���ͺ���������
void SendChar(uint8_t Data)   //���͵����ַ���
void SendString(char *str)    //�����ַ���
void Send_Data(char *fmt, ...)  //����һ֡�����ɱ䳤���ݣ���������������
��һ������Ϊ�������ͣ��÷���printfһ����ע�ⷢ��ʱ��Ҫ�пո񣬵ڶ��������������������ͣ��͵�һ��ƥ��ʹ��
������������uart���涨��

***********************************/


int main(void)
{ 
   float c=111.26;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	while(1)
	{
    Send_Data("%f",c);
    //delay_ms(20);
  }
} 


