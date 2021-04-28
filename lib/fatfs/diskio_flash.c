/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "stm32f10x_flash.h"

/* Definitions of physical drive number for each drive */
#define DEV_FLASH	0	/* Map Flash memory to physical drive 0 */

static volatile DSTATUS dstat = STA_NOINIT;	/* Physical drive status */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive number to identify the drive */
)
{
	if(pdrv)
		return STA_NOINIT; /* Supports only drive 0 */
	return dstat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	if(pdrv)
		return STA_NOINIT; /* Supports only drive 0 */
	else
		dstat &= ~STA_NOINIT; /* Clear STA_NOINIT flag */
	return dstat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	if (pdrv || !count) return RES_PARERR;		/* Check parameter */
	if (dstat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	uint32_t read_address = FLASH_DISK_START_ADDRESS + sector * FF_MIN_SS;
	uint32_t *buff_address = (uint32_t*) buff;
	uint32_t read_length = count * FF_MIN_SS;
	uint32_t i;

	for (i = 0; i < read_length; i += 4)
	{
		*buff_address = (*(volatile uint32_t*) (read_address + i)); //read flash 4 byte at address
		buff_address++;
	}

	return RES_OK;
}
