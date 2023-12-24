/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>

#include <string.h>
#include <stdlib.h>
#include "aes.h"
#include "textlcd.h"
#include "pushButton.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AES.C"



int main(void)
{

//	const char* textStr[4] =
//	{
//	"Hello MCU World!",
//	"CNDI Inc.",
//	"TEXTLCD TEST",
//	"Success!"
//	};
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
	/* USER CODE BEGIN 2 */
	TextlcdInit();
	bool condition1=true;
	int button;
	char value1[48];
	char value2[48];
	char value3[48];
	char value4[16];
	char value5[16];
	char* animation[16]={
			"/       \\       ",
			" -       |      ",
			"  \\       /     ",
			"   |       -    ",
			"    /       \\   ",
			"     -       |  ",
			"      \\       / ",
			"       |       -",
			"\\       /       ",
			" |       -      ",
			"  /       \\     ",
			"   -       |    ",
			"    \\       /   ",
			"     |       -  ",
			"      /       \\ ",
			"       -       |"
						};
	char *In = calloc(1024, sizeof(char));
	int init_len = 0;
	BYTE Key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	BYTE ENC[1024];
	BYTE DEC[1024];

	//시작 화면
	clearScreen(ALL_LINE);
	writeTextLine(LINE_1, "Press any button");
	int i=0;
	int j=0;
	writeTextLine(LINE_2, animation[0]);
	while(PushBtnRead()==-1){
		i++;
		if(i==2){
			i=0;
			j++;
			writeTextLine(LINE_2, animation[j]);
			if(j==15){j=0;}
		}

	}
	clearScreen(ALL_LINE);
	 writeTextLine(LINE_1, "<-This buttons ");
	 writeTextLine(LINE_2, "are 0~f hex.   /");
	 HAL_Delay(3000);
	 clearScreen(ALL_LINE);
	 writeTextLine(LINE_1, "0)Find inverse");
	 writeTextLine(LINE_2, "1)AES encryption");



	while (condition1){
		button = PushBtnRead();

		//inverse 찾기
		if(button==0){
			while (PushBtnRead()==button){};
			int a;
			int b;
			clearScreen(ALL_LINE);
		    writeTextLine(LINE_1, "Press the button to");
		    writeTextLine(LINE_2, "select the byte.");
			while (condition1){
				button = PushBtnRead();
				if (button!=-1){
					a=button;
					sprintf(value3,"%s","1byte to calcula");
					sprintf(value4,"%s","-te:0x");
					sprintf(value1,"%x",button);
					strcat(value4, value1);
					clearScreen(ALL_LINE);
				    writeTextLine(LINE_1, value3);
				    writeTextLine(LINE_2, value4);
				    condition1=false;}
			}
			while (PushBtnRead()==button){};
			condition1=true;
			while (condition1){
				button = PushBtnRead();
				if(button!=-1){
					b=button;
					sprintf(value2,"%x",button);
					strcat(value4, value2);
					writeTextLine(LINE_2, value4);
					condition1=false;}
			}


				HAL_Delay(1000);
				int c = 16 * a + b;
				char hexadecimal[4];
				sprintf(hexadecimal, "%02x", c);
				clearScreen(ALL_LINE);
				unsigned char hex = 0x01;
				    do {
				        if (gmul(hex, c) == 1) {
				            sprintf(value1,"%02x",hex);
				            sprintf(value2,"%s","0x");
							strcat(value2, hexadecimal);
							strcat(value2, " is 0x");
							strcat(value2, value1);
							strcat(value2, ".");
							writeTextLine(LINE_1, "The inverse of");
				            writeTextLine(LINE_2, value2);
				            break;
				        }
				        hex++;
				    } while (hex != 0x01);

				    return 0;

		}

		if(button==1){
			sprintf(value1,"%s","");
			sprintf(value2,"%s","");
			sprintf(value3,"%s","");
			sprintf(value4,"%s","");
			int index=0;
			int index2=0;
			int index3=0;
			char result[48];
			while (PushBtnRead()==button){};

			//분석할 원문 입력 형태 선택
			clearScreen(ALL_LINE);
		    writeTextLine(LINE_1, "Select input opt");
		    writeTextLine(LINE_2, "-ion to encript");
		    HAL_Delay(2500);
			clearScreen(ALL_LINE);
		    writeTextLine(LINE_1, "0)characters");
		    writeTextLine(LINE_2, "1)hex values");
		    while (condition1){
		    	button = PushBtnRead();

		    	//문자열 암호화
		    	if(button==0){
					clearScreen(ALL_LINE);
					writeTextLine(LINE_2, "ASCII CODE:0x");
		    		while (PushBtnRead()==button){};
				while (condition1){
					button = PushBtnRead();

					//입력 후 6초간 입력이 없으면 자동으로 계산
					if (button==-1 && strcmp(value2, "") == 0 && strcmp(value3, "") != 0)
					 {
						HAL_Delay(20);
					 index3++;
					 if(index3>300){
						 index3=0;
						sprintf(result,"%s",hexToAscii(value2));
						if (strcmp(result, "error")==0){
							clearScreen(ALL_LINE);
							writeTextLine(LINE_1, "Odd number of ");
							writeTextLine(LINE_2, "items entered");
							HAL_Delay(3000);
							clearScreen(ALL_LINE);
							writeTextLine(LINE_1, value3);
							writeTextLine(LINE_2, value4);
						}

						else {condition1=false;}
					 }
					 }

					//
					if (button!=-1){
						index3=0;
						sprintf(value4,"%s","ASCII CODE:0x");
						sprintf(value1,"%x",button);
						strcat(value2, value1);
						strcat(value4, value2);
						writeTextLine(LINE_2, value4);
						index++;
						while (PushBtnRead()==button){};
						HAL_Delay(50);
						if (index==2){
							index=0;
						    HAL_Delay(500);
							int k;
							sscanf(value2,"%x",&k);
							sprintf(value2,"%c",(char)k);
							strcat(value3, value2);
							sprintf(value2,"%s","");
							writeTextLine(LINE_1, value3);
							writeTextLine(LINE_2, "ASCII CODE:0x  ");
							index2++;
					}
						if (index2==16){
							index2=0;
							condition1=false;
							HAL_Delay(2000);

						}
						while (PushBtnRead()==button){};
				}
		}



				//문자열 암호화 계산 및 출력
				clearScreen(ALL_LINE);
			    strcpy(In, value3);
				init_len = strlen(In);
				while(strlen(In) % 16 != 0) In[strlen(In)] = '.';

				int Len = strlen(In) + 1;
				AES_ECB_Encrypt(In, Key, ENC, Len);


				printf("암호화:\t");
				sprintf(value1,"%s","");
				sprintf(value2,"%s","");
				for (int i = 0; i < Len; i++) {
					sprintf(value1,"%c",ENC[i]);
					strcat(value2, value1);
				};
				writeTextLine(LINE_1, "Encryption");
				writeTextLine(LINE_2, value2);
				printf("\n");


		    	}


		    	//16진수 암호화
		    	if(button==1){
		    		clearScreen(ALL_LINE);
				    writeTextLine(LINE_1, "Calculate per 1 ");
				    writeTextLine(LINE_2, "byte---Press Btn");
				    bool condition2=true;
		    		while (PushBtnRead()==button){};


		    						while (condition1){
		    							button = PushBtnRead();

		    							//입력 후 6초간 입력이 없으면 자동으로 계산
		    							if (button==-1 && strcmp(value3, "") != 0)
		    							 {
		    								HAL_Delay(20);
		    							 index3++;
		    							 if(index3>300){
		    								index3=0;
		    								sprintf(result,"%s",hexToAscii(value3));
		 		    						if (strcmp(result, "error")==0){
		 		    							clearScreen(ALL_LINE);
		 										writeTextLine(LINE_1, "Odd number of ");
		 										writeTextLine(LINE_2, "items entered");
		 										HAL_Delay(3000);
		 										clearScreen(ALL_LINE);
		 										writeTextLine(LINE_1, value3);
		 										writeTextLine(LINE_2, value4);
		 		    						}
		 		    						else {condition1=false;}

		    							 }
		    							 }

		    							//
		    							if (button!=-1){
		    								while(condition2){
		    									clearScreen(ALL_LINE);
		    									condition2=false;
		    								}
		    								index3=0;
		    								index++;
		    								sprintf(value1,"%x",button);
		    								strcat(value3, value1);
		    								if (index<=16){
		    									clearScreen(ALL_LINE);
			    								writeTextLine(LINE_1, value3);
		    								}
		    								if (16<index){
		    									strcat(value4,value1);
												writeTextLine(LINE_2, value4);
											}
		    								if (index==32){
		    									index=0;
		    									HAL_Delay(1000);
		    									condition1=false;
		    								}
		    								HAL_Delay(30);
		    								while (PushBtnRead()==button){};
		    						}
		    				}
		    						clearScreen(ALL_LINE);
		    						//16진수를 1byte 단위로 변환
		    						sprintf(result,"%s",hexToAscii(value3));

		    						//문자열 암호화 계산 및 출력
									strcpy(In, result);
									init_len = strlen(In);
									while(strlen(In) % 16 != 0) In[strlen(In)] = '.';

									int Len = strlen(In) + 1;
									AES_ECB_Encrypt(In, Key, ENC, Len);

									printf("암호화:\t");
									sprintf(value1,"%s","");
									sprintf(value2,"%s","");
									sprintf(value3,"%s","");
									for (int i = 0; i < 8; i++) {
										sprintf(value1,"%x",ENC[i]);
										strcat(value2, value1);
									};
									for (int i = 8; i < 16; i++) {
										sprintf(value1,"%02x",ENC[i]);
										strcat(value3, value1);
									};
									writeTextLine(LINE_1, value2);
									writeTextLine(LINE_2, value3);



		    	}


		    }

//				char *In = calloc(1024, sizeof(char));
//				int init_len = 0;
//				BYTE Key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
//				BYTE ENC[1024];
//				BYTE DEC[1024];

//
//			    strcpy(In, value3);
//				init_len = strlen(In);
//				while(strlen(In) % 16 != 0) In[strlen(In)] = '.';
////
//				printf("\n원문:\t");
//				sprintf(value1,"%s","");
//				sprintf(value2,"%s","");
//				for (int i = 0; i < init_len; i++) {
//					sprintf(value1,"%c",In[i]);
//					strcat(value2, value1);
//				};
//				printf("\n");
//				int Len = strlen(In) + 1;
//				AES_ECB_Encrypt(In, Key, ENC, Len);
////
//				printf("암호화:\t");
//				sprintf(value1,"%s","");
//				sprintf(value2,"%s","");
//				for (int i = 0; i < Len; i++) {
//					sprintf(value1,"%x",ENC[i]);
//					strcat(value2, value1);
//				};
//				remove_spaces(value2);
//				keep_first_16_chars(value2);
//				writeTextLine(LINE_2, value2);
//				writeTextLine(LINE_2, value2);

//
//
//				printf("암호화:\t");
//				sprintf(value1,"%s","");
//				sprintf(value2,"%s","");
//				for (int i = 0; i < Len; i++) {
//					sprintf(value1,"%c",ENC[i]);
//					strcat(value2, value1);
//				};
//				writeTextLine(LINE_1, "Encryption");
//				writeTextLine(LINE_2, value2);
//				printf("\n");
////
//
//				memset(DEC, 0, sizeof(DEC));
//				AES_ECB_Decrypt(ENC, Key, DEC, Len);
//				printf("복호화:\t", DEC);
//				for (int i = 0; i < init_len; i++) printf("%c", DEC[i]);
//				printf("\n");
//
//				free(In);
//				return 0;





	}


}
}







/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0
                           PC1 PC2 PC3 PC4
                           PC5 PC6 PC7 PC8
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD0
                           PD1 PD2 PD3 PD4
                           PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
