
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
	
	key_init();
	
	while(1)
	{
		//1.��ȡ��һ��������״̬�����ݰ�����״̬���ƵƵ�״̬
		pins = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10);
		if(pins == GPIO_PIN_RESET) //������������
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
		}
		
		
		
		//2.��ȡ�ڶ���������״̬�����ݰ�����״̬���ƵƵ�״̬
		pins = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);
		if(pins == GPIO_PIN_RESET) //������������
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
		}
		
		
		//3.��ȡ������������״̬�����ݰ�����״̬���ƵƵ�״̬
		pins = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		if(pins == GPIO_PIN_RESET) //������������
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
		}

	}
}


void SysTick_Handler(void)
{
	HAL_IncTick();
}
