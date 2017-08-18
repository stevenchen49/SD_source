/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */


/* 2017.8.9 add by chen -------------------------*/
#include "bsp_sdcard.h"         /* SD spi driver */
/* 2017.8.9 add by chen -------------------------*/


/* Definitions of physical drive number for each drive */
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 0 */
#define DEV_RAM		1	/* Example: Map Ramdisk to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */



/* 2017.8.9 add by chen ************************************************ */

/*-----------------------------------------------------------------------*/
/* Real Time Clock                                                       */
/*-----------------------------------------------------------------------*/
DWORD get_fattime (void)
{
	RTC_DateTypeDef   rtc_date;
	RTC_TimeTypeDef   rtc_time;

	BYTE    year;
	BYTE    month;
	BYTE    date;
	BYTE    hour;
	BYTE    minute;
	BYTE    second;

	DWORD   fattime;

	RTC_GetDate(RTC_Format_BIN,&rtc_date);
	RTC_GetTime(RTC_Format_BIN,&rtc_time);

	year    = rtc_date.RTC_Year;
	month   = rtc_date.RTC_Month;
	date    = rtc_date.RTC_Date;

	hour    = rtc_time.RTC_Hours;
	minute  = rtc_time.RTC_Minutes;
	second  = rtc_time.RTC_Seconds;

	fattime = (year<<25)+(month<<21)+(date<<16)+(hour<<11)+(minute<<5)+second;

	return fattime;
}

/*-----------------------------------------------------------------------*/
/* SD/MMC disk initialize                                                */
/*-----------------------------------------------------------------------*/
uint8_t MMC_disk_initialize (void)
{
	return SD_Init();
}

/*-----------------------------------------------------------------------*/
/* MMC disk status                                                       */
/*-----------------------------------------------------------------------*/
uint8_t MMC_disk_status (void)
{
	uint8_t   err;

	err = SD_GetCID(SD_CID_Data);
	if(err != SD_ERR_NONE) return err;
	err = SD_GetCSD(SD_CSD_Data);
	return err;
}

/*-----------------------------------------------------------------------*/
/* MMC disk read                                                         */
/*-----------------------------------------------------------------------*/
uint8_t MMC_disk_read(BYTE *buff, DWORD sector, UINT count)
{
	uint8_t   err;

	if(count == 1){
		err = SD_ReadSingleBlock(sector,buff);
	}else{
		err = SD_ReadMultiBlock(sector,buff,count);
	}
	return err;
}

/*-----------------------------------------------------------------------*/
/* MMC disk write                                                        */
/*-----------------------------------------------------------------------*/
uint8_t MMC_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
	uint8_t   err;

	if(count ==1){
		err = SD_WriteSingleBlock(sector,(uint8_t *)buff);
	}else{
		err = SD_WriteMultiBlock(sector,(uint8_t *)buff,count);
	}
	return err;
}




/*-----------------------------------------------------------------------*/
/* RAM disk initialize                                                   */
/*-----------------------------------------------------------------------*/
uint8_t RAM_disk_initialize (void)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* RAM disk status                                                       */
/*-----------------------------------------------------------------------*/
uint8_t RAM_disk_status (void)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* RAM disk read                                                         */
/*-----------------------------------------------------------------------*/
uint8_t RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* RAM disk write                                                        */
/*-----------------------------------------------------------------------*/
uint8_t RAM_disk_write(const BYTE *buff, DWORD sector, UINT count)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* USB disk initialize                                                   */
/*-----------------------------------------------------------------------*/
uint8_t USB_disk_initialize (void)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* USB disk status                                                       */
/*-----------------------------------------------------------------------*/
uint8_t USB_disk_status (void)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* USB disk read                                                         */
/*-----------------------------------------------------------------------*/
uint8_t USB_disk_read(BYTE *buff, DWORD sector, UINT count)
{ return 0; }

/*-----------------------------------------------------------------------*/
/* USB disk write                                                        */
/*-----------------------------------------------------------------------*/
uint8_t USB_disk_write(const BYTE *buff, DWORD sector, UINT count)
{ return 0; }
    
/* 2017.8.9 add by chen ************************************************ */



/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_status();

		// translate the reslut code here
        stat = result;

		return stat;

	case DEV_USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here
        stat = result;

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here
        if(result == SD_ERR_NONE)             res = RES_OK;
        if(result == SD_ERR_TIMEOUT)          res = RES_NOTRDY;
        if(result == SD_ERR_RESPONSE_FAILURE) res = RES_ERROR;

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here
        if(result == SD_ERR_NONE)             res = RES_OK;
        if(result == SD_ERR_TIMEOUT)          res = RES_NOTRDY;
        if(result == SD_ERR_RESPONSE_FAILURE) res = RES_ERROR;

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		switch(cmd){

			case CTRL_SYNC:
				res = RES_OK;
				break;

			case GET_SECTOR_SIZE:
				*(DWORD*)buff = 512;
				res = RES_OK;
				break;

			case GET_BLOCK_SIZE:
				*(DWORD*)buff = 512;
				res = RES_OK;
				break;

			case GET_SECTOR_COUNT:
				if((SD_CSD_Data[0]&0xC0)==0x40){
					*(DWORD*)buff = SD_CSD_Data[9] + ((uint32_t)SD_CSD_Data[8]<<8)+((uint32_t)(SD_CSD_Data[7]&0x63)<<16) + 1;
					*(DWORD*)buff = ((*(DWORD*)buff)<<9)*2;
					res = RES_OK;
				}else{
					res = RES_ERROR;
				}
				break;

			default:
				res = RES_PARERR;
				break;
		}
		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}

