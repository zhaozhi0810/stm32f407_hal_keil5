
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


int main(void)
{
	HAL_Init();  //�����ڵ�һ�����ִ��
	
	led_init();
	
	while(1)
	{

	}
}
