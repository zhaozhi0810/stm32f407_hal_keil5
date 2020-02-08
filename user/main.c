
#include <stm32f4xx.h>


void led_init(void)
{	
	GPIO_InitTypeDef GPIO_Init;

	//1.时钟使能
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	
	//2.端口设置
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_OD;  //输出开漏模式
	GPIO_Init.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init.Pull = GPIO_PULLUP;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_Init.Alternate = ;  //GPIO的mode设置位复用功能的时候，才会配置复用功能
	HAL_GPIO_Init(GPIOE, &GPIO_Init);
	
	//3.点亮或熄灭灯
}


int main(void)
{
	HAL_Init();  //必须在第一个语句执行
	
	led_init();
	
	while(1)
	{

	}
}
