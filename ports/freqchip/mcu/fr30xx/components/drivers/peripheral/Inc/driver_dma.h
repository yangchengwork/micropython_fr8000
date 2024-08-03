/*
  ******************************************************************************
  * @file    driver_dma.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of DMA HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_DMA_H__
#define __DRIVER_DMA_H__

#include "fr30xx.h"

#define DMA_CHANNELS_MAX     (8)


/** @addtogroup DMA_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Linked List Pointer Register for Channel */
typedef struct 
{
    uint32_t LMS : 2;    // Starting Address In Memory.
    uint32_t LOC : 30;   // List Master Select.
}REG_LLP_t;

/* Control Register for Channel */
typedef struct
{
    uint32_t INT_EN         : 1;    // Interrupt Enable.
    uint32_t DST_TR_WIDTH   : 3;    // Destination Transfer Width.
    uint32_t SRC_TR_WIDTH   : 3;    // Source Transfer Width.
    uint32_t DINC           : 2;    // Destination Address Increment.
    uint32_t SINC           : 2;    // Source Address Increment.
    uint32_t DEST_MSIZE     : 3;    // Destination Burst Transaction Length.
    uint32_t SRC_MSIZE      : 3;    // Source Burst Transaction Length.
    uint32_t SRC_GATHER_EN  : 1;    // Source gather enable.
    uint32_t DST_SCATTER_EN : 1;    // Destination scatter enable.
    uint32_t rsv_0          : 1;    // 
    uint32_t TT_FC          : 3;    // Transfer Type and Flow Control.
    uint32_t DMS            : 2;    // Destination Master Select.
    uint32_t SMS            : 2;    // Source Master Select.
    uint32_t LLP_DST_EN     : 1;    // Block chaining is enabled on the destination
    uint32_t LLP_SRC_EN     : 1;    // Block chaining is enabled on the source
    uint32_t rsv_1          : 3;    // 
}REG_CTL1_t;

/* Control Register for Channel */
typedef struct
{
    uint32_t BLOCK_TS : 24;    // Block Transfer Size.
    uint32_t rsv_0    : 7;
    uint32_t DONE     : 1;     // Done bit.
}REG_CTL2_t;

/* Configuration Register for Channel */
typedef struct
{
    uint32_t rsv_0      : 5;
    uint32_t CH_PRIOR   : 3;    // Channel Priority.
    uint32_t CH_SUSP    : 1;    // Channel Suspend.
    uint32_t FIFO_EMPTY : 1;    // Channel FIFO status.
    uint32_t HS_SEL_DST : 1;    // Destination Software or Hardware Handshaking Select.
    uint32_t HS_SEL_SRC : 1;    // Source Software or Hardware Handshaking Select.
    uint32_t LOCK_CH_L  : 2;
    uint32_t LOCK_B_L   : 2;
    uint32_t LOCK_CH    : 1;
    uint32_t LOCK_B     : 1;
    uint32_t DST_HS_POL : 1;    // Destination Handshaking Interface Polarity.
    uint32_t SRC_HS_POL : 1;    // Source Handshaking Interface Polarity.
    uint32_t MAX_ABRST  : 10;
    uint32_t RELOAD_SRC : 1;    // Automatic Source Reload.
    uint32_t RELOAD_DST : 1;
}REG_CFG1_t;

/* Configuration Register for Channel */
typedef struct
{
    uint32_t FCMODE    : 1;
    uint32_t FIFO_MODE : 1;
    uint32_t PROTCTL   : 3;
    uint32_t DS_UPD_EN : 1;
    uint32_t SS_UPD_EN : 1;
    uint32_t SRC_PER   : 4;
    uint32_t DEST_PER  : 4;
    uint32_t rsv_0     : 17;
}REG_CFG2_t;

/* Source Gath Register for Channel */
typedef struct
{
    uint32_t SGI : 20;
    uint32_t SGC : 12;
}REG_SGR_t;

/* Destination Scatter Register for Channel */
typedef struct
{
    uint32_t DSI : 20;
    uint32_t DSC : 12;
}REG_DSR_t;

