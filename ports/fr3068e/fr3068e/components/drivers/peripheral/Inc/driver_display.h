/*
  ******************************************************************************
  * @file    driver_display.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of display controller HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_DISPLAY_H__
#define __DRIVER_DISPLAY_H__

#include "fr30xx.h"

/** @addtogroup Display_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* display controller config */
typedef struct
{
    uint32_t DC_POLARITY : 1;
    uint32_t CS_POLARITY : 1;
    uint32_t MODE        : 1;
    uint32_t PARA_WIDTH  : 1;
    uint32_t rsv_0       : 1;
    uint32_t INTF_MODE   : 2;
    uint32_t rsv_1       : 1;
    uint32_t PARA_CLKEN  : 1; 
    uint32_t SPI_CLKEN   : 1;  
    uint32_t RGB_CLKEN   : 1;   
    uint32_t PARA_RST    : 1; 
    uint32_t SPI_RST     : 1;  
    uint32_t RGB_RST     : 1;     
    uint32_t rsv_2       : 18;    
}REG_INTERFACE_CFG_t;

/* Write/Read clock Config */
typedef struct
{
    uint32_t WRITE_CLK_DIV : 3;
    uint32_t rsv_0         : 1;
    uint32_t READ_CLK_DIV  : 4;
    uint32_t WR_L_LEN      : 3;
    uint32_t rsv_1         : 1;
    uint32_t WR_H_LEN      : 3;
    uint32_t rsv_2         : 17;
}REG_WR_CLK_t;

/* Data transmission Configuration */
typedef struct 
{
    uint32_t DATA_TRANS_SEQ_0 : 2;
    uint32_t DATA_TRANS_SEQ_1 : 2;
    uint32_t DATA_TRANS_SEQ_2 : 2;
    uint32_t DATA_TRANS_SEQ_3 : 2;
    uint32_t rsv_1            :24;
}REG_DATA_CFG_t;

/* DMA Configuration */
typedef struct 
{
    uint32_t DMA_TX_LEVEL : 6;
    uint32_t DMA_ENABLE   : 1;
    uint32_t rsv_0        : 25;
}REG_DMA_t;

/* RGB Configuration */
typedef struct 
{
    uint32_t RGB_MODE_EN         :1;
    uint32_t RGB_MODE            :2;
    uint32_t DCLKPOL             :1;
    uint32_t DEPOL               :1;
    uint32_t HDPOL               :1;
    uint32_t VDPOL               :1;
    uint32_t RGB_FORMAT_IN       :1; 
    uint32_t RGB_FORAMAT_OUT     :2;
    uint32_t PIXEL_CLK_DIV       :4;
    uint32_t rsv_0               :18;
}REG_RGB_CFG_t;

/* RGB Porch period */
typedef struct 
{
    uint32_t VFP     :8;
    uint32_t VBP     :8;
    uint32_t HFP     :8;
    uint32_t HBP     :8;
}REG_PORCH_PERIOD_t;

/* RGB Display Period */
typedef struct 
{
    uint32_t VRES     :12;
    uint32_t rsv_0    :4;
    uint32_t HRES     :12;
    uint32_t rsv_1    :4;
}REG_DISPLAY_PERIOD_t;

/* RGB SYNC Pulse */
typedef struct 
{
    uint32_t VSPW    :6;
    uint32_t rsv_1   :2;
    uint32_t HSPW    :6;
    uint32_t rsv_0   :18;
}REG_SYNC_PULSE_t;

/* SPI Control0 */
typedef struct 
{
    uint32_t rsv_0     :4;    
    uint32_t FRF       :2;
    uint32_t SCPH      :1;
    uint32_t SCPOL     :1;    
    uint32_t rsv_1     :4;
    uint32_t CFS       :4;
    uint32_t DFS       :5;
    uint32_t SPI_FRF   :2;
    uint32_t rsv_2     :1;
    uint32_t SS_TGL_EN :1;
    uint32_t rsv_3     :7;
}REG_SPI_CTRL0_t;

