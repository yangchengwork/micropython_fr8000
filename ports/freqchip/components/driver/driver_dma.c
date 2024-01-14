/*
  ******************************************************************************
  * @file    driver_dma.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   DMA module driver.
  *          This file provides firmware functions to manage the 
  *          Direct Memory Access (DMA) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "driver_dma.h"

/*********************************************************************
 * @fn      dma_init
 *
 * @brief   Initialize the DMA according to the specified parameters
 *          in the dma_InitParameter_t 
 *
 * @param   hdma : pointer to a DMA_HandleTypeDef structure that contains
 *                 the configuration information for DMA module
 *          
 * @return  None.
 */
void dma_init(DMA_HandleTypeDef *hdma)
{
    /* FIFO_MODE_1 */
    DMA->Channels[hdma->Channel].CFG2.FIFO_MODE = 1;

    /* Clear Linked List Pointer Register */
    DMA->Channels[hdma->Channel].LLP.LOC = 0;
    DMA->Channels[hdma->Channel].LLP.LMS = 0;

    /* Interrupt Enable */
    DMA->Channels[hdma->Channel].CTL1.INT_EN = 1;

    /* Transfer Width */
    DMA->Channels[hdma->Channel].CTL1.SRC_TR_WIDTH = hdma->Init.Source_Width;
    DMA->Channels[hdma->Channel].CTL1.DST_TR_WIDTH = hdma->Init.Desination_Width;

    /* Address Increment */
    DMA->Channels[hdma->Channel].CTL1.SINC = hdma->Init.Source_Inc;
    DMA->Channels[hdma->Channel].CTL1.DINC = hdma->Init.Desination_Inc;

    /* DMA Data Flow */
    DMA->Channels[hdma->Channel].CTL1.TT_FC = hdma->Init.Data_Flow;

    /* Set Peripheral Request ID */
    if (hdma->Init.Data_Flow == DMA_M2P_DMAC) 
    {
        DMA->Channels[hdma->Channel].CFG2.DEST_PER = hdma->Init.Request_ID;
    }
    else if (hdma->Init.Data_Flow == DMA_P2M_DMAC) 
    {
        DMA->Channels[hdma->Channel].CFG2.SRC_PER = hdma->Init.Request_ID;
    }

    /* Hardware handshaking interface */
    DMA->Channels[hdma->Channel].CFG1.HS_SEL_SRC = 0;
    DMA->Channels[hdma->Channel].CFG1.HS_SEL_DST = 0;
	
    /* AHB dmac Enabled */
    DMA->Misc_Reg.DmaCfgReg.DMA_EN = 1;
}

/*********************************************************************
 * @fn      dma_start
 *
 * @brief   DMA transfer start. 
 *
 * @param   hdma : pointer to a DMA_HandleTypeDef structure that contains
 *                 the configuration information for DMA module
 *          SrcAddr:  source address
 *          DstAddr:  desination address
 *          Size:     transfer size (This parameter can be a 12-bit Size)
 *          BurstLen: Burst Length
 * @return  None.
 */
void dma_start(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DstAddr, uint32_t Size, dma_burst_len_t SrcBurstLen, dma_burst_len_t DestBurstLen)
{
    /* Set source address and desination address */
    DMA->Channels[hdma->Channel].SAR = SrcAddr;
    DMA->Channels[hdma->Channel].DAR = DstAddr;
    
    /* Set Transfer Size */
    DMA->Channels[hdma->Channel].CTL2.BLOCK_TS = Size;
    
    /* Burst Length */
    DMA->Channels[hdma->Channel].CTL1.DEST_MSIZE = DestBurstLen;
    DMA->Channels[hdma->Channel].CTL1.SRC_MSIZE  = SrcBurstLen;

    /* Enable the channel */
    DMA->Misc_Reg.ChEnReg |= (1 << hdma->Channel | (1 << (hdma->Channel + 8)));
}