/* -------------------------------------------*/
/*            DAM Channel Register            */
/* -------------------------------------------*/
typedef struct 
{
    volatile uint32_t    SAR;        // offset 0x00. Source Address for Channel
    volatile uint32_t    rsv_0;      // offset 0x04
    volatile uint32_t    DAR;        // offset 0x08. Destination Address Register for Channel
    volatile uint32_t    rsv_1;      // offset 0x0C
    volatile REG_LLP_t   LLP;        // offset 0x10. Linked List Pointer Register for Channel
    volatile uint32_t    rsv_2;      // offset 0x14
    volatile REG_CTL1_t  CTL1;       // offset 0x18. Control Register for Channel
    volatile REG_CTL2_t  CTL2;       // offset 0x1C. Control Register for Channel
    volatile uint32_t    SSTAT;      // offset 0x20. Source Status Register for Channel
    volatile uint32_t    rsv_3;      // offset 0x24
    volatile uint32_t    DSTAT;      // offset 0x28. Destination Status Register for Channel
    volatile uint32_t    rsv_4;      // offset 0x2C
    volatile uint32_t    SSTATAR;    // offset 0x30. Source Status Address Register for Channel
    volatile uint32_t    rsv_5;      // offset 0x34
    volatile uint32_t    DSTATAR;    // offset 0x38. Destination Status Address Register for Channel
    volatile uint32_t    rsv_6;      // offset 0x3C
    volatile REG_CFG1_t  CFG1;       // offset 0x40. Configuration Register for Channel
    volatile REG_CFG2_t  CFG2;       // offset 0x44. Configuration Register for Channel
    volatile REG_SGR_t   SGR;        // offset 0x48. Source Gather Register for Channel
    volatile uint32_t    rsv_7;      // offset 0x4C
    volatile REG_DSR_t   DSR;        // offset 0x50. Destination Scatter Register for Channel
    volatile uint32_t    rsv_8;      // offset 0x54
}dma_channel_t;


/* -------------------------------------------*/
/*            DAM Interrupt Register          */
/* -------------------------------------------*/
typedef struct  
{
    volatile uint32_t RawTfr;
    volatile uint32_t rsv_0;
    volatile uint32_t RawBlock;
    volatile uint32_t rsv_1;
    volatile uint32_t RawSrcTran;
    volatile uint32_t rsv_2;
    volatile uint32_t RawDstDran;
    volatile uint32_t rsv_3;
    volatile uint32_t RawErr;
    volatile uint32_t rsv_4;
    volatile uint32_t StatusTfr;
    volatile uint32_t rsv_5;
    volatile uint32_t StatusBlock;
    volatile uint32_t rsv_6;
    volatile uint32_t StatusSrcTran;
    volatile uint32_t rsv_7;
    volatile uint32_t StatusDstTran;
    volatile uint32_t rsv_8;
    volatile uint32_t StatusErr;
    volatile uint32_t rsv_9;
    volatile uint32_t MaskTfr;
    volatile uint32_t rsv_10;
    volatile uint32_t MaskBlock;
    volatile uint32_t rsv_11;
    volatile uint32_t MaskSrcTran;
    volatile uint32_t rsv_12;
    volatile uint32_t MaskDstTran;
    volatile uint32_t rsv_13;
    volatile uint32_t MaskErr;
    volatile uint32_t rsv_14;
    volatile uint32_t ClearTfr;
    volatile uint32_t rsv_15;
    volatile uint32_t ClearBlock;
    volatile uint32_t rsv_16;
    volatile uint32_t ClearSrcTran;
    volatile uint32_t rsv_17;
    volatile uint32_t ClearDstTran;
    volatile uint32_t rsv_18;
    volatile uint32_t ClearErr;
    volatile uint32_t rsv_19;
    volatile uint32_t StatusInt;
    volatile uint32_t rsv_20;
}dma_interrupt_t;


