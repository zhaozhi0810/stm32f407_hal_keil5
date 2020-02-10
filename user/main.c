
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


/*按键初始化*/
void key_init(void)
{	
	GPIO_InitTypeDef GPIO_Init;

	//1.时钟使能，按键使用的时GPIOE
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	
	//2.端口设置
	GPIO_Init.Mode = GPIO_MODE_INPUT;  //输入模式
	GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;   //设置的引脚
	GPIO_Init.Pull = GPIO_NOPULL;      //上拉电阻可以有也可以没有，电路本身有上拉
//	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;    //这个是设置输出速度，输入模式可以不管
//	GPIO_Init.Alternate = ;  //GPIO的mode设置位复用功能的时候，才会配置复用功能
	HAL_GPIO_Init(GPIOE, &GPIO_Init);
	
}



/*
	按键测试程序，我的例子实现为，（这是最简单的方法）
    第一个按键按下的时候，第一个灯点亮
	第二个按键按下的时候，第二个灯点亮
	第三个按键按下的时候，第三个灯点亮
*/

int main(void)
{
	int i;
	GPIO_PinState pins;
	
	
	HAL_Init();  //必须在第一个语句执行
	
	led_init();
	
	key_init();
	
	while(1)
	{
		//1.读取第一个按键的状态，根据按键的状态控制灯的状态
		pins = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10);
		if(pins == GPIO_PIN_RESET) //按键被按下了
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
		}
		
		
		
		//2.读取第二个按键的状态，根据按键的状态控制灯的状态
		pins = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);
		if(pins == GPIO_PIN_RESET) //按键被按下了
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
		}
		
		
		//3.读取第三个按键的状态，根据按键的状态控制灯的状态
		pins = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		if(pins == GPIO_PIN_RESET) //按键被按下了
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
