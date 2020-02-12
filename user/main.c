
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




/*按键中断方式初始化*/
void key_int_init(void)
{
	GPIO_InitTypeDef GPIO_Init;

	//1.时钟使能，按键使用的时GPIOE
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	
	//2.端口设置
	GPIO_Init.Mode = GPIO_MODE_IT_FALLING;  //下降沿中断模式
	GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;   //设置的引脚
	GPIO_Init.Pull = GPIO_NOPULL;      //上拉电阻可以有也可以没有，电路本身有上拉

	HAL_GPIO_Init(GPIOE, &GPIO_Init);


	NVIC_SetPriority(EXTI15_10_IRQn,0xA0);  //设置简单的中断优先级
	NVIC_EnableIRQ(EXTI15_10_IRQn);  //外部中断，10-15共用一个外部中断
	
	
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
	
	key_int_init();
	
	while(1)
	{
		//什么事都不做，空转

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
		hexti.Line = arr[i];       //哪一个外部中断线触发中断
		ret = HAL_EXTI_GetPending(&hexti, EXTI_TRIGGER_FALLING);
		if(ret)   
		{
			//中断处理比较简单，直接翻转led
			HAL_GPIO_TogglePin(GPIOE, ledarr[i]);
			
			//清中断标志
			HAL_EXTI_ClearPending(&hexti, EXTI_TRIGGER_FALLING); //下降沿
		}
	}
}


void SysTick_Handler(void)
{
	HAL_IncTick();
}