/* ------------------------------------------------*/
/*         DAM Software Handshake Register         */
/* ------------------------------------------------*/
typedef struct  
{
    volatile uint32_t ReqSrcReg;
    volatile uint32_t rsv_0;
    volatile uint32_t ReqDstReg;
    volatile uint32_t rsv_1;
    volatile uint32_t SglRqSrcReg;
    volatile uint32_t rsv_2;
    volatile uint32_t SglRqDstReg;
    volatile uint32_t rsv_3;
    volatile uint32_t LstSrcReg;
    volatile uint32_t rsv_4;
    volatile uint32_t LstDstReg;
    volatile uint32_t rsv_5;
}dma_software_handshake_t;


/* -------------------------------------------*/
/*         DAM Miscellaneous Register         */
/* -------------------------------------------*/
typedef struct
{
    volatile uint32_t DMA_EN : 1;
    volatile uint32_t rsv_0  : 31;
}REG_DmaCfg_t;

typedef struct  
{
    volatile REG_DmaCfg_t  DmaCfgReg;
    volatile uint32_t      rsv_0;
    volatile uint32_t      ChEnReg;
}dma_miscellaneous_t;


typedef struct 
{
    dma_channel_t              Channels[DMA_CHANNELS_MAX];
    dma_interrupt_t            Int_Reg;
    dma_software_handshake_t   Software_Handshake_Reg; 
    dma_miscellaneous_t        Misc_Reg;
}struct_DMA_t;

#define DMA0              ((struct_DMA_t *)DMAC0_BASE)
#define DMA1              ((struct_DMA_t *)DMAC1_BASE)
/* ################################ Register Section END ################################ */
/**
  * @}
  */



/** @addtogroup DMA_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization, Config Section Start ################################ */

typedef enum  
{
    DMA_Channel0,
    DMA_Channel1,
    DMA_Channel2,
    DMA_Channel3,
    DMA_Channel4,
    DMA_Channel5,
    DMA_Channel6,
    DMA_Channel7,
}dma_channel_select_t;

enum dma_data_flow_t 
{
    DMA_M2M_DMAC,       // Memory     to Memory     and Flow Controller is dmac
    DMA_M2P_DMAC,       // Memory     to Peripheral and Flow Controller is dmac
    DMA_P2M_DMAC,       // Peripheral to Memory     and Flow Controller is dmac
    DMA_P2P_DMAC,       // Peripheral to Peripheral and Flow Controller is dmac
    DMA_P2M_PER,        // Peripheral to Memory     and Flow Controller is Peripheral
    DMA_P2P_SRCPER,     // Peripheral to Peripheral and Flow Controller is Source Peripheral
    DMA_M2P_PER,        // Memory     to Peripheral and Flow Controller is Peripheral
    DMA_P2P_DSTPER,     // Peripheral to Peripheral and Flow Controller is Destination Peripheral
};

enum dma_addr_inc_t 
{
    DMA_ADDR_INC_INC,          // Increments the source/destination address
    DMA_ADDR_INC_DEC,          // Decrements the source/destination address
    DMA_ADDR_INC_NO_CHANGE,    // No change  the source/destination address
};

enum dma_transfer_width_t 
{
    DMA_TRANSFER_WIDTH_8,
    DMA_TRANSFER_WIDTH_16,
    DMA_TRANSFER_WIDTH_32,
};

typedef enum  
{
    DMA_BURST_LEN_1,
    DMA_BURST_LEN_4,
    DMA_BURST_LEN_8,
    DMA_BURST_LEN_16,
    DMA_BURST_LEN_32,
    DMA_BURST_LEN_64,
    DMA_BURST_LEN_128,
    DMA_BURST_LEN_256,
}dma_burst_len_t;

enum dma_ahb_master_t 
{
    DMA_AHB_MASTER_1,       /* access to 0x00000000~0x1FFFFFFF space */
    DMA_AHB_MASTER_2,       /* access to 0x20000000~           space */
    DMA_AHB_MASTER_3,       /* access to 0x20000000~           space */
    DMA_AHB_MASTER_4,       /* access to 0x20000000~           space */
};



/**
  * @brief  DMA Initialization Structure definition
  */