/*********************************************************************
 * @fn      dma_start_IT
 *
 * @brief   DMA transfer start and enable interrupt
 *
 * @param   hdma : pointer to a DMA_HandleTypeDef structure that contains
 *                 the configuration information for DMA module
 *          SrcAddr:  source address
 *          DstAddr:  desination address
 *          Size:     transfer size (This parameter can be a 12-bit Size)
 *          BurstLen: Burst Length
 * @return  None.
 */
void dma_start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DstAddr, uint32_t Size, dma_burst_len_t BurstLen)
{
    /* Set source address and desination address */
    DMA->Channels[hdma->Channel].SAR = SrcAddr;
    DMA->Channels[hdma->Channel].DAR = DstAddr;
    
    /* Set Transfer Size */
    DMA->Channels[hdma->Channel].CTL2.BLOCK_TS = Size;
    
    /* Burst Length */
    DMA->Channels[hdma->Channel].CTL1.DEST_MSIZE = BurstLen;
    DMA->Channels[hdma->Channel].CTL1.SRC_MSIZE  = BurstLen;

    /* Clear Transfer complete status */
    dma_clear_tfr_Status(hdma->Channel);
    /* channel Transfer complete interrupt enable */
    dma_tfr_interrupt_enable(hdma->Channel);

    /* Enable the channel */
    DMA->Misc_Reg.ChEnReg |= (1 << hdma->Channel | (1 << (hdma->Channel + 8)));
}

/*********************************************************************
 * @fn      dma_linked_list_init
 *
 * @brief   Initialize the linked list parameters
 *
 * @param   link : The list structure that needs to be initialized
 *          param: Initialization parameter
 * @return  None
 */
void dma_linked_list_init(DMA_LLI_InitTypeDef *link, dma_LinkParameter_t *param)
{
    link->SrcAddr           = param->SrcAddr;
    link->DstAddr           = param->DstAddr;
    link->Next              = (DMA_LLI_InitTypeDef *)param->NextLink;

    link->CTL1.INT_EN       = 1;
    link->CTL1.SRC_TR_WIDTH = param->Source_Width;
    link->CTL1.DST_TR_WIDTH = param->Desination_Width;
    link->CTL1.SINC         = param->Source_Inc;
    link->CTL1.DINC         = param->Desination_Inc;
    link->CTL1.TT_FC        = param->Data_Flow;
    link->CTL1.DEST_MSIZE   = param->Burst_Len;
    link->CTL1.SRC_MSIZE    = param->Burst_Len;
    link->CTL1.SRC_GATHER_EN  = param->gather_enable;
    link->CTL1.DST_SCATTER_EN = param->scatter_enable;
    link->CTL2.BLOCK_TS     = param->Size;

    /* Block chaining using Linked List is enabled on the Source side */
    /* Block chaining using Linked List is enabled on the Destination side */
    link->CTL1.LLP_DST_EN = 1;
    link->CTL1.LLP_SRC_EN = 1;
    
    /* AHB dmac Enabled */
    DMA->Misc_Reg.DmaCfgReg.DMA_EN = 1;
}

/*********************************************************************
 * @fn      dma_linked_list_start. 
 *
 * @brief   DMA linked list transfer start. 
 *
 * @param   link    : The first address of the linked list
 *          param   : Initialization parameter
 *          Channel : This parameter can be a value of @ref dma_channel_select_t 
 *
 * @return  None
 */
void dma_linked_list_start(DMA_LLI_InitTypeDef *link, dma_LinkParameter_t *param, uint32_t Channel)
{
    /* Set Peripheral Request ID */
    if (link->CTL1.TT_FC == DMA_M2P_DMAC) 
    {
        DMA->Channels[Channel].CFG2.DEST_PER = param->Request_ID;
    }
    else if (link->CTL1.TT_FC == DMA_P2M_DMAC) 
    {
        DMA->Channels[Channel].CFG2.SRC_PER = param->Request_ID;
    }

    /* Hardware handshaking interface */
    DMA->Channels[Channel].CFG1.HS_SEL_SRC = 0;
    DMA->Channels[Channel].CFG1.HS_SEL_DST = 0;

    /* Block chaining using Linked List is enabled on the Source side */
    /* Block chaining using Linked List is enabled on the Destination side */
    DMA->Channels[Channel].CTL1.LLP_DST_EN = link->CTL1.LLP_DST_EN;
    DMA->Channels[Channel].CTL1.LLP_SRC_EN = link->CTL1.LLP_SRC_EN;

    DMA->Channels[Channel].LLP.LOC = ((uint32_t)link) >> 2;

    DMA->Misc_Reg.ChEnReg |= (1 << Channel | (1 << (Channel + 8)));
}

