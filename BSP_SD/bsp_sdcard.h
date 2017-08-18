
#ifndef __BSP_SDCARD_H
#define __BSP_SDCARD_H
/*
*********************************************************************************************************
*                                            INCLUDE HEADER FILES
*********************************************************************************************************
*/
#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>

#include <ff.h>
#include <string.h>
#include <stdio.h>
#include <bsp_rtc.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/
#define SD_SPI_SPEED_HIGH                               1
#define SD_SPI_SPEED_LOW                                0

#define SD_CS_ENABLE()   GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SD_CS_DISABLE()    GPIO_SetBits(GPIOB,GPIO_Pin_12)


/* SD CMD ------------------------------------------------ */
#define NO_RELEASE                                       0
#define RELEASE                                          1 

#define SD_TYPE_ERR                                   0X00
#define SD_TYPE_MMC                                   0X01
#define SD_TYPE_V1                                    0X02
#define SD_TYPE_V2                                    0X04
#define SD_TYPE_V2HC                                  0X06

#define CMD0                                          0x40      //ø®∏¥Œª
#define CMD1                                             1
#define CMD8                                             8      //√¸¡Ó8 £¨SEND_IF_COND
#define CMD9                                             9      //√¸¡Ó9 £¨∂¡CSD ˝æ›
#define CMD10                                           10      //√¸¡Ó10£¨∂¡CID ˝æ›
#define CMD12                                           12      //√¸¡Ó12£¨Õ£÷π ˝æ›¥´ ‰
#define CMD16                                           16      //√¸¡Ó16£¨…Ë÷√SectorSize ”¶∑µªÿ0x00
#define CMD17                                           17      //√¸¡Ó17£¨∂¡sector
#define CMD18                                           18      //√¸¡Ó18£¨∂¡Multi sector
#define ACMD23                                          23      //√¸¡Ó23£¨…Ë÷√∂‡sector–¥»Î«∞‘§œ»≤¡≥˝N∏ˆblock
#define CMD24                                           24      //√¸¡Ó24£¨–¥sector
#define CMD25                                           25      //√¸¡Ó25£¨–¥Multi sector
#define ACMD41                                          41      //√¸¡Ó41£¨”¶∑µªÿ0x00
#define CMD55                                           55      //√¸¡Ó55£¨”¶∑µªÿ0x01
#define CMD58                                           58      //√¸¡Ó58£¨∂¡OCR–≈œ¢
#define CMD59                                           59      //√¸¡Ó59£¨ πƒ‹/Ω˚÷πCRC£¨”¶∑µªÿ0x00

#define MSD_DATA_OK                                   0x05
#define MSD_DATA_CRC_ERROR                            0x0B
#define MSD_DATA_WRITE_ERROR                          0x0D
#define MSD_DATA_OTHER_ERROR                          0xFF

#define MSD_RESPONSE_NO_ERROR                         0x00
#define MSD_IN_IDLE_STATE                             0x01
#define MSD_ERASE_RESET                               0x02
#define MSD_ILLEGAL_COMMAND                           0x04
#define MSD_COM_CRC_ERROR                             0x08
#define MSD_ERASE_SEQUENCE_ERROR                      0x10
#define MSD_ADDRESS_ERROR                             0x20
#define MSD_PARAMETER_ERROR                           0x40
#define MSD_RESPONSE_FAILURE                          0xFF

#define BLOCK_SIZE                                     512 

#define SD_ERR_NONE                                   0x00
#define SD_ERR_TIMEOUT                                0x01
#define SD_ERR_RESPONSE_FAILURE                       0xFF

#define SD_DATA_TYPE_DEC                              0x00
#define SD_DATA_TYPE_HEX                              0x01
#define SD_DATA_TYPE_FP                               0x02
/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/
extern   u8      SD_CID_Data[18];
extern   u8      SD_CSD_Data[18];

extern   DWORD   SD_Total_Capacity;
extern   DWORD   SD_Free_Capacity;

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void      SD_Card_SPI_Init        (void);

void      SD_Card_SPI_Speed_Set   (uint8_t   speed_set);

uint8_t   SPI_ReadWriteByte       (uint8_t   txdata);

uint8_t   SD_WaitReady            (void);

uint8_t   SD_SendCommand          (u8 cmd, u32 arg, u8 crc);
uint8_t   SD_SendCommand_NoDeasser(u8 cmd, u32 arg, u8 crc);

uint8_t   SD_Init                 (void);

uint8_t   SD_ReceiveData          (uint8_t  *p_data, 
                                   uint16_t  length, 
                                   uint8_t   release);

uint8_t   SD_GetCID               (uint8_t  *p_cid_data);
uint8_t   SD_GetCSD               (uint8_t  *p_csd_data);

float     SD_GetCapacity          (void);

uint8_t   SD_ReadSingleBlock      (uint32_t   sector,
                                   uint8_t   *p_buffer);

uint8_t   SD_WriteSingleBlock     (uint32_t   sector,
                                   uint8_t   *p_buffer);

uint8_t   SD_ReadSingleBlock      (uint32_t   sector,
                                   uint8_t   *p_buffer);

uint8_t   SD_WriteSingleBlock     (uint32_t   sector,
                                   uint8_t   *p_buffer);

uint8_t   SD_ReadMultiBlock       (uint32_t   sector,
                                   uint8_t   *p_buffer,
                                   uint8_t    number);

uint8_t   SD_WriteMultiBlock      (uint32_t   sector,
                                   uint8_t   *p_buffer,
                                   uint8_t    number);

uint8_t   SD_SectorClear          (uint32_t   sector);



FRESULT   SD_FATFS_Init           (DWORD     *total,
                                   DWORD     *free);

FRESULT   SD_FATFS_Creat_File     (TCHAR     *path);

FRESULT   SD_FATFS_Read_File      (TCHAR     *path,
                                   uint8_t   *p_buff,
                                   uint32_t   buff_len);

FRESULT   SD_FATFS_Write_File     (TCHAR     *path,
                                   void      *buff);

FRESULT   SD_Write_Data           (TCHAR     *path,
                                   void      *p_buff,
                                   uint32_t   buff_len,
                                   uint8_t    type);
#endif
