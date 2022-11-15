/*
 * button.c
 *
 *  Created on: Nov 2, 2022
 *      Author: HELLO SON
 */

#include "main.h"
#include"timer.h"
#include "button.h"
#define NO_OF_BUTTONS 3
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static GPIO_PinState buttonBuffer [NO_OF_BUTTONS]={BUTTON_IS_RELEASED,BUTTON_IS_RELEASED,BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer1 [NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2 [NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3 [NO_OF_BUTTONS]={BUTTON_IS_RELEASED,BUTTON_IS_RELEASED,BUTTON_IS_RELEASED};

static uint16_t buttonAddress[NO_OF_BUTTONS]={Button1_Pin,Button2_Pin,Button3_Pin};
static GPIO_TypeDef* buttonPort[NO_OF_BUTTONS]={Button1_GPIO_Port,Button2_GPIO_Port,Button3_GPIO_Port};
int DURATION;
void button_reading(void)
{
	for(uint8_t i=0;i<NO_OF_BUTTONS;i++)
	{
		debounceButtonBuffer2[i]=debounceButtonBuffer1[i];
		debounceButtonBuffer1[i]=HAL_GPIO_ReadPin(buttonPort[i], buttonAddress[i]);
		if(debounceButtonBuffer1[i]==debounceButtonBuffer2[i])
		{
			if(debounceButtonBuffer3[i]!=debounceButtonBuffer1[i])
			{
				debounceButtonBuffer3[i]=debounceButtonBuffer1[i];
				if(debounceButtonBuffer1[i]==BUTTON_IS_PRESSED)
				{buttonBuffer[i]=BUTTON_IS_PRESSED;
				DURATION=100;
				}
			}
			else
			{	DURATION--;
				if(DURATION<=0)
				{
					debounceButtonBuffer3[i]=BUTTON_IS_RELEASED;
				}
			}
		}
	}
}
int is_button_pressed(int index)
{
	if(buttonBuffer[index]==BUTTON_IS_PRESSED)
	{
		buttonBuffer[index]=BUTTON_IS_RELEASED;
		return 1;
	}
	else return 0;
}
