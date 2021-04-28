#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "generic.h"
#include "device.h"
#include "mass_storage.h"
#include "fatfs.h"
#include <stdlib.h>

#define DEFAULT_DELAY 100
#define LEN 20

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	DWT_Delay_Init();

	MSD_Init();

	FatFs_Init();
	const char* filename = "file1.txt";
	file_open(filename);
	char line[LEN] = {0};
	file_readline(line, LEN);
	uint32_t delay = atoi(line);

	delay = delay ? delay : DEFAULT_DELAY;

	while (1)
	{
		GPIO_ToggleBits(GPIOC, PIN_LED);
		DWT_Delay_ms(500);
	}
}