/* SPI Control1 */
typedef struct 
{
    uint32_t TRANS_TYPE         :2;
    uint32_t SPI_ADDR           :4; 
    uint32_t rsv_0              :2;
    uint32_t SPI_INST           :2;
    uint32_t rsv_1              :10;
    uint32_t TX_ENDIAN_CFG      :2;
    uint32_t rsv_2              :2;
    uint32_t LCD_LANE           :1;
    uint32_t LCD_LANE_CMD       :1;
    uint32_t LCD_LANEX2         :1;
    uint32_t LCD_LANEX2_SWAP    :1;
    uint32_t rsv_3              :4;
}REG_SPI_CTRL1_t;

/* -------------------------------------------*/
/*               display  Register            */
/* -------------------------------------------*/
typedef struct 
{
    volatile REG_INTERFACE_CFG_t        INTF_CFG;           /* offset 0x00 */
    volatile uint32_t                   CSX;                /* offset 0x04 */
    volatile REG_WR_CLK_t               CRM;                /* offset 0x08 */    
    volatile uint32_t                   BUS_STATUS;         /* offset 0x0C */ 
    volatile uint32_t                   CFG;                /* offset 0x10 */ 
    volatile uint32_t                   DATA_WR_LEN;        /* offset 0x14 */  
    volatile REG_DATA_CFG_t             DATA_CFG;           /* offset 0x18 */   
    volatile uint32_t                   TX_FIFO;            /* offset 0x1C */  
    volatile uint32_t                   RD_REQ;             /* offset 0x20 */ 
    volatile uint32_t                   DAT_RD;             /* offset 0x24 */ 
    volatile uint32_t                   TXFF_AEMP_LV;       /* offset 0x28 */    
    volatile uint32_t                   TXFF_CLR;           /* offset 0x2C */
    volatile uint32_t                   INT_CONTROL;        /* offset 0x30 */  
    volatile uint32_t                   INT_STATUS;         /* offset 0x34 */     
    volatile REG_DMA_t                  DMA;                /* offset 0x38 */  
    volatile uint32_t                   rsv0[3];
    volatile REG_RGB_CFG_t              RGB_CFG;            /* offset 0x48 */ 
    volatile REG_PORCH_PERIOD_t         PORCH_PERIOD;       /* offset 0x4C */ 
    volatile REG_DISPLAY_PERIOD_t       DISPLAY_PERIOD;     /* offset 0x50 */ 
    volatile REG_SYNC_PULSE_t           SYNC_PULSE;         /* offset 0x54 */ 
    volatile uint32_t                   rsv1[2];
    volatile REG_SPI_CTRL0_t            SPI_CTRL0;          /* offset 0x60 */
    volatile uint32_t                   SPI_EN;             /* offset 0x64 */  
    volatile uint32_t                   SPI_SER;            /* offset 0x68 */
    volatile uint32_t                   SPI_BAUDR;          /* offset 0x6C */
    volatile REG_SPI_CTRL1_t            SPI_CTRL1;          /* offset 0x70 */  
}struct_display_t;

#define DISPLAY        ((struct_display_t *)DISPLAY_BASE)

/* ################################ Register Section END ################################ */
/**
  * @}
  */



/** @addtogroup Display_Initialization_Config_Section
  * @{            
  */
/* ################################ Initialization Config Section Start ################################ */

/** @defgroup DISPLAY_FIFO
  * @{
  */

#define DISPLAY_FIFO_DEPTH      (64)

/**
  * @}
  */

/* Display Interface select */
typedef enum
{
    DISPLAY_INTERFACE_PARALLEL,
    DISPLAY_INTERFACE_RGB,
    DISPLAY_INTERFACE_SPI,    
}enum_DISPLAY_Interface_Select;

