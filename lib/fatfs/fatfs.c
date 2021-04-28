/*
 * fatfs.c
 *
 *  Created on: Jan 15, 2021
 *      Author: v.simonenko
 */

#include "fatfs.h"
#include "ff.h"

FATFS fs;
FIL file;
FRESULT result;

uint8_t FatFs_Init()
{
    // mount the default drive
    result = f_mount(&fs, "", 0);
    return result;
}

uint8_t file_open(const char *path)
{
	result = f_open(&file, path, FA_READ);
	return result;
}

uint8_t file_readline(char *line_buffer, uint8_t buffer_size)
{
	TCHAR *result = f_gets(line_buffer, buffer_size, &file);
	return result ? 1 : 0; //return true untill EOF or error
}

uint8_t file_close()
{
	result = f_close(&file);
	return result;
}


