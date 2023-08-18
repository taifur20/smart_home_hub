/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <math.h>

#include "wizchip_conf.h"
#include "w5x00_mqtt_info.h"
#include "dht11.h"
#include "pzem004t.h"

#include "w5x00_network.h"
#include "httpServer.h"
#include "web_page.h"

//GitHub link: https://github.com/eziya
#include "fatfs_sd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */
uint32_t VOC_VALUE = 0;
uint8_t adc_conv_complete_flag = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_FMC_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void send_to_cloud(float temperature, float humidity, float voltage, float current, float power,
		           float energy, float frequency, float pf, float voc);
void http_server_demo(wiz_NetInfo *net_info);
void write_image_sd(void);
void test_sd_card(void);
//void read_pzem004t(void);
/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFF);

  return ch;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  // Conversion Complete & DMA Transfer Complete As Well
  adc_conv_complete_flag = 1;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
wiz_NetInfo net_info =
  {
	  .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
	  .ip = {192, 168, 0, 2},                      // IP address
	  .sn = {255, 255, 255, 0},                    // Subnet Mask
	  .gw = {192, 168, 0, 1},                      // Gateway
	  .dns = {8, 8, 8, 8},                         // DNS server
	  .dhcp = NETINFO_DHCP                         // Dynamic IP, for static ip use NETINFO_STATIC

  };

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FMC_Init();
  MX_TIM6_Init();
  MX_USART6_UART_Init();
  MX_ADC1_Init();
  MX_USART3_UART_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  // ----------------------------------------------------------------------------------------------------
  // Call main function - example funcion
  // Select one application
  // ----------------------------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------------------------
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  pzem_values pzem_sensor1; //Connected to Arduino D8 and D9 pins of TOE Shield

  dht11_t dht; //Connected to Arduino D3 pin of TOE Shield
  init_dht11(&dht, &htim6, DHT11_PIN_GPIO_Port, DHT11_PIN_Pin);

  int mqtt_connect_flag = 0;
  int count = 0;
  //takes three attempts to connect the MQTT broker
  while(count<3){
	  int val = mqtt_connect(&net_info);
	  if(val==1) {
		  mqtt_connect_flag = 1;
		  mqtt_subscribe(&net_info);
		  break;
	  }
	  count++;
  }

  while (1)
  {
	  read_pzem004t(&pzem_sensor1, &huart6);
	  float volt = pzem_sensor1.voltage;
	  float cur = pzem_sensor1.current;
	  float pow = pzem_sensor1.power;
	  float enrg = pzem_sensor1.energy;
	  float freq = pzem_sensor1.frequency;
	  float pfactor = pzem_sensor1.pf;

      float temp = 0;
      float humid = 0;
	  int result = readDHT11(&dht);
      if(result == 1){
    	  temp = dht.temperature;
    	  humid = dht.humidity;
      }

      HAL_ADC_Start_DMA(&hadc1, &VOC_VALUE, 1);
      float voc_value = 0;
      if(adc_conv_complete_flag == 1){
    	  voc_value = VOC_VALUE;
    	  adc_conv_complete_flag = 0;
      }

      //Check if mqtt is connected or not. If not connected then connect
      if(!mqtt_connect_flag){
		  int result = mqtt_connect(&net_info);
		  if(result==1) mqtt_connect_flag = 1;
		  else continue;
	  }

      //If connected then sends the data to MQTT broker
	  send_to_cloud(temp, humid, volt, cur, pow, enrg, freq, pfactor, voc_value);

	  //publish data to every 5 seconds, adjust as per your requirement
	  HAL_Delay(5000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 108;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FMC_NORSRAM_DEVICE;
  hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hsram1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram1.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
  hsram1.Init.PageSize = FMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 255;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RELAY_1_Pin|RELAY_2_Pin|RELAY_3_Pin|RELAY_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(W5x00_RST_GPIO_Port, W5x00_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : W5x00_BRDY0_Pin W5x00_BRDY1_Pin W5x00_BRDY2_Pin W5x00_BRDY3_Pin */
  GPIO_InitStruct.Pin = W5x00_BRDY0_Pin|W5x00_BRDY1_Pin|W5x00_BRDY2_Pin|W5x00_BRDY3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : RELAY_1_Pin RELAY_2_Pin RELAY_3_Pin RELAY_4_Pin */
  GPIO_InitStruct.Pin = RELAY_1_Pin|RELAY_2_Pin|RELAY_3_Pin|RELAY_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : DHT11_PIN_Pin */
  GPIO_InitStruct.Pin = DHT11_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT11_PIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : W5x00_INT_Pin */
  GPIO_InitStruct.Pin = W5x00_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(W5x00_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : W5x00_RST_Pin */
  GPIO_InitStruct.Pin = W5x00_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(W5x00_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//This function make two integers from the float value add form a data array to send the cloud
void send_to_cloud(float temperature, float humidity, float voltage, float current, float power, float energy, float frequency, float pf, float voc)
{
	int tempInt1 = temperature;
	float tempF = temperature - tempInt1;
	int tempInt2 = trunc(tempF * 100);

	int humidInt1 = humidity;
	float humidF = humidity - humidInt1;
	int humidInt2 = trunc(humidF * 100);

	int voltInt1 = voltage;
	float voltF = voltage - voltInt1;
	int voltInt2 = trunc(voltF * 100);

	int curInt1 = current;
	float curF = current - curInt1;
    int curInt2 = trunc(curF * 100);

    int powInt1 = power;
    float powF = power - powInt1;
    int powInt2 = trunc(powF * 100);

    int enrgInt1 = energy;
    float enrgF = energy - enrgInt1;
    int enrgInt2 = trunc(enrgF * 100);

    int freqInt1 = frequency;
    float freqF = frequency - freqInt1;
    int freqInt2 = trunc(freqF * 100);

    int pfInt1 = pf;
    float pfF = pf - pfInt1;
    int pfInt2 = trunc(pfF * 100);

    int vocInt1 = voc;
    float vocF = voc - vocInt1;
    int vocInt2 = trunc(vocF * 100);

    char data_array[200];
    snprintf(data_array, sizeof(data_array), "%d.%d,%d.%d,%d.%d,%d.%d,%d.%d,%d.%d,%d.%d,%d.%d,%d.%d",
    		tempInt1, tempInt2, humidInt1, humidInt2, voltInt1, voltInt2, curInt1, curInt2, powInt1, powInt2, enrgInt1, enrgInt2,
			freqInt1, freqInt2, pfInt1, pfInt2, vocInt1, vocInt2);
    printf("%s\n", data_array);
    mqtt_publish(data_array);

}

//This function form an http server to show the image.
void http_server_demo(wiz_NetInfo *net_info)
{
  uint8_t i = 0;

  wizchip_network_initialize(net_info);
  wizchip_network_information(net_info);

  httpServer_init(g_http_send_buf, g_http_recv_buf, HTTP_SOCKET_MAX_NUM, g_http_socket_num_list);

  reg_httpServer_webContent("index.html", index_page);

  /* Infinite loop */
  while (1)
  {
    for (i = 0; i < HTTP_SOCKET_MAX_NUM; i++)
    {
      /* Run HTTP server */
      httpServer_run(i);
    }
  }
}

//https://github.com/STMicroelectronics/STM32CubeF7/tree/master/Projects/STM32F769I_EVAL/Applications/Camera/Camera_To_USBDisk

void write_image_sd(void)
{
	FATFS fs;
	FRESULT res1, res2;
	FIL MyFile;
	uint32_t byteswritten;  /* File write count */
	uint8_t str[30];

	/* Image header */
	const uint32_t aBMPHeader[14]=
	{0xFA364D42, 0x00000005, 0x00360000, 0x00280000, 0x01E00000, 0x01100000, 0x00010000,
	 0x00000018, 0xF5400000, 0x00000006, 0x00000000, 0x00000000, 0x00000000, 0x0000};

	static uint32_t   CameraResX = 480;
	static uint32_t   CameraResY = 320;

    #define CONVERTED_FRAME_BUFFER        3 + (CameraResX * CameraResY * 3)

	sprintf((char *)str,"image.bmp");

	/* Mount SD Card */
    if(f_mount(&fs, "", 0) != FR_OK)
    {
		_Error_Handler(__FILE__, __LINE__);
    }
	/* Create and Open a new text file object with write access */
	if(f_open(&MyFile, (const char*)str, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	else
	{
		/* Write data to the BMP file */
		res1 = f_write(&MyFile, (uint32_t *)aBMPHeader, 54, (void *)&byteswritten);

		res2 = f_write(&MyFile, (uint8_t *)((uint8_t *)CONVERTED_FRAME_BUFFER),
	    		       (CameraResX * CameraResY * 3),
	    		       (void *)&byteswritten);


		if((res1 != FR_OK) || (res2 != FR_OK) || (byteswritten == 0))
	    {
			_Error_Handler(__FILE__, __LINE__);
	    }
	    else
	    {
	      /* Close the open BMP file */
	      f_close(&MyFile);

	    }
	}
    /* Unmount SDCARD */
	if(f_mount(NULL, "", 1) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);
}

void test_sd_card(void)
{
	FATFS fs;
	FATFS *pfs;
	FIL fil;
	FRESULT fres;
	DWORD fre_clust;
	uint32_t totalSpace, freeSpace;
	char buffer[100];

	/* Mount SD Card */
	if(f_mount(&fs, "", 0) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);

	/* Open file to write */
	if(f_open(&fil, "first.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);

	/* Check freeSpace space */
	if(f_getfree("", &fre_clust, &pfs) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);

	totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);

	/* free space is less than 1kb */
	if(freeSpace < 1)
		_Error_Handler(__FILE__, __LINE__);

	/* Writing text */
	f_puts("STM32 SD Card I/O Example via SPI\n", &fil);
	f_puts("Save the world!!!", &fil);

	/* Close file */
	if(f_close(&fil) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);

	/* Open file to read */
	if(f_open(&fil, "first.txt", FA_READ) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);

	while(f_gets(buffer, sizeof(buffer), &fil))
	{
		/* SWV output */
		printf("%s", buffer);
		fflush(stdout);
	}

	/* Close file */
	if(f_close(&fil) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);

	/* Unmount SDCARD */
	if(f_mount(NULL, "", 1) != FR_OK)
		_Error_Handler(__FILE__, __LINE__);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