/*********************************************************************
 * @fn      dma_linked_list_start_IT 
 *
 * @brief   DMA linked list transfer start and enable interrupt
 *
 * @param   link    : The first address of the linked list
 *          param   : Initialization parameter
 *          Channel : This parameter can be a value of @ref dma_channel_select_t 
 *
 * @return  None
 */
void dma_linked_list_start_IT(DMA_LLI_InitTypeDef *link, dma_LinkParameter_t *param, uint32_t Channel)
{
    /* Set Peripheral Request ID */
    if (link->CTL1.TT_FC == DMA_M2P_DMAC) 
    {
        DMA->Channels[Channel].CFG2.DEST_PER = param->Request_ID;
    }
    else if (link->CTL1.TT_FC == DMA_P2M_DMAC) 
    {
        DMA->Channels[Channel].CFG2.SRC_PER = param->Request_ID;
    }

    /* Hardware handshaking interface */
    DMA->Channels[Channel].CFG1.HS_SEL_SRC = 0;
    DMA->Channels[Channel].CFG1.HS_SEL_DST = 0;

    DMA->Channels[Channel].CTL1.LLP_DST_EN = link->CTL1.LLP_DST_EN;
    DMA->Channels[Channel].CTL1.LLP_SRC_EN = link->CTL1.LLP_SRC_EN;

    DMA->Channels[Channel].LLP.LOC = ((uint32_t)link) >> 2;

    /* Clear Transfer complete status */
    dma_clear_tfr_Status(Channel);
    /* channel Transfer complete interrupt enable */
    dma_tfr_interrupt_enable(Channel);

    DMA->Misc_Reg.ChEnReg |= (1 << Channel | (1 << (Channel + 8)));
}

/*********************************************************************
 * @fn      dma_tfr_interrupt_enable
 *
 * @brief   channel transfer complete interrupt enable
 *
 * @param   Channel : This parameter can be a value of @ref dma_channel_select_t 
 *
 * @return  None
 */
void dma_tfr_interrupt_enable(uint32_t Channel)
{
    DMA->Int_Reg.MaskTfr = (1 << Channel) | (1 << (Channel + 8));
}

/*********************************************************************
 * @fn      dma_tfr_interrupt_disable
 *
 * @brief   channel transfer complete interrupt disable
 *
 * @param   Channel : This parameter can be a value of @ref dma_channel_select_t 
 *
 * @return  None
 */
void dma_tfr_interrupt_disable(uint32_t Channel)
{
    DMA->Int_Reg.MaskTfr = (1 << (Channel + 8));
}

/*********************************************************************
 * @fn      dma_get_tfr_Status
 *
 * @brief   Get channel transfer complete status
 *
 * @param   Channel : This parameter can be a value of @ref dma_channel_select_t 
 *
 * @return  true:  channel Transfer complete
 *          false: Not
 */
bool dma_get_tfr_Status(uint32_t Channel)
{
    /* Check channel Transfer complete */
    if (DMA->Int_Reg.RawTfr & (1 << Channel)) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

/*********************************************************************
 * @fn      dma_clear_tfr_Status
 *
 * @brief   clear channel transfer complete status
 *
 * @param   Channel : This parameter can be a value of @ref dma_channel_select_t 
 *
 * @return  None
 */
void dma_clear_tfr_Status(uint32_t Channel)
{
    /* Clear channel Transfer complete Status */
    DMA->Int_Reg.ClearTfr = 1 << Channel;
}