/* -----------------------------------------------------*/
/*       Parallel interface Initialization Config       */
/* -----------------------------------------------------*/

/* mode select */
typedef enum
{
    MODE_8080,
    MODE_6800,
}enum_Parallel_MODE_t;

/* data bus width */
typedef enum
{
    DATA_BUS_8_BIT,
    DATA_BUS_16_BIT,
}enum_DATA_BUS_t;

/* read clock division */
typedef enum
{
    RDCLK_DIV_1,
    RDCLK_DIV_2,
    RDCLK_DIV_3,
    RDCLK_DIV_4,
    RDCLK_DIV_6,
    RDCLK_DIV_8,
    RDCLK_DIV_16,
    RDCLK_DIV_32,
    RDCLK_DIV_64,
}enum_RDCLK_DIV_t;

/* write clock division */
typedef enum
{
    WDCLK_DIV_1,
    WDCLK_DIV_2,
    WDCLK_DIV_3,
    WDCLK_DIV_4,
    WDCLK_DIV_6,
    WDCLK_DIV_8,
}enum_WDCLK_DIV_t;

/* interrupt index */
typedef enum
{
    INT_TXFIFO_FULL     = 0x00000001,
    INT_TXFIFO_EMPTY    = 0x00000002, 
    INT_TXFIFO_LEVEMPT  = 0x00000004,
}enum_INT_t;

/* -----------------------------------------------------*/
/*             RGB Initialization Config                */
/* -----------------------------------------------------*/

/* RGB FORMAT */
typedef enum
{
    RGB888_OUT,
    RGB666_OUT,
    RGB565_OUT,
}enum_RGB_OUT_FORMAT_SELECT_t;

/* RGB FORMAT */
typedef enum
{
    RGB888_IN,
    RGB565_IN,
}enum_RGB_IN_FORMAT_SELECT_t;

/* -----------------------------------------------------*/
/*             SPI Initialization Config                */
/* -----------------------------------------------------*/

/* SPI Frame Size Select */
/* SPI Work Mode Select  */
/* SPI x2/x4/x8 Select   */
/* SPI Instruct Length   */
/* SPI Address Length    */
/* SPI Transfer Type     */
#define enum_SPI_FrameFormat_Select_t   enum_FrameSize_t
#define enum_SPI_Work_Mode_Select_t     enum_Work_Mode_t
#define enum_SPI_Wire_X2X4X8_t          enum_Wire_X2X4_t
#define enum_SPI_TransferType_t         enum_TransferType_t

/**
  * @brief  Display parallel interface Initialization Structure definition
  */
typedef struct 
{
    uint32_t ParallelMode;              /* This parameter can be a value of @ref enum_Parallel_MODE_t */

    uint32_t DataBusSelect;             /* This parameter can be a value of @ref enum_DATA_BUS_t */

    uint32_t ReadClock;                 /* This parameter can be a value of @ref enum_RDCLK_DIV_t */

    uint32_t WriteClock;                /* This parameter can be a value of @ref enum_WDCLK_DIV_t */
    
}struct_display_parallelInit_t;

/**
  * @brief  Display RGB Initialization Structure definition
  */
typedef struct 
{
    uint32_t PixelClock_Prescaler;      /* This parameter can becan be a 5bit value */
    
    uint32_t RGB_OUT_FORMAT_SELECT;     /* This parameter can be a value of @ref enum_RGB_OUT_FORMAT_SELECT_t */  
    
    uint32_t RGB_IN_FORMAT_SELECT;      /* This parameter can be a value of @ref enum_RGB_IN_FORMAT_SELECT_t */   
        
    uint32_t HBP;                       /* This parameter can becan be a 8bit value */
    
    uint32_t HFP;                       /* This parameter can becan be a 8bit value */  

    uint32_t VBP;                       /* This parameter can becan be a 8bit value */
    
    uint32_t VFP;                       /* This parameter can becan be a 8bit value */ 

    uint32_t HRES;                      /* This parameter can becan be a 12bit value */ 
    
    uint32_t VRES;                      /* This parameter can becan be a 12bit value */ 
    
    uint32_t HSPW;                      /* This parameter can becan be a 6bit value */
    
    uint32_t VSPW;                      /* This parameter can becan be a 6bit value */    
    
}struct_display_RGBInit_t;