typedef struct 
{
    uint8_t Data_Flow;              /* This parameter can be a value of @ref dma_data_flow_t */

    uint8_t Request_ID;             /* This parameter can be a value of @ref dma_requeat_id_t */
    
    uint8_t Source_Master_Sel;      /* This parameter can be a value of @ref dma_ahb_master_t */
    
    uint8_t Desination_Master_Sel;  /* This parameter can be a value of @ref dma_ahb_master_t */

    uint8_t Source_Inc;             /* This parameter can be a value of @ref dma_addr_inc_t */

    uint8_t Desination_Inc;         /* This parameter can be a value of @ref dma_addr_inc_t */

    uint8_t Source_Width;           /* This parameter can be a value of @ref dma_transfer_width_t */

    uint8_t Desination_Width;       /* This parameter can be a value of @ref dma_transfer_width_t */

    uint8_t Source_Burst_Len;       /* This parameter can be a value of @ref dma_burst_len_t */

    uint8_t Desination_Burst_Len;   /* This parameter can be a value of @ref dma_burst_len_t */

}dma_InitParameter_t;

/**
  * @brief  DAM handle Structure definition
  */
typedef struct 
{
    struct_DMA_t           *DMAx;        /* DMA registers base address           */
    
    dma_channel_select_t    Channel;     /* DMA registers base address */
                                         /* This parameter can be a value of @ref dma_channel_select_t */

    dma_InitParameter_t     Init;        /* DMA initialization parameters */

}DMA_HandleTypeDef;

/**
  * @brief  DMA Link List Item Structure
  */
typedef struct DMA_NextLink
{
    uint32_t SrcAddr;               /* source address */

    uint32_t DstAddr;               /* desination address */

    struct DMA_NextLink *Next;      /* Next Link */

    REG_CTL1_t  CTL1;               /* Control Register for Channel */
    REG_CTL2_t  CTL2;               /* Control Register for Channel */

}DMA_LLI_InitTypeDef;

/**
  * @brief  DMA Initialization Structure definition
  */
typedef struct 
{
    uint32_t SrcAddr;               /* source address */
    
    uint32_t DstAddr;               /* desination address */
    
    uint32_t NextLink;              /* Next Link Address */
    
    uint32_t Data_Flow;             /* This parameter can be a value of @ref dma_data_flow_t */

    uint32_t Request_ID;            /* This parameter can be a value of @ref dma_requeat_id_t */
    
    uint8_t Source_Master_Sel;      /* This parameter can be a value of @ref dma_ahb_master_t */
    
    uint8_t Desination_Master_Sel;  /* This parameter can be a value of @ref dma_ahb_master_t */
    
    uint8_t Linked_Master_Sel;      /* This parameter can be a value of @ref dma_ahb_master_t */        

    uint32_t Source_Inc;            /* This parameter can be a value of @ref dma_addr_inc_t */

    uint32_t Desination_Inc;        /* This parameter can be a value of @ref dma_addr_inc_t */

    uint32_t Source_Width;          /* This parameter can be a value of @ref dma_transfer_width_t */

    uint32_t Desination_Width;      /* This parameter can be a value of @ref dma_transfer_width_t */

    uint32_t Source_Burst_Len;      /* This parameter can be a value of @ref dma_burst_len_t */
    
    uint32_t Desination_Burst_Len;  /* This parameter can be a value of @ref dma_burst_len_t */
    
    uint32_t Size;                  /* This parameter can be a 12-bit Size */

    uint8_t gather_enable;          /* Enable Source Gather or not */
    
    uint8_t scatter_enable;         /* Enable Destination Scatter or not */

}dma_LinkParameter_t;

/* ################################ Initialization, Config Section END ################################ */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* set DATA flow selection */
#define __DMA_DATA_FLOW_CONTROL_SET(__DMAC__, __CHANNEL__, SEL)         (__DMAC__->Channels[__CHANNEL__].CTL1.TT_FC = SEL)

/* APB Master selection configuration */
#define __DMA_SRC_MASTER_SET(__DMAC__, __CHANNEL__, SEL)    (__DMAC__->Channels[__CHANNEL__].CTL1.SMS = SEL)
#define __DMA_DES_MASTER_SET(__DMAC__, __CHANNEL__, SEL)    (__DMAC__->Channels[__CHANNEL__].CTL1.DMS = SEL)

