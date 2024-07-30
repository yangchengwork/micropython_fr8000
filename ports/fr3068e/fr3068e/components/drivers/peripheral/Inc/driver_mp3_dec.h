/*
  ******************************************************************************
  * @file    driver_mp3_dec.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of MP3 DECODER module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_MP3_DEC_H__
#define __DRIVER_MP3_DEC_H__

#include "fr30xx.h"

/** @addtogroup MP3_DEC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* MP3 DECODER CTRL REG  0x00*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t OPERA_EN               : 1;//this bit enables the mp3d 0->no effect 1->operation enable
        uint32_t OPERA_START            : 1;//this bit enables to start the mp3d 0->no effect 1->start mp3 decoder
        uint32_t ISR_EN                 : 1;//this bit enables the interrupt request 0->disable interrupt requeset 1->enable...
        uint32_t RESTART_DEC            : 1;//this bit enables to restart the mp3d
        uint32_t RESET_PCM_FIFO         : 1;//this bit enables to reset the pcm fifo
        uint32_t DAI_EN                 : 1;//this bit enables direct audio interface
        uint32_t ISSUE_NEW_FILE         : 1;//this bit enables to issue new mp3 file
        uint32_t RSV                    : 24;//
        uint32_t MP3D_SOFTRST           : 1;//this bit enable to reset the mp3d controller
    } Bits;
} REG_MP3D_CTRL_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t SOURCE_CMPLETION_ISR_EN            : 1;//this bit enables source complete interrupt 
        uint32_t PCM_BUFFER_UNDERRUN_ISR_EN         : 1;//this bit enables pcm buffer underrun interrupt
        uint32_t PCM_BUFFER_FULL_ISR_EN             : 1;//this bit enables pcm buffer full interrupt
        uint32_t MP3_FRAME_LOCKED_ISR_EN            : 1;//this bit enables mp3 frame locked interrupt
        uint32_t RSV                                : 28;//
    } Bits;
} REG_MP3D_INTMASK_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t SOURCE_CMPLETION_ISR            : 1;//this bit indicates the source decoding is complete 0->no effect 1->decode complete
        uint32_t PCM_BUFFER_UNDERRUN_ISR         : 1;//this bit indicates the pcm buffer is underrun 0->no effect 1->pcm buffer is underrun
        uint32_t PCM_BUFFER_FULL_ISR             : 1;//this bit indicates the pcm buffer is full
        uint32_t MP3_FRAME_LOCKED_ISR            : 1;//this bit indicates the mp3 frame is locked
        uint32_t RSV                             : 28;//
    } Bits;
} REG_MP3D_INTSTA_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t VOLUME            : 5;//volume control range from 0 to 31,0->no volume gain,31->maximum volume gain
        uint32_t RSV               : 27;//
    } Bits;
} REG_MP3D_VOL_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t EQ_60HZ_BAND            : 6;//equalizer coefficients,60Hz band
        uint32_t EQ_170HZ_BAND           : 6;//equalizer coefficients,170Hz band
        uint32_t EQ_310HZ_BAND           : 6;//equalizer coefficients,310Hz band
        uint32_t EQ_600HZ_BAND           : 6;//equalizer coefficients,600Hz band
        uint32_t EQ_1KHZ_BAND            : 6;//equalizer coefficients,1KHz band
        uint32_t RSV                     : 2;//
    } Bits;
} REG_MP3D_EQ0_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t EQ_3kHZ_BAND            : 6;//equalizer coefficients,3KHz band
        uint32_t EQ_6kHZ_BAND            : 6;//equalizer coefficients,6KHz band
        uint32_t EQ_12kHZ_BAND           : 6;//equalizer coefficients,12KHz band
        uint32_t EQ_14kHZ_BAND           : 6;//equalizer coefficients,14KHz band
        uint32_t EQ_16KHZ_BAND           : 6;//equalizer coefficients,16KHz band
        uint32_t RSV                     : 2;//
    } Bits;
} REG_MP3D_EQ1_t;


typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t MP3_STREAM_AUDIO_VER             : 2;//MP3 stream audio version 11172 or 13818
        uint32_t MP3_STREAM_ERROR_PROTECT         : 1;//mp3 stream error protection
        uint32_t MP3_STREAM_BIT_RATE              : 4;//mp3 stream bit rate
        uint32_t MP3_STREAM_SAMPLE_RATE           : 2;//mp3 stream sample rate
        uint32_t MP3_STREAM_AUDIO_MODE            : 2;//mp3 stream audio mode
        uint32_t MP3_STREAM_AUDIO_MODE_EXTEN      : 2;//mp3 stream audio mode extension
        uint32_t MP3_STREAM_COPYRIGHT             : 1;//mp3 stream copyright
        uint32_t MP3_STREAM_ORIGINAL              : 1;//mp3 stream original
        uint32_t MP3_STREAM_AUDIO_EMPHASIS        : 2;//mp3 stream emphasis
        uint32_t MP3_FRAME_LOCKED                : 1;//mp3 frame locked bit[16:0] valid only when frame locked
        uint32_t MP3_MAIN_DONE                    : 1;//mp3 huffman main done
        uint32_t MP3_MAIN_EXHAUST                 : 1;//mp3 huffman main exhaust
        uint32_t RSV                              : 12;//
    } Bits;
} REG_MP3D_INFO_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t MP3_DATA_SOURCE_SIZE            : 16;//mp3 data source buffer size
        uint32_t RSV                             : 16;//
    } Bits;
} REG_MP3D_SSIZE_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t MP3_PCM_BUFFER_SIZE             : 16;//mp3 pcm buffer size (32 bit align)
        uint32_t RSV                             : 16;//
    } Bits;
} REG_MP3D_PSIZE_t;

typedef struct 
{
    volatile REG_MP3D_CTRL_t         MP3D_CTRL;                 /* Offset 0x00 */
    volatile REG_MP3D_INTMASK_t      MP3D_INTMASK;              /* Offset 0x04 */
    volatile REG_MP3D_INTSTA_t       MP3D_INTSTA;               /* Offset 0x08 */
    volatile REG_MP3D_VOL_t          MP3D_VOL;                  /* Offset 0x0C */
    volatile REG_MP3D_EQ0_t          MP3D_EQ0;                  /* Offset 0x10*/
    volatile REG_MP3D_EQ1_t          MP3D_EQ1;                  /* Offset 0x14 */
    volatile REG_MP3D_INFO_t         MP3D_INFO;                 /* Offser 0x18*/
    volatile uint32_t                MP3D_SADDR;                /* Offser 0x1C*/
    volatile REG_MP3D_SSIZE_t        MP3D_SSIZE;                /* Offser 0x20*/
    volatile uint32_t                MP3D_PADDR;                /* Offser 0x24*/
    volatile REG_MP3D_PSIZE_t        MP3D_PSIZE;                /* Offser 0x28*/
    volatile uint32_t                RSV[3];                    /*Offser 0x2C-0x34*/
    volatile uint32_t                MP3D_FRMCNT;               /* Offser 0x38*/
}struct_MP3D_t;