/*
 * @brief  Display SPI Initialization Structure definition
 */
typedef struct
{
    uint32_t  Work_Mode;                /* This parameter can be a value of @ref enum_SPI_Work_Mode_Select_t */

    uint32_t  Frame_Size;               /* This parameter can be a value of @ref enum_SPI_FrameFormat_Select_t */
    
    uint32_t  BaudRate_Prescaler;       /* This parameter can be a value 2 ~ 65534 */
    uint32_t  Wire_X2X4X8;              /*!< This parameter can be a value of @ref enum_SPI_Wire_X2X4X8_t */      
    
}struct_display_SPIInit_t;

/**
 * @brief  Display controller handle Structure definition
 */
typedef struct
{
    struct_display_t                  *DISPLAYx;                 /*!< display controller registers base address */
    
    uint32_t                           Interface_Select;         /*!< This parameter can be a value of @ref enum_DISPLAY_Interface_Select */    
    
    /* ---------------------------------------------------------------- */
    /* Set the following parameters when interface select Parallel mode */
    /* ---------------------------------------------------------------- */                                        
    struct_display_parallelInit_t      Parallel_Init;            /*!< PARALLEL communication parameters   */
    
    /* ----------------------------------------------------------- */
    /* Set the following parameters when interface select RGB mode */
    /* ----------------------------------------------------------- */                                        
    struct_display_RGBInit_t           RGB_Init;                 /*!< RGB communication parameters        */  

    /* ------------------------------------------------------------ */
    /* Set the following parameters when interface select SPI mode  */
    /* ------------------------------------------------------------ */    
    struct_display_SPIInit_t           SPI_Init;                 /*!< SPI communication parameters         */
    
}DISPLAY_HandTypeDef;

/* ################################ Initialization_Config Section END ################################ */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Display tx fifo level */                                                              /* fu8_level: 0 ~ 31 */
#define __DISPLAY_TX_FIFO_ALMOST_EMPTY_LEVEL(__DISPLAYx__, __LEVEL__)                    (__DISPLAYx__->TXFF_AEMP_LV = __LEVEL__)

/* Display tx fifo reset */
/* Display tx fifo release */
#define __DISPLAY_TX_FIFO_RESET(__DISPLAYx__)                                            (__DISPLAYx__->TXFF_CLR = 0x07)
#define __DISPLAY_TX_FIFO_RELEASE(__DISPLAYx__)                                          (__DISPLAYx__->TXFF_CLR = 0x00)

/* Display get interrupt status */
#define __DISPLAY_INT_STATUS(__DISPLAYx__)                                               (__DISPLAYx__->INT_STATUS)                                                                                     
/* Display interrupt Status enable/disable */                                           
#define __DISPLAY_INT_STATUS_ENABLE(__DISPLAYx__, __STATUS__)                            (__DISPLAYx__->INT_CONTROL |=  (__STATUS__))                        
#define __DISPLAY_INT_STATUS_DISABLE(__DISPLAYx__, __STATUS__)                           (__DISPLAYx__->INT_CONTROL &= ~(__STATUS__))  
#define __DISPLAY_INT_STATUS_ALL_ENABLE(__DISPLAYx__, __STATUS__)                        (__DISPLAYx__->INT_CONTROL = 0x0F)                                                                                         
#define __DISPLAY_INT_STATUS_ALL_DISABLE(__DISPLAYx__, __STATUS__)                       (__DISPLAYx__->INT_CONTROL = 0x00)   
                                                                                       
