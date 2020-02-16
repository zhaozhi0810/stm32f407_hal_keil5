
#include <stm32f4xx.h>


static void Error_Handler(void);
static void SystemClock_Config(void);



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
	
	SystemClock_Config();   //������ʼ��֮��cpu��ʱ���Ѿ���168M��
	
	
	led_init();
	
	key_int_init();
	
	while(1)
	{
		//ʲô�¶���������ת

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
  *            HSE Frequency(Hz)              = 25000000   //��Ϊ25
  *            PLL_M                          = 25         //��Ϊ25
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
  RCC_OscInitStruct.PLL.PLLM = 25U;   //���λ�ø�Ϊ25����Ϊ�ҵĿ�����ľ�����25MHz
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