typedef struct{
    volatile uint32_t audio_ver;
    volatile uint32_t error_protection;
    volatile uint32_t bit_rate;
    volatile uint32_t sample_rate;
    volatile uint32_t audio_mode;
    volatile uint32_t mode_extension;
    volatile uint32_t copyright;
    volatile uint32_t original;
    volatile uint32_t audio_emphasis;
    volatile uint32_t frame_locked;
    volatile uint32_t main_done;
    volatile uint32_t main_exhaust;
}struct_MP3D_stream_info_t;

typedef enum{
    SOURCE_COMPLETE_ISR = 0,
    PCM_BUF_UNDERRUN_ISR,
    PCM_BUF_FULL_ISR,
    MP3_FRAME_LOCKED_ISR,
}enum_mp3d_isr_t;

#define MP3D        ((struct_MP3D_t *)MP3_DEC_BASE)

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t DAI_EN            : 1;
        uint32_t ISR_EN            : 1;
        uint32_t VOL               : 5;       
    } Bits;
} struct_MP3Dec_Init_t;


typedef struct __MP3_DEC_HandleTypeDef
{
    struct_MP3Dec_Init_t mp3dec_ctrl_Init;
    REG_MP3D_EQ0_t       mp3dec_eq0_Init;
    REG_MP3D_EQ1_t       mp3dec_eq1_Init;
    uint8_t              *MP3Enced_Data;
    uint32_t             MP3Enced_Index;
    uint32_t             FrameLen;
    uint32_t             LeftLen;
    void (*Callback)(struct __MP3_DEC_HandleTypeDef *hSbcDec);                /*!< MP3 decode finish Callback */
}MP3_DEC_HandleTypeDef;