/* Display bus status */      
#define __DISPLAY_IS_BUS_BUSY(__DISPLAYx__)                                              (__DISPLAYx__->BUS_STATUS)
                                                                    
/* Display dma requset level */                                                          /* fu8_level: 0 ~ 31 */
#define __DISPLAY_DMA_TX_LEVEL(__DISPLAYx__, __LEVEL__)                                  (__DISPLAYx__->DMA.DMA_TX_LEVEL = __LEVEL__)

/* Display dma ENABLE and DISABLE */
#define __DISPLAY_DMA_ENABLE(__DISPLAYx__)                                               (__DISPLAYx__->DMA.DMA_ENABLE = 1)   
#define __DISPLAY_DMA_DISABLE(__DISPLAYx__)                                              (__DISPLAYx__->DMA.DMA_ENABLE = 0) 

/* Display Parallel writer CMD */
#define __DISPLAY_PARALLEL_WR_CMD(__DISPLAYx__ , __CMD__)                                (__DISPLAYx__->CFG = __CMD__)                                                                            
#define __DISPLAY_PARALLEL_WR_PARAM(__DISPLAYx__ , __DATA__)                             (__DISPLAYx__->CFG = 0x10000 | __DATA__)

/* Display Parallel RD REQ */      
#define __DISPLAY_PARALLEL_RD_REQ(__DISPLAYx__)                                          (__DISPLAYx__->RD_REQ = 0x1)

/* Display Parallel cs set */
/* Display Parallel cs release */
#define __DISPLAY_PARALLEL_CS_SET(__DISPLAYx__)                                          (__DISPLAYx__->CSX = 0)
#define __DISPLAY_PARALLEL_CS_RELEASE(__DISPLAYx__)                                      (__DISPLAYx__->CSX = 1)

/* Display Parallel set bus 8bit */
/* Display Parallel set bus 16bit */
#define __DISPLAY_PARALLEL_SET_BUS_8BIT(__DISPLAYx__)                                    (__DISPLAYx__->INTF_CFG.PARA_WIDTH = DATA_BUS_8_BIT)  
#define __DISPLAY_PARALLEL_SET_BUS_16BIT(__DISPLAYx__)                                   (__DISPLAYx__->INTF_CFG.PARA_WIDTH = DATA_BUS_16_BIT)                     

/* Display Parallel wrclk div */
/* Display Parallel rdclk div */
#define __DISPLAY_PARALLEL_WRCLK_DIV(__DISPLAYx__, __WDCLK_DIV__)                        (__DISPLAYx__->CRM.WRITE_CLK_DIV = __WDCLK_DIV__)
#define __DISPLAY_PARALLEL_RDCLK_DIV(__DISPLAYx__, __RDCLK_DIV__)                        (__DISPLAYx__->CRM.READ_CLK_DIV  = __RDCLK_DIV__)

/* Display Parallel wrclk HighLength */
/* Display Parallel wrclk LowLength  */
#define __DISPLAY_PARALLEL_WRCLK_HIGHLENGTH(__DISPLAYx__, __LENGTH__)                    (__DISPLAYx__->CRM.WR_H_LEN = __LENGTH__)         
#define __DISPLAY_PARALLEL_WRCLK_LOWLENGTH(__DISPLAYx__, __LENGTH__)                     (__DISPLAYx__->CRM.WR_L_LEN = __LENGTH__)  

/* Display Parallel CS Polarity */                                                       /* fb_Polarity: 1: high active */
/* Display Parallel DC Polarity */                                                       /*              0: low  active */
#define __DISPLAY_PARALLEL_CS_POLARITY(__DISPLAYx__, __POLARITY__)                       (__DISPLAYx__->INTF_CFG.CS_POLARITY = __POLARITY__)  
#define __DISPLAY_PARALLEL_DC_POLARITY(__DISPLAYx__, __FB_POLARITY__)                    (__DISPLAYx__->INTF_CFG.DC_POLARITY = __POLARITY__)
                                                                                         
