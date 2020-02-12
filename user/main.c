
#include <stm32f4xx.h>


void led_init(void)
{	
	GPIO_InitTypeDef GPIO_Init;

	//1.ʱ��ʹ��
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	
	//2.�˿�����
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_OD;  //�����©ģʽ
	GPIO_Init.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init.Pull = GPIO_PULLUP;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_Init.Alternate = ;  //GPIO��mode����λ���ù��ܵ�ʱ�򣬲Ż����ø��ù���
	HAL_GPIO_Init(GPIOE, &GPIO_Init);
	
	//3.������Ϩ���
}







/*������ʼ��*/
void key_init(void)
{	
	GPIO_InitTypeDef GPIO_Init;

	//1.ʱ��ʹ�ܣ�����ʹ�õ�ʱGPIOE
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	
	//2.�˿�����
	GPIO_Init.Mode = GPIO_MODE_INPUT;  //����ģʽ
	GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;   //���õ�����
	GPIO_Init.Pull = GPIO_NOPULL;      //�������������Ҳ����û�У���·����������
//	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;    //�������������ٶȣ�����ģʽ���Բ���
//	GPIO_Init.Alternate = ;  //GPIO��mode����λ���ù��ܵ�ʱ�򣬲Ż����ø��ù���
	HAL_GPIO_Init(GPIOE, &GPIO_Init);
	
}




/*�����жϷ�ʽ��ʼ��*/
void key_int_init(void)
{
	GPIO_InitTypeDef GPIO_Init;

	//1.ʱ��ʹ�ܣ�����ʹ�õ�ʱGPIOE
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	
	//2.�˿�����
	GPIO_Init.Mode = GPIO_MODE_IT_FALLING;  //�½����ж�ģʽ
	GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;   //���õ�����
	GPIO_Init.Pull = GPIO_NOPULL;      //�������������Ҳ����û�У���·����������

	HAL_GPIO_Init(GPIOE, &GPIO_Init);


	NVIC_SetPriority(EXTI15_10_IRQn,0xA0);  //���ü򵥵��ж����ȼ�
	NVIC_EnableIRQ(EXTI15_10_IRQn);  //�ⲿ�жϣ�10-15����һ���ⲿ�ж�
	
	
}



/*
	�������Գ����ҵ�����ʵ��Ϊ����������򵥵ķ�����
    ��һ���������µ�ʱ�򣬵�һ���Ƶ���
	�ڶ����������µ�ʱ�򣬵ڶ����Ƶ���
	�������������µ�ʱ�򣬵������Ƶ���
*/

int main(void)
{
	int i;
	GPIO_PinState pins;
	
	
	HAL_Init();  //�����ڵ�һ�����ִ��
	
	led_init();
	
	key_int_init();
	
	while(1)
	{
		//ʲô�¶���������ת

	}
}


void EXTI15_10_IRQHandler(void)
{
	uint32_t ret;
	EXTI_HandleTypeDef hexti;
	int i;
	uint32_t arr[3] = {EXTI_LINE_10,EXTI_LINE_11,EXTI_LINE_12};
	uint32_t ledarr[3] = {GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};
		
	for(i=0;i<3;i++)
	{
		hexti.Line = arr[i];       //��һ���ⲿ�ж��ߴ����ж�
		ret = HAL_EXTI_GetPending(&hexti, EXTI_TRIGGER_FALLING);
		if(ret)   
		{
			//�жϴ���Ƚϼ򵥣�ֱ�ӷ�תled
			HAL_GPIO_TogglePin(GPIOE, ledarr[i]);
			
			//���жϱ�־
			HAL_EXTI_ClearPending(&hexti, EXTI_TRIGGER_FALLING); //�½���
		}
	}
}


void SysTick_Handler(void)
{
	HAL_IncTick();
}