#define __MP3D_SOFTRST()                   (MP3D->MP3D_CTRL.Bits.MP3D_SOFTRST = 1)
#define __MP3D_PCM_FIFO_RESET()            (MP3D->MP3D_CTRL.Bits.RESET_PCM_FIFO = 1)
#define __MP3D_ISSUE_NEW_FILE()            (MP3D->MP3D_CTRL.Bits.ISSUE_NEW_FILE = 1)
#define __MP3D_OPERA_ENABLE()              (MP3D->MP3D_CTRL.Bits.OPERA_EN = 1)
#define __MP3D_SET_FRMCNT(frmcnt)          (MP3D->MP3D_FRMCNT = frmcnt)
#define __MP3D_GET_FRMCNT                  (MP3D->MP3D_FRMCNT)
#define __MP3D_GET_INTSTA                  (MP3D->MP3D_INTSTA.Word)
#define __MP3D_CHECK_NEED_SEC()            (MP3D->MP3D_INTSTA.Bits.SOURCE_CMPLETION_ISR == 1)
#define __MP3D_RESTART()                   (MP3D->MP3D_CTRL.Bits.RESTART_DEC = 1)

#define __MP3D_PCM_BUFF_FULL_ISR_IS_SET()  (MP3D->MP3D_INTSTA.Bits.PCM_BUFFER_FULL_ISR == 1)
#define __MP3D_SRC_COMPLETE_ISR_IS_SET()   (MP3D->MP3D_INTSTA.Bits.SOURCE_CMPLETION_ISR == 1)

#define __MP3D_COMPLETE_ISR_DISABLE()      (MP3D->MP3D_INTMASK.Bits.SOURCE_CMPLETION_ISR_EN = 0)
#define __MP3D_COMPLETE_ISR_ENABLE()       (MP3D->MP3D_INTMASK.Bits.SOURCE_CMPLETION_ISR_EN = 1)

/* mp3 decoder init */
void mp3_dec_init(MP3_DEC_HandleTypeDef *hmp3dec, uint32_t *pcm_buff, uint32_t pcm_buf_size);
/* mp3 decoder play data without isr */
void mp3_dec_playdata(MP3_DEC_HandleTypeDef *hmp3dec, uint8_t *fp_Data, uint32_t fu32_Size);
/* mp3 decoder get stream information */
void mp3d_get_stream_info(struct_MP3D_stream_info_t *info);
/* mp3 decoder failed */
int  mp3d_check_dec_failed(void);
/* mp3 decoder handle function in mp3 decoder isr */
void mp3dec_IRQHandler(MP3_DEC_HandleTypeDef *hmp3dec);
/* mp3 decoder play data with isr */
void mp3_dec_playdata_IT(MP3_DEC_HandleTypeDef *hmp3dec, uint8_t *fp_Data, uint32_t fu32_Size);

#endif