/* Display Parallel Set WR LEN */ 
#define __DISPLAY_PARALLEL_SET_WR_LEN(__DISPLAYx__, __LEVEL__)                           (__DISPLAYx__->DATA_WR_LEN = __LEVEL__)    

/* Display RGB Pixel Clk polarity */ 
#define __DISPLAY_RGB_SET_PIXEL_CLK_POLARITY_HIGH(__DISPLAYx__)                          (__DISPLAYx__->RGB_CFG.DCLKPOL = 1)
#define __DISPLAY_RGB_SET_PIXEL_CLK_POLARITY_LOW(__DISPLAYx__)                           (__DISPLAYx__->RGB_CFG.DCLKPOL = 0)

/* Display RGB VSYNC polarity */ 
#define __DISPLAY_RGB_SET_VSYNC_POLARITY_HIGH(__DISPLAYx__)                              (__DISPLAYx__->RGB_CFG.VDPOL = 1)
#define __DISPLAY_RGB_SET_VSYNC_POLARITY_LOW(__DISPLAYx__)                               (__DISPLAYx__->RGB_CFG.VDPOL = 0)  
#define __DISPLAY_RGB_SET_HSYNC_POLARITY_HIGH(__DISPLAYx__)                              (__DISPLAYx__->RGB_CFG.HDPOL = 1)
#define __DISPLAY_RGB_SET_HSYNC_POLARITY_LOW(__DISPLAYx__)                               (__DISPLAYx__->RGB_CFG.HDPOL = 0)                                                                                              
#define __DISPLAY_RGB_SET_DE_POLARITY_HIGH(__DISPLAYx__)                                 (__DISPLAYx__->RGB_CFG.DEPOL = 0)
#define __DISPLAY_RGB_SET_DE_POLARITY_LOW(__DISPLAYx__)                                  (__DISPLAYx__->RGB_CFG.DEPOL = 1) 

/* Display RGB Enable and Disable */                                                                                             
#define __DISPLAY_RGB_ENABLE(__DISPLAYx__)                                               (__DISPLAYx__->RGB_CFG.RGB_MODE_EN = 1)  
#define __DISPLAY_RGB_DISABLE(__DISPLAYx__)                                              (__DISPLAYx__->RGB_CFG.RGB_MODE_EN = 0)   

/* Display RGB Pixel Clk Div */                                                                                             
#define __DISPLAY_RGB_SET_PIXEL_CLK_DIV(__DISPLAYx__, __CLKDIV__)                        (__DISPLAYx__->RGB_CFG.PIXEL_CLK_DIV = __CLKDIV__)      

/* Display SPI Enable/Disable */
#define __DISPLAY_SPI_ENABLE(__DISPLAYx__)                                               (__DISPLAYx__->SPI_EN = 1)
#define __DISPLAY_SPI_DISABLE(__DISPLAYx__)                                              (__DISPLAYx__->SPI_EN = 0) 
                                                                                             
/* Display SPI Master Standard Dual Quad Octal mode */
#define __DISPLAY_SPI_SET_MODE_X1(__DISPLAYx__)                                          (__DISPLAYx__->SPI_CTRL0.SPI_FRF = 0)
#define __DISPLAY_SPI_SET_MODE_X2(__DISPLAYx__)                                          (__DISPLAYx__->SPI_CTRL0.SPI_FRF = 1)
#define __DISPLAY_SPI_SET_MODE_X4(__DISPLAYx__)                                          (__DISPLAYx__->SPI_CTRL0.SPI_FRF = 2)
#define __DISPLAY_SPI_SET_MODE_X8(__DISPLAYx__)                                          (__DISPLAYx__->SPI_CTRL0.SPI_FRF = 3)
#define __DISPLAY_SPI_SET_MODE_X2X4X8(__DISPLAYx__, __WIDTH__)                           (__DISPLAYx__->SPI_CTRL0.SPI_FRF = __WIDTH__)    

