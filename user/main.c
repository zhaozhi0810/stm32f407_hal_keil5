
#include <stm32f4xx.h>


static void Error_Handler(void);
static void SystemClock_Config(void);



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
	
	SystemClock_Config();   //经过初始化之后，cpu的时钟已经到168M了
	
	
	led_init();
	
	key_int_init();
	
	while(1)
	{
		//什么事都不做，空转

	}
}




/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000   //改为25
  *            PLL_M                          = 25         //改为25
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25U;   //这个位置改为25，因为我的开发板的晶振是25MHz
  RCC_OscInitStruct.PLL.PLLN = 336U; 
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7U;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */

static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
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
