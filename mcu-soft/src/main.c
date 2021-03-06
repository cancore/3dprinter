/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    30-December-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F7xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdarg.h>
#include <command.h>

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USBD_HandleTypeDef USBD_Device;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This sample code shows how to use GPIO HAL API to toggle GPIOB-GPIO_PIN_0 IO
    in an infinite loop. It is possible to connect a LED between GPIOB-GPIO_PIN_0
    output and ground via a 330ohm resistor to see this external LED blink.
    Otherwise an oscilloscope can be used to see the output GPIO signal */

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* STM32F7xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 216 MHz */
  SystemClock_Config();

  /* -1- Enable GPIO Clock (to be able to program the configuration registers) */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  {
      GPIO_InitTypeDef  GPIO_InitStruct;
      /* -2- Configure IO in output push-pull mode to drive external LEDs */
      GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull  = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
      
      GPIO_InitStruct.Pin = GPIO_PIN_0;         //led2
      HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_15;        //led1
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      
      GPIO_InitStruct.Pin = GPIO_PIN_1;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_5;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_6;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_7;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_8;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_9;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_10;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);               
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);               
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);               
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);               
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);               
  }
  
  //inputs (for sensors)
  {
      GPIO_InitTypeDef  GPIO_InitStruct;
      /* -2- Configure IO in output push-pull mode to drive external LEDs */
      GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
      GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; //GPIO_SPEED_FREQ_VERY_HIGH;
      
      GPIO_InitStruct.Pin = GPIO_PIN_0;         //U13, pin6 - input laser sensor #1 (X axis, blue)
      HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_1;         //U13, pin5 - input laser sensor #2 (Y axis, green)
      HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
      GPIO_InitStruct.Pin = GPIO_PIN_2;         //U13, pin4 - input laser sensor #3 (Z axis, yellow)
      HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);      
  }
  
    /* Init Device Library */
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
  /* Add CDC Interface Class */
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
  /* Start Device Process */
  USBD_Start(&USBD_Device);
  
  
  cmd_enter_command_loop();
  
  /* -3- Toggle IO in an infinite loop 
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_0);
    // Insert delay 100 ms
    HAL_Delay(100);
  }
  */
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            PLL_R                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)        //don't forget to change main_cpu_clock_speed() below to conform
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON; //RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 10;
  RCC_OscInitStruct.PLL.PLLR = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1) {};
  }

  /* Activate the OverDrive to reach the 216 Mhz Frequency */
//   if(HAL_PWREx_EnableOverDrive() != HAL_OK)
//   {
//     while(1) {};
//   }

  /* Select PLLSAI output as USB clock source */
//   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
//   PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
//   PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
//   PeriphClkInitStruct.PLLSAI.PLLSAIQ = 7; 
//   PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
//   if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct)  != HAL_OK)
//   {
//     Error_Handler();
//   }
   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
   PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
   if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct)  != HAL_OK)
   {
    while(1) {};
   }


  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    while(1) {};
  }
}

int main_cpu_clock_speed()
{
    return 160000000;   //don't forget to change SystemClock_Config() above to conform
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  main_fail_with_error("assert in file: %s, line: %d\n", file, line);
}
#endif

void main_fail_with_error(char * fmt, ...)
{
     va_list vl;
     va_start(vl, fmt);
     vfprintf(stderr /*STDERR_FILENO*/, fmt, vl);      //see newlib-supp/newlib-supp.c, write function
     va_end(vl);
    
    while(1)
    {
    }
}

//YS: warning, looks like Cortex-M0 have no it at all... but I hope Kolia will not convince me to use them...
//also the counter should be enabled first..
static void enable_cpu_ticks()
{   //http://stackoverflow.com/questions/36378280/stm32-how-to-enable-dwt-cycle-counter 
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;        //see ARM®v7-M Architecture Reference Manual, page page 593,
    DWT->LAR = 0xC5ACCE55; //holy shit, http://infocenter.arm.com/help/topic/com.arm.doc.ihi0029d/IHI0029D_coresight_architecture_spec_v2_0.pdf, page B2-48 says
                           //A write of 0xC5ACCE55 enables further write access to this device. An invalid write has the affect of removing write access.
}

int main_get_cpu_ticks()
{
    static int first_time = 1;
    if (first_time)
    {
        enable_cpu_ticks();
        first_time = 0;        
    }
    
    int const ret = DWT->CYCCNT; //*(uint32_t volatile*)0xE0001004; //DWT_CYCCNT; http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0439c/BABJFFGJ.html
    return ret;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