/* Address increment configuration */
#define __DMA_SRC_ADDR_INC_SET(__DMAC__, __CHANNEL__, INC)  (__DMAC__->Channels[__CHANNEL__].CTL1.SINC = INC)
#define __DMA_DES_ADDR_INC_SET(__DMAC__, __CHANNEL__, INC)  (__DMAC__->Channels[__CHANNEL__].CTL1.DINC = INC)

/* Gather function enable,disable */
#define __DMA_GATHER_FUNC_ENABLE(__DMAC__, __CHANNEL__)                 (__DMAC__->Channels[__CHANNEL__].CTL1.SRC_GATHER_EN = 1)
#define __DMA_GATHER_FUNC_DISABLE(__DMAC__, __CHANNEL__)                (__DMAC__->Channels[__CHANNEL__].CTL1.SRC_GATHER_EN = 0)
/* Gather count, Gather interval */ 
#define __DMA_GATHER_COUNT(__DMAC__, __CHANNEL__, __COUNT__)            (__DMAC__->Channels[__CHANNEL__].SGR.SGC = __COUNT__)
#define __DMA_GATHER_INTERVAL(__DMAC__, __CHANNEL__, __INTERVAL__)      (__DMAC__->Channels[__CHANNEL__].SGR.SGI = __INTERVAL__)
    
/* Scatter function enable,disable */   
#define __DMA_SCATTER_FUNC_ENABLE(__DMAC__, __CHANNEL__)                (__DMAC__->Channels[__CHANNEL__].CTL1.DST_SCATTER_EN = 1)
#define __DMA_SCATTER_FUNC_DISABLE(__DMAC__, __CHANNEL__)               (__DMAC__->Channels[__CHANNEL__].CTL1.DST_SCATTER_EN = 0)
/* Scatter count, Gather interval */    
#define __DMA_SCATTER_COUNT(__DMAC__, __CHANNEL__, __COUNT__)           (__DMAC__->Channels[__CHANNEL__].DSR.DSC = __COUNT__)
#define __DMA_SCATTER_INTERVAL(__DMAC__, __CHANNEL__, __INTERVAL__)     (__DMAC__->Channels[__CHANNEL__].DSR.DSI = __INTERVAL__)

/* Exported functions --------------------------------------------------------*/

/* dma_init */
void dma_init(DMA_HandleTypeDef *hdma);

/* dma_start */
void dma_start(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DstAddr, uint32_t Size);

/* dma_start_interrupt */
void dma_start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DstAddr, uint32_t Size);

/* dma_linked_list_init */
void dma_linked_list_init(DMA_LLI_InitTypeDef *link, dma_LinkParameter_t *param);

/* dma_linked_list_start */
void dma_linked_list_start(DMA_HandleTypeDef *hdma, DMA_LLI_InitTypeDef *link, dma_LinkParameter_t *param);

/* dma_linked_list_start_IT */
void dma_linked_list_start_IT(DMA_HandleTypeDef *hdma, DMA_LLI_InitTypeDef *link, dma_LinkParameter_t *param);

/* dma_tfr_interrupt_enable */
void dma_tfr_interrupt_enable(DMA_HandleTypeDef *hdma);

/* dma_tfr_interrupt_disable */
void dma_tfr_interrupt_disable(DMA_HandleTypeDef *hdma);

/* dma_get_tfr_Status */
bool dma_get_tfr_Status(DMA_HandleTypeDef *hdma);

/* dma_clear_tfr_Status */
void dma_clear_tfr_Status(DMA_HandleTypeDef *hdma);

/* dma_error_interrupt_enable */
void dma_error_interrupt_enable(DMA_HandleTypeDef *hdma);

/* dma_error_interrupt_disable */
void dma_error_interrupt_disable(DMA_HandleTypeDef *hdma);

/* dma_get_error_Status */
bool dma_get_error_Status(DMA_HandleTypeDef *hdma);

/* dma_clear_error_Status */
void dma_clear_error_Status(DMA_HandleTypeDef *hdma);

#endif