/* Display SPI Data Frame Size */
#define __DISPLAY_SPI_DATA_FRAME_SIZE(__DISPLAYx__, __SIZE__)                            (__DISPLAYx__->SPI_CTRL0.DFS = __SIZE__)
#define __DISPLAY_SPI_DATA_FRAME_SIZE_GET(__DISPLAYx__)                                  (__DISPLAYx__->SPI_CTRL0.DFS)
                                                                                         
/* Display SPI bit8 custom send Enable */                                                            
#define __DISPLAY_SPI_CUSTOM_DATA_ENABLE(__DISPLAYx__)                                   (__DISPLAYx__->SPI_CTRL1.LCD_LANE = 1)
#define __DISPLAY_SPI_CUSTOM_DATA_DISABLE(__DISPLAYx__)                                  (__DISPLAYx__->SPI_CTRL1.LCD_LANE = 0)  
                                                                                         
/* Display SPI bit8 custom send LANE x2 or x1 Enable */                                              
#define __DISPLAY_SPI_CUSTOM_LANE_X1(__DISPLAYx__)                                       (__DISPLAYx__->SPI_CTRL1.LCD_LANEX2 = 0)
#define __DISPLAY_SPI_CUSTOM_LANE_X2(__DISPLAYx__)                                       (__DISPLAYx__->SPI_CTRL1.LCD_LANEX2 = 1)  

/* Display SPI bit8 custom select */
#define __DISPLAY_SPI_DATA_LANE_DATA(__DISPLAYx__)                                       (__DISPLAYx__->SPI_CTRL1.LCD_LANE_CMD = 1)
#define __DISPLAY_SPI_DATA_LANE_COMMAND(__DISPLAYx__)                                    (__DISPLAYx__->SPI_CTRL1.LCD_LANE_CMD = 0)   
                                                                                         
/* Exported functions ---------------------------------------------------------------*/

/* display_init */
void display_init(DISPLAY_HandTypeDef *hdisplay);

/* display_Parallel_write_cmd */
/* display_Parallel_write_param */
/* display_Parallel_write_data */
void display_Parallel_write_cmd(DISPLAY_HandTypeDef *hdisplay, uint8_t fp8_CMD);
void display_Parallel_write_param(DISPLAY_HandTypeDef *hdisplay, uint16_t fu16_Data);
void display_Parallel_write_data(DISPLAY_HandTypeDef *hdisplay, uint32_t *fp32_WriteBuffer, uint32_t fu32_WriteNum);

/* display_Parallel_read_data_8bit */
/* display_Parallel_read_data_16bit */
void display_Parallel_read_data_8bit(DISPLAY_HandTypeDef *hdisplay, uint8_t fu8_Param, uint8_t *fp8_ReadBuffer, uint32_t fu32_ReadNum);
void display_Parallel_read_data_16bit(DISPLAY_HandTypeDef *hdisplay, uint8_t fu8_Param, uint16_t *fp16_ReadBuffer, uint32_t fu32_ReadNum);

/* display_rgb_write_data */
void display_rgb_write_data(DISPLAY_HandTypeDef *hdisplay, void *fp32_WriteBuffer, uint32_t fu32_WriteNum);

/* display_spi_transmit_x1 */
/* display_spi_transmit_x2x4x8 */
/* display_spi_transmit_X2X4X8_DMA */
void display_spi_transmit_x1(DISPLAY_HandTypeDef *hdisplay, void *fp_Data, uint32_t fu32_Size);
void display_spi_transmit_x2x4x8(DISPLAY_HandTypeDef *hdisplay, void *fp_Data, uint32_t fu32_Size);
void display_spi_transmit_X2X4X8_DMA(DISPLAY_HandTypeDef *hdisplay);

#endif
