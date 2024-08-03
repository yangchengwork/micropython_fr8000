/*
  ******************************************************************************
  * @file    driver_codec.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of codec HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_CODEC_H__
#define __DRIVER_CODEC_H__

#include "fr30xx.h"

/** @addtogroup CODEC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Block clock enable Register */
typedef union
{
    struct {
        uint32_t CLK_CDC_ADC        : 1;
        uint32_t CLK_CDC_DAC        : 1;
        uint32_t CLK_I2STX          : 1;
        uint32_t CLK_I2SRX          : 1;
        uint32_t CLK_ADCFF          : 1;
        uint32_t CLK_DACFFLR        : 1;
        uint32_t CLK_DACFF01        : 1;
        uint32_t CLK_ASRC0          : 1;
        uint32_t CLK_ASRC1          : 1;
        uint32_t CLK_GPF0           : 1;
        uint32_t CLK_GPF1           : 1;
        uint32_t CLK_ALC            : 1;
        uint32_t CLK_DRC            : 1;
        uint32_t CLK_rsv            : 13;
        uint32_t CLK_ASRC0_OUT_LVD  : 1;
        uint32_t CLK_ASRC1_OUT_LVD  : 1;
        uint32_t CLK_ASRC0_OUT_SR   : 1;
        uint32_t CLK_ASRC0_IN_SR    : 1;
        uint32_t CLK_ASRC1_OUT_SR   : 1;
        uint32_t CLK_ASRC1_IN_SR    : 1;
    }s;
    uint32_t CLK_EN;
}REG_CodecClockEnable_t;

/* Block Reset Register */
typedef union
{
    struct {
        uint32_t Rst_CDC_ADC    : 1;
        uint32_t Rst_CDC_DAC    : 1;
        uint32_t Rst_I2STX      : 1;
        uint32_t Rst_I2SRX      : 1;
        uint32_t Rst_ADCFF_O    : 1;
        uint32_t Rst_ADCFF_I    : 1;
        uint32_t Rst_ADCFF      : 1;
        uint32_t Rst_DACFFLR_O  : 1;
        uint32_t Rst_DACFFLR_I  : 1;
        uint32_t Rst_DACFFLR    : 1;
        uint32_t Rst_DACFF01_O  : 1;
        uint32_t Rst_DACFF01_I  : 1;
        uint32_t Rst_DACFF01    : 1;
        uint32_t Rst_ASRC0      : 1;
        uint32_t Rst_ASRC1      : 1;
        uint32_t Rst_GPF0       : 1;
        uint32_t Rst_GPF1       : 1;
        uint32_t Rst_ALC        : 1;
        uint32_t Rst_DRC        : 1;
        uint32_t rsv            : 13;
    }s;
    uint32_t RESET;
}REG_CodecReset_t;

/* Block Enable Register */
typedef struct
{
    uint32_t CDC_ADC    : 1;
    uint32_t CDC_DAC    : 1;
    uint32_t I2STX      : 1;
    uint32_t I2SRX      : 1;
    uint32_t DACFFLR    : 1;
    uint32_t DACFF01    : 1;
    uint32_t ASRC0      : 1;
    uint32_t ASRC1      : 1;
    uint32_t GPF0       : 1;
    uint32_t GPF1       : 1;
    uint32_t DRC        : 1;
    uint32_t ALC        : 1;
    uint32_t CDC_TXOUT  : 1;
    uint32_t rsv        : 19;
}REG_CodecEnable_t;

/* Audio PLL predividor Register */
typedef struct
{
    uint32_t AUPLL_DIV_GPF    : 6;
    uint32_t AUPLL_DIV_ASRC   : 6;
    uint32_t AUPLL_DIV_SAMPLE : 6;
    uint32_t rsv              : 14;
}REG_AUPLLPrediv_t;

/* System PLL predividor Register */
typedef struct
{
    uint32_t SPLL_DIV_GPF    : 6;
    uint32_t SPLL_DIV_ASRC   : 6;
    uint32_t rsv             : 20;
}REG_SPLLPrediv_t;

/* Master Clock Output Configuration Register */
typedef struct
{
    uint32_t DIV        : 10;
    uint32_t DIV_TYPE   : 1;
    uint32_t MCLK_SRC   : 2;
    uint32_t EN         : 1;
    uint32_t rsv        : 18;
}REG_MCLKCfg_t;

/* ADC Configure Register */
typedef struct
{
    uint32_t rsv2               : 1;
    uint32_t ENDIAN_REVERSE     : 1;
    uint32_t USB_MODE           : 1;
    uint32_t rsv0               : 1;
    uint32_t CLK_SOURCE         : 2;
    uint32_t OV_SAMPLE_MODE     : 2;
    uint32_t SAMPLE_RATE        : 4;
    uint32_t HFP_EN             : 1;
    uint32_t rsv1               : 19;
}REG_CodecAdcCfg_t;

/* ADC Volume Configure Register */
typedef struct
{
    uint32_t VOLUME     : 17;
    uint32_t rsv        : 15;
}REG_CodecAdcVol_t;

/* ADC Clock Divider Configure Register */
typedef struct
{
    uint32_t DIV            : 7;
    uint32_t DIV_TYPE       : 1;
    uint32_t SMP_DIV        : 7;
    uint32_t DIV_MAUAL_EN   : 1;
    uint32_t rsv            : 16;
}REG_CodecAdcClkDiv_t;

/* DAC Configure Register */
typedef struct
{
    uint32_t rsv3               : 1;
    uint32_t USB_MODE           : 1;
    uint32_t rsv0               : 2;
    uint32_t SAMPLE_RATE        : 4;
    uint32_t OV_SAMPLE_MODE     : 2;
    uint32_t CLK_SOURCE         : 2;
    uint32_t rsv2               : 4;
    uint32_t SINC_GAIM_COMP     : 12;
    uint32_t rsv1               : 4;
}REG_CodecDacCfg_t;

/* DAC DSM Configure Register */
typedef struct
{
    uint32_t DITHER_POW     : 24;
    uint32_t DSM_MODE       : 1;
    uint32_t DITHER_EN      : 1;
    uint32_t SCRAMBLE_EN    : 1;
    uint32_t rsv1           : 5;
}REG_CodecDacDsmCfg_t;

/* DAC Volume Configure Register */
typedef struct
{
    uint32_t VOLUME     : 16;
    uint32_t rsv        : 16;
}REG_CodecDacVol_t;

/* DAC Clock Divider Configure Register */
typedef struct
{
    uint32_t DIV            : 7;
    uint32_t DIV_TYPE       : 1;
    uint32_t CIC_DIV        : 7;
    uint32_t DIV_MAUAL_EN   : 1;
    uint32_t rsv            : 16;
}REG_CodecDacClkDiv_t;

/* I2S TX Control Register */
typedef struct
{
    uint32_t FORMAT     : 2;
    uint32_t DCI_WL     : 2;
    uint32_t LR_POL     : 1;
    uint32_t LR_SWAP    : 1;
    uint32_t CHANNEL_CP : 1;
    uint32_t BCLK_INV   : 1;
    uint32_t I2S_MODE   : 1;
    uint32_t MCLK_SRC   : 2;
    uint32_t TRX_SHARE  : 1;
    uint32_t rsv        : 20;
}REG_I2STxCtrl_t;

/* I2S TX Clock Control Register */
typedef struct
{
    uint32_t BCLK_DIV   : 16;
    uint32_t LRCLK_DIV  : 16;
}REG_I2STxClkCtrl_t;

/* I2S RX Control Register */
typedef struct
{
    uint32_t FORMAT     : 2;
    uint32_t DCI_WL     : 2;
    uint32_t LR_POL     : 1;
    uint32_t LR_SWAP    : 1;
    uint32_t CHANNEL_CP : 1;
    uint32_t BCLK_INV   : 1;
    uint32_t I2S_MODE   : 1;
    uint32_t MCLK_SRC   : 2;
    uint32_t rsv        : 21;
}REG_I2SRxCtrl_t;

/* I2S RX Clock Control Register */
typedef struct
{
    uint32_t BCLK_DIV   : 16;
    uint32_t LRCLK_DIV  : 16;
}REG_I2SRxClkCtrl_t;

/* FIFO Operation Mode Register */
typedef struct
{
    uint32_t ADCFF      : 1;
    uint32_t DACFFLR    : 1;
    uint32_t DACFF01    : 1;
    uint32_t rsv1       : 29;
}REG_CodecFIFOOpMode_t;

/* ADC FIFO Threshold Configure Register */
typedef struct
{
    uint32_t LEFT_F     : 6;
    uint32_t rsv0       : 2;
    uint32_t RIGHT_F    : 6;
    uint32_t rsv1       : 18;
}REG_CodecADCFIFOThd_t;

/* DAC FIFO Threshold Configure Register */
typedef struct
{
    uint32_t FFLR_LEFT_E    : 6;
    uint32_t rsv0           : 2;
    uint32_t FFLR_RIGHT_E   : 6;
    uint32_t rsv1           : 2;
    uint32_t FF01_LEFT_E    : 6;
    uint32_t rsv2           : 2;
    uint32_t FF01_RIGHT_E   : 6;
    uint32_t rsv3           : 2;
}REG_CodecDACFIFOThd_t;

/* DAC FIFO-LR Sample Rate Configure Register */
typedef struct
{
    uint32_t DIV        : 16;
    uint32_t CLK_SRC    : 2;
    uint32_t rsv        : 14;
}REG_CodecDACFFLRSampleRate_t;

/* DAC FIFO-01 Sample Rate Configure Register */
typedef struct
{
    uint32_t DIV        : 16;
    uint32_t CLK_SRC    : 2;
    uint32_t rsv        : 14;
}REG_CodecDACFF01SampleRate_t;

/* Codec DMA Enable Register */
typedef struct
{
    uint32_t ADC_L    : 1;
    uint32_t ADC_R    : 1;
    uint32_t DACLR_L  : 1;
    uint32_t DACLR_R  : 1;
    uint32_t DAC01_L  : 1;
    uint32_t DAC01_R  : 1;
    uint32_t rsv        : 26;
}REG_CodecDmaCtrl_t;

/* Codec DMA ADC Level Register */
typedef struct
{
    uint32_t L          : 6;
    uint32_t rsv0       : 2;
    uint32_t R          : 6;
    uint32_t rsv1       : 18;
}REG_CodecDmaADCLvl_t;

/* Codec DMA DAC Level Register */
typedef struct
{
    uint32_t FFLR_L     : 6;
    uint32_t rsv0       : 2;
    uint32_t FFLR_R     : 6;
    uint32_t rsv1       : 2;
    uint32_t FF01_L     : 6;
    uint32_t rsv2       : 2;
    uint32_t FF01_R     : 6;
    uint32_t rsv3       : 2;
}REG_CodecDmaDACLvl_t;

/* Codec ASRC System Config Register */
typedef struct
{
    uint32_t MAX_COUNT      : 14;
    uint32_t FIFO_OPT_LEVEL : 9;
    uint32_t MUTE           : 1;
    uint32_t BYPASS         : 1;
    uint32_t rsv            : 7;
}REG_CodecASRCSysCfg_t;

/* Codec ASRC Ratio Control Mode Selection Register */
typedef struct
{
    uint32_t MANUAL_RATIO   : 26;
    uint32_t RATIO_MODE     : 1;
    uint32_t rsv            : 5;
}REG_CodecASRCModeCfg_t;

/* Codec ASRC Ratio Status Register */
typedef struct
{
    uint32_t RATIO_OUT      : 26;
    uint32_t LOCKED         : 1;
    uint32_t rsv            : 5;
}REG_CodecASRCRatioStatus_t;

/* Codec ASRC FIFO Status Register */
typedef struct
{
    uint32_t LEVEL          : 9;
    uint32_t OVERFLOW       : 1;
    uint32_t rsv            : 22;
}REG_CodecASRCFIFOStatus_t;

/* ASRC Input Sample Rate Configure Register */
typedef struct
{
    uint32_t DIV        : 16;
    uint32_t CLK_SRC    : 2;
    uint32_t rsv        : 14;
}REG_CodecASRCInputSampleRate_t;

/* ASRC Output Sample Rate Configure Register */
typedef struct
{
    uint32_t DIV        : 16;
    uint32_t CLK_SRC    : 2;
    uint32_t rsv        : 14;
}REG_CodecASRCOutputSampleRate_t;

/* ASRC Clock Configure Register */
typedef struct
{
    uint32_t DIV            : 5;
    uint32_t DIV_TYPE       : 1;
    uint32_t CLK_SRC        : 2;
    uint32_t rsv            : 24;
}REG_CodecASRCClkCfg_t;

/* GPF System Configure Register */
typedef struct
{
    uint32_t DSP_MODE           : 1;
    uint32_t BYPASS             : 1;
    uint32_t PRE_GAIN0_CHG_SMP  : 10;
    uint32_t PRE_GAIN1_CHG_SMP  : 10;
    uint32_t PRE_GAIN0_STEPS    : 4;
    uint32_t PRE_GAIN1_STEPS    : 4;
    uint32_t rsv                : 2;
}REG_CodecGPFSysCfg_t;

/* GPF Clock Configure Register */
typedef struct
{
    uint32_t DIV            : 7;
    uint32_t DIV_TYPE       : 1;
    uint32_t CLK_SRC        : 2;
    uint32_t rsv            : 22;
}REG_CodecGPFClkCfg_t;

/* GPF Pre-Gain Configure Register */
typedef struct
{
    uint32_t CH0            : 16;
    uint32_t CH1            : 16;
}REG_CodecGPFPreGainCfg_t;


/* GPF Sections Enable Register */
typedef union
{
    struct {
        uint32_t GP_1A_EN       : 1;
        uint32_t GP_1B_EN       : 1;
        uint32_t GP_1C_EN       : 1;
        uint32_t GP_1D_EN       : 1;
        uint32_t GP_1E_EN       : 1;
        uint32_t GP_1F_EN       : 1;
        uint32_t GP_2A_EN       : 1;
        uint32_t GP_2B_EN       : 1;
        uint32_t GP_2C_EN       : 1;
        uint32_t GP_2D_EN       : 1;
        uint32_t GP_2E_EN       : 1;
        uint32_t GP_2F_EN       : 1;
        uint32_t rsv            : 20;
    } s;
    uint32_t EN;
}REG_CodecGPFSectionEn_t;

/* GPF Sum Enable Register */
typedef union
{
    struct {
        uint32_t GP_SUM0_EN     : 1;
        uint32_t GP_SUM1_EN     : 1;
        uint32_t GP_SUM2_EN     : 1;
        uint32_t GP_SUM3_EN     : 1;
        uint32_t GP_SUM4_EN     : 1;
        uint32_t GP_SUM5_EN     : 1;
        uint32_t GP_SUM6_EN     : 1;
        uint32_t rsv            : 25;
    } s;
    uint32_t EN;
}REG_CodecGPFSumnEn_t;

/* GPF Sum Cfg Register */
typedef union
{
    struct {
        uint32_t GP_SUM0_ADDSUB : 1;
        uint32_t GP_SUM1_ADDSUB : 1;
        uint32_t GP_SUM2_ADDSUB : 1;
        uint32_t GP_SUM3_ADDSUB : 1;
        uint32_t GP_SUM4_ADDSUB : 1;
        uint32_t GP_SUM5_ADDSUB : 1;
        uint32_t GP_SUM6_ADDSUB : 1;
        uint32_t rsv            : 25;
    } s;
    uint32_t ADD_OR_SUB;
}REG_CodecGPFSumCfg_t;

/* GPF Sum0 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 2;
    uint32_t SRC_B          : 2;
    uint32_t rsv            : 28;
}REG_CodecGPFSum0Cfg_t;

/* GPF Sum1 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 4;
    uint32_t SRC_B          : 4;
    uint32_t rsv            : 24;
}REG_CodecGPFSum1Cfg_t;

/* GPF Sum2 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 4;
    uint32_t SRC_B          : 4;
    uint32_t rsv            : 24;
}REG_CodecGPFSum2Cfg_t;

/* GPF Sum3 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 4;
    uint32_t SRC_B          : 4;
    uint32_t rsv            : 24;
}REG_CodecGPFSum3Cfg_t;

/* GPF Sum4 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 4;
    uint32_t SRC_B          : 4;
    uint32_t rsv            : 24;
}REG_CodecGPFSum4Cfg_t;

/* GPF Sum5 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 5;
    uint32_t rsv0           : 3;
    uint32_t SRC_B          : 5;
    uint32_t rsv1           : 19;
}REG_CodecGPFSum5Cfg_t;

/* GPF Sum6 Cfg Register */
typedef struct
{
    uint32_t SRC_A          : 5;
    uint32_t rsv0           : 3;
    uint32_t SRC_B          : 5;
    uint32_t rsv1           : 19;
}REG_CodecGPFSum6Cfg_t;

/* GPF Output Cfg Register */
typedef struct
{
    uint32_t SRC_CH0        : 5;
    uint32_t rsv0           : 3;
    uint32_t SRC_CH1        : 5;
    uint32_t rsv1           : 19;
}REG_CodecGPFOutputCfg_t;

/* GPF Section Coefficient Register */
typedef struct
{
    uint32_t FIRST_B0;
    uint32_t FIRST_B1;
    uint32_t FIRST_B2;
    uint32_t FIRST_A1;
    uint32_t FIRST_A2;
    uint32_t SECOND_B0;
    uint32_t SECOND_B1;
    uint32_t SECOND_B2;
    uint32_t SECOND_A1;
    uint32_t SECOND_A2;
}REG_CodecGPFSectionCoef_t;

/* ALC Clock Configure Register */
typedef struct
{
    uint32_t DIV            : 7;
    uint32_t DIV_TYPE       : 1;
    uint32_t rsv            : 24;
}REG_CodecALCClkCfg_t;

/* ALC System Configure Register */
typedef struct
{
    uint32_t HFP_EN         : 1;
    uint32_t EXPAND_CFG     : 1;
    uint32_t NOISE_CFG      : 1;
    uint32_t LEFT_EN        : 1;
    uint32_t RIGHT_EN       : 1;
    uint32_t SPLIT_MODE     : 1;
    uint32_t CH_SEL         : 1;
    uint32_t BYPASS         : 1;
    uint32_t rsv            : 24;
}REG_CodecALCSysCfg_t;

/* ALC Attack Rate Configure Register */
typedef struct
{
    uint32_t ATTACK_RATE    : 21;
    uint32_t rsv            : 11;
}REG_CodecALCAttackRate_t;

/* ALC Decay Rate Configure Register */
typedef struct
{
    uint32_t DECAY_RATE     : 21;
    uint32_t rsv            : 11;
}REG_CodecALCDecayRate_t;

/* ALC Target Threshold Configure Register */
typedef struct
{
    uint32_t THD            : 20;
    uint32_t rsv0           : 12;
    uint32_t THD_LOWER      : 20;
    uint32_t rsv1           : 12;
    uint32_t THD_UPPER      : 20;
    uint32_t rsv2           : 12;
}REG_CodecALCTgtThd_t;

/* ALC Target Threshold Upper Limite Configure Register */
typedef struct
{
    uint32_t THD_LOWER      : 20;
    uint32_t rsv0           : 12;
    uint32_t THD_UPPER      : 20;
    uint32_t rsv1           : 12;
    uint32_t THD            : 20;
    uint32_t rsv2           : 12;
}REG_CodecALCNoiseThd_t;

/* ALC high pass filter Configure Register */
typedef struct {
    uint32_t N0     : 24;
    uint32_t rsv0   : 8;
    uint32_t N1     : 24;
    uint32_t rsv1   : 8;
    uint32_t D1     : 24;
    uint32_t rsv2   : 8;
}REG_CodecALCHPF_t;

/* ALC low pass filter Configure Register */
typedef struct {
    uint32_t N0     : 24;
    uint32_t rsv0   : 8;
    uint32_t N1     : 24;
    uint32_t rsv1   : 8;
    uint32_t D1     : 24;
    uint32_t rsv2   : 8;
}REG_CodecALCLPF_t;

/* Codec Data Routing Configuration Register */
typedef struct {
    uint32_t ADC_SEL    : 1;
    uint32_t DAC_SEL    : 1;
    uint32_t rsv0       : 2;
    uint32_t rsv1       : 2;
    uint32_t rsv2       : 26;
}REG_CodecRoute_t;

/* Codec FIFO Routing Configuration Register */
typedef struct {
    uint32_t ADCFF_R_SRC    : 2;
    uint32_t ADCFF_L_SRC    : 2;
    uint32_t ADCFF_BITWD    : 2;
    uint32_t DACFF_LR_BITWD : 2;
    uint32_t DACFF_01_BITWD : 2;
    uint32_t rsv            : 22;
}REG_CodecFFRoute_t;

/* Codec ASRC Routing Configuration Register */
typedef struct {
    uint32_t ASRC0_SRC      : 4;
    uint32_t ASRC1_SRC      : 4;
    uint32_t rsv            : 24;
}REG_CodecASRCRoute_t;

/* Codec GPF0 Routing Configuration Register */
typedef struct {
    uint32_t CH0_SRC        : 2;
    uint32_t CH1_SRC        : 2;
    uint32_t rsv            : 28;
}REG_CodecGPF0Route_t;

/* Codec GPF1 Routing Configuration Register */
typedef struct {
    uint32_t CH0_SRC        : 3;
    uint32_t CH1_SRC        : 3;
    uint32_t rsv            : 26;
}REG_CodecGPF1Route_t;

/* Codec interrupt enable Register */
typedef union
{
    struct {
        uint32_t ASRC0_LOCK     : 1;
        uint32_t ASRC0_UNLOCK   : 1;
        uint32_t ASRC0_FF_OF    : 1;    // FIFO overflow
        uint32_t ASRC0_FF_RCV   : 1;    // FIFO recover from overflow
        uint32_t ASRC1_LOCK     : 1;
        uint32_t ASRC1_UNLOCK   : 1;
        uint32_t ASRC1_FF_OF    : 1;    // FIFO overflow
        uint32_t ASRC1_FF_RCV   : 1;    // FIFO recover from overflow
        uint32_t ADCFF_L_F       : 1;
        uint32_t ADCFF_R_F       : 1;
        uint32_t ADCFF_L_E       : 1;
        uint32_t ADCFF_R_E       : 1;
        uint32_t ADCFF_L_AF      : 1;
        uint32_t ADCFF_R_AF      : 1;
        uint32_t DACFFLR_L_F     : 1;
        uint32_t DACFFLR_R_F     : 1;
        uint32_t DACFFLR_L_E     : 1;
        uint32_t DACFFLR_R_E     : 1;
        uint32_t DACFFLR_L_AE    : 1;
        uint32_t DACFFLR_R_AE    : 1;
        uint32_t DACFF01_L_F     : 1;
        uint32_t DACFF01_R_F     : 1;
        uint32_t DACFF01_L_E     : 1;
        uint32_t DACFF01_R_E     : 1;
        uint32_t DACFF01_L_AE    : 1;
        uint32_t DACFF01_R_AE    : 1;
        uint32_t rsv2           : 6;
    } s;
    uint32_t STATUS;
}REG_CodecIntEn_t;

/* Codec interrupt Status Register */
typedef union
{
    struct {
        uint32_t ASRC0_LOCK     : 1;
        uint32_t ASRC0_UNLOCK   : 1;
        uint32_t ASRC0_FF_OF    : 1;    // FIFO overflow
        uint32_t ASRC0_FF_RCV   : 1;    // FIFO recover from overflow
        uint32_t ASRC1_LOCK     : 1;
        uint32_t ASRC1_UNLOCK   : 1;
        uint32_t ASRC1_FF_OF    : 1;    // FIFO overflow
        uint32_t ASRC1_FF_RCV   : 1;    // FIFO recover from overflow
        uint32_t ADCFF_L_F      : 1;
        uint32_t ADCFF_R_F      : 1;
        uint32_t ADCFF_L_E      : 1;
        uint32_t ADCFF_R_E      : 1;
        uint32_t ADCFF_L_AF     : 1;
        uint32_t ADCFF_R_AF     : 1;
        uint32_t DACFFLR_L_F    : 1;
        uint32_t DACFFLR_R_F    : 1;
        uint32_t DACFFLR_L_E    : 1;
        uint32_t DACFFLR_R_E    : 1;
        uint32_t DACFFLR_L_AE   : 1;
        uint32_t DACFFLR_R_AE   : 1;
        uint32_t DACFF01_L_F    : 1;
        uint32_t DACFF01_R_F    : 1;
        uint32_t DACFF01_L_E    : 1;
        uint32_t DACFF01_R_E    : 1;
        uint32_t DACFF01_L_AE   : 1;
        uint32_t DACFF01_R_AE   : 1;
        uint32_t rsv2           : 6;
    } s;
    uint32_t STATUS;
}REG_CodecIntStatus_t;

/* Codec interrupt clear Register */
typedef union
{
    struct {
        uint32_t ASRC0_LOCK     : 1;
        uint32_t ASRC0_UNLOCK   : 1;
        uint32_t ASRC0_FF_OF    : 1;    // FIFO overflow
        uint32_t ASRC0_FF_RCV   : 1;    // FIFO recover from overflow
        uint32_t ASRC1_LOCK     : 1;
        uint32_t ASRC1_UNLOCK   : 1;
        uint32_t ASRC1_FF_OF    : 1;    // FIFO overflow
        uint32_t ASRC1_FF_RCV   : 1;    // FIFO recover from overflow
        uint32_t rsv            : 24;
    } s;
    uint32_t STATUS;
}REG_CodecIntClear_t;

/* Codec Analog Register 0 */
typedef struct
{
    uint32_t PGA2_TO_TST_EN    :    1; 
    uint32_t PGA1_TO_TST_EN    :    1;
    uint32_t R2TST_EN          :    1;
    uint32_t L2TST_EN          :    1;
    uint32_t VMID_CTL          :    3;
    uint32_t RSV0              :    1;
    uint32_t BIAS_IB_IS        :    3;
    uint32_t CODEC_BIAS_MODE   :    1;
    uint32_t MICBIAS_CTL       :    1;
    uint32_t LVVDDA_EN         :    1;
    uint32_t VMID_DRV          :    1;
    uint32_t VMID_SEL          :    1;
    uint32_t RPA_PD            :    2;
    uint32_t RMIX_PD           :    2;
    uint32_t RMIX_VMIDBUF_PD   :    1;
    uint32_t PA_PDD            :    1;
    uint32_t RDAC_PD           :    1;
    uint32_t CODEC_BG_PD       :    1;
    uint32_t ADC_PD            :    1;
    uint32_t PGA_STG2_PD       :    1;
    uint32_t PGA_STG1_PD       :    1;
    uint32_t PGA_STG2_INV_PD   :    1;
    uint32_t MICBIAS_PD        :    1;
    uint32_t VMID_RAMP_PD      :    1;
    uint32_t VMID_PD           :    1;
    uint32_t BIAS_PD           :    1;
}REG_CodecAna0_t;

typedef struct
{
    uint32_t rsv            : 32;
}REG_CodecAna1_t;

typedef struct
{
    uint32_t rsv            : 32;
}REG_CodecAna2_t;

typedef struct
{
    uint32_t rsv            : 32;
}REG_CodecAna3_t;

typedef struct
{
    uint32_t diag0_mux           : 7;
    uint32_t diag0_en            : 1;
    uint32_t diag1_mux           : 7;
    uint32_t diag1_en            : 1;
    uint32_t diag2_mux           : 7;
    uint32_t diag2_en            : 1;
    uint32_t diag3_mux           : 7;
    uint32_t diag3_en            : 1;
}REG_CodecDiag_t;

/* ------------------------------------------------*/
/*                   CODEC Register                */
/* ------------------------------------------------*/
typedef struct 
{
    /* Codec System Control Registers */
    volatile REG_CodecClockEnable_t         ClockEnable;        /* Offset 0x00 */
    volatile REG_CodecReset_t               Reset;              /* Offset 0x04 */
    volatile REG_CodecEnable_t              Enable;             /* Offset 0x08 */
    volatile REG_AUPLLPrediv_t              AudioPLLPrediv;     /* Offset 0x0C */
    volatile REG_SPLLPrediv_t               SystemPLLPrediv;    /* Offset 0x10 */
    volatile REG_MCLKCfg_t                  MCLKCfg;            /* Offset 0x14 */
    
    /* Codec ADC Control Registers */
    volatile REG_CodecAdcCfg_t              AdcCfg;             /* Offset 0x18 */
    volatile REG_CodecAdcVol_t              AdcVolume;          /* Offset 0x1C */
    volatile REG_CodecAdcClkDiv_t           AdcClockDiv;        /* Offset 0x20 */
    
    /* Codec DAC Control Registers */
    volatile REG_CodecDacCfg_t              DacCfg;             /* Offset 0x24 */
    volatile REG_CodecDacDsmCfg_t           DacDsmCfg;          /* Offset 0x28 */
    volatile REG_CodecDacVol_t              DacVolume;          /* Offset 0x2C */
    volatile REG_CodecDacClkDiv_t           DacClockDiv;        /* Offset 0x30 */
    
    /* I2S Control Registers */
    volatile REG_I2STxCtrl_t                I2STxCtrl;          /* Offset 0x34 */
    volatile REG_I2STxClkCtrl_t             I2STxClkCtrl;       /* Offset 0x38 */
    volatile REG_I2SRxCtrl_t                I2SRxCtrl;          /* Offset 0x3C */
    volatile REG_I2SRxClkCtrl_t             I2SRxClkCtrl;       /* Offset 0x40 */
    
    /* FIFO Control Registers */
    volatile uint32_t                       rsv0;               /* Offset 0x44 */
    volatile REG_CodecFIFOOpMode_t          FifoOpMode;         /* Offset 0x48 */
    volatile REG_CodecADCFIFOThd_t          FifoADCThd;         /* Offset 0x4C */
    volatile REG_CodecDACFIFOThd_t          FifoDACThd;         /* Offset 0x50 */
    volatile REG_CodecDACFFLRSampleRate_t   FifoDACFFSR;        /* Offset 0x54 */
    volatile REG_CodecDACFF01SampleRate_t   FifoDAC01SR;        /* Offset 0x58 */
    volatile uint32_t                       ADCDataL;           /* Offset 0x5C */
    volatile uint32_t                       ADCDataR;           /* Offset 0x60 */
    volatile uint32_t                       DACLRDataL;         /* Offset 0x64 */
    volatile uint32_t                       DACLRDataR;         /* Offset 0x68 */
    volatile uint32_t                       DAC01DataL;         /* Offset 0x6C */
    volatile uint32_t                       DAC01DataR;         /* Offset 0x70 */
    
    /* Codec DMA Control Registers */
    volatile REG_CodecDmaCtrl_t             DmaEnable;          /* Offset 0x74 */
    volatile REG_CodecDmaADCLvl_t           DmaADCLevel;        /* Offset 0x78 */
    volatile REG_CodecDmaDACLvl_t           DmaDACLevel;        /* Offset 0x7C */
    
    /* Codec ASRC Control Registers */
    struct {
        volatile REG_CodecASRCSysCfg_t              SysCfg;         /* Offset 0x80, 0x9C */
        volatile REG_CodecASRCModeCfg_t             RatioMode;      /* Offset 0x84, 0xA0 */
        volatile REG_CodecASRCRatioStatus_t         RatioStatus;    /* Offset 0x88, 0xA4 */
        volatile REG_CodecASRCFIFOStatus_t          FIFOStatus;     /* Offset 0x8C, 0xA8 */
        volatile REG_CodecASRCInputSampleRate_t     InputSR;        /* Offset 0x90, 0xAC */
        volatile REG_CodecASRCOutputSampleRate_t    OutputSR;       /* Offset 0x94, 0xB0 */
        volatile REG_CodecASRCClkCfg_t              ClkCfg;         /* Offset 0x98, 0xB4 */
    } ASRC[2];
              
    /* Codec GPF Control Registers */
    struct {
        volatile REG_CodecGPFSysCfg_t           SysCfg;             /* Offset 0xB8, 0x300 */
        volatile REG_CodecGPFClkCfg_t           ClkCfg;             /* Offset 0xBC, 0x304 */
        volatile REG_CodecGPFPreGainCfg_t       PreGainCfg;         /* Offset 0xC0, 0x308 */
        volatile REG_CodecGPFSectionEn_t        SectionEn;          /* Offset 0xC4, 0x30C */
        volatile REG_CodecGPFSumnEn_t           SumEn;              /* Offset 0xC8, 0x310 */
        volatile REG_CodecGPFSumCfg_t           SumCfg;             /* Offset 0xCC, 0x314 */
        volatile uint32_t                       Section1ASrc;       /* Offset 0xD0, 0x318 */
        volatile uint32_t                       Section1BSrc;       /* Offset 0xD4, 0x31C */
        volatile uint32_t                       Section1CSrc;       /* Offset 0xD8, 0x320 */
        volatile uint32_t                       Section1DSrc;       /* Offset 0xDC, 0x324 */
        volatile uint32_t                       Section1ESrc;       /* Offset 0xE0, 0x328 */
        volatile uint32_t                       Section1FSrc;       /* Offset 0xE4, 0x32C */
        volatile uint32_t                       Section2ASrc;       /* Offset 0xE8, 0x330 */
        volatile uint32_t                       Section2BSrc;       /* Offset 0xEC, 0x334 */
        volatile uint32_t                       Section2CSrc;       /* Offset 0xF0, 0x338 */
        volatile uint32_t                       Section2DSrc;       /* Offset 0xF4, 0x33C */
        volatile uint32_t                       Section2ESrc;       /* Offset 0xF8, 0x340 */
        volatile uint32_t                       Section2FSrc;       /* Offset 0xFC, 0x344 */
        volatile REG_CodecGPFSum0Cfg_t          Sum0Src;            /* Offset 0x100, 0x348 */
        volatile REG_CodecGPFSum1Cfg_t          Sum1Src;            /* Offset 0x104, 0x34C */
        volatile REG_CodecGPFSum2Cfg_t          Sum2Src;            /* Offset 0x108, 0x350 */
        volatile REG_CodecGPFSum3Cfg_t          Sum3Src;            /* Offset 0x10C, 0x354 */
        volatile REG_CodecGPFSum4Cfg_t          Sum4Src;            /* Offset 0x110, 0x358 */
        volatile REG_CodecGPFSum5Cfg_t          Sum5Src;            /* Offset 0x114, 0x35C */
        volatile REG_CodecGPFSum6Cfg_t          Sum6Src;            /* Offset 0x118, 0x360 */
        volatile REG_CodecGPFOutputCfg_t        OutCfg;             /* Offset 0x11C, 0x364 */
        volatile REG_CodecGPFSectionCoef_t      SectionCoef[12];    /* Offset 0x120, 0x368 */
    } GPF[2];
    
    /* Codec ALC, DRC Control Registers */
    struct {    
        volatile REG_CodecALCClkCfg_t           ClkCfg;             /* Offset 0x548, 0x588 */
        volatile REG_CodecALCSysCfg_t           SysCfg;             /* Offset 0x54C, 0x58C */
        volatile REG_CodecALCAttackRate_t       AttackRate;         /* Offset 0x550, 0x590 */
        volatile REG_CodecALCDecayRate_t        DecayRate;          /* Offset 0x554, 0x594 */
        volatile REG_CodecALCTgtThd_t           TargetThd;          /* Offset 0x558, 0x598 */
        volatile REG_CodecALCNoiseThd_t         NoiseThd;           /* Offset 0x564, 0x5A4 */
        volatile REG_CodecALCHPF_t              HPFCoef;            /* Offset 0x570, 0x5B0 */
        volatile REG_CodecALCLPF_t              LPFCoef;            /* Offset 0x57C, 0x5BC */
    } ALC[2];
    
    /* Codec Route Registers */
    volatile REG_CodecRoute_t                   CodecRoute;         /* Offset 0x5C8 */
    volatile REG_CodecFFRoute_t                 FFRoute;            /* Offset 0x5CC */
    volatile REG_CodecASRCRoute_t               ASRCRoute;          /* Offset 0x5D0 */
    volatile REG_CodecGPF0Route_t               GPF0Route;          /* Offset 0x5D4 */
    volatile REG_CodecGPF1Route_t               GPF1Route;          /* Offset 0x5D8 */
    
    /* Codec interrupt Registers */
    volatile REG_CodecIntEn_t                   CodecIntEn;         /* Offset 0x5DC */
    volatile REG_CodecIntStatus_t               CodecIntRawStatus;  /* Offset 0x5E0 */
    volatile REG_CodecIntStatus_t               CodecIntStatus;     /* Offset 0x5E4 */
    volatile REG_CodecIntClear_t                CodecIntClear;      /* Offset 0x5E8 */

    /* Codec Analog Registers */
    // volatile REG_CodecAna0_t                    CodecAna0;          /* Offset 0x5EC */
    // volatile REG_CodecAna1_t                    CodecAna1;          /* Offset 0x5F0 */
    // volatile REG_CodecAna2_t                    CodecAna2;          /* Offset 0x5F4 */
    // volatile REG_CodecAna3_t                    CodecAna3;          /* Offset 0x5F8 */
    volatile uint32_t                    CodecAna0;          /* Offset 0x5EC */
    volatile uint32_t                    CodecAna1;          /* Offset 0x5F0 */
    volatile uint32_t                    CodecAna2;          /* Offset 0x5F4 */
    volatile uint32_t                    CodecAna3;          /* Offset 0x5F8 */
    /* Codec Debug Settings */
    volatile REG_CodecDiag_t                    CodecDiag;          /* Offset 0x5FC */
}struct_Codec_t; 

#define CODEC       ((struct_Codec_t *)CODEC_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup CODEC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */

#define CODEC_FIFO_DEPTH                (64)
#define CODEC_FIFO_HALF_DEPTH           (CODEC_FIFO_DEPTH >> 1)

/* Codec input Config */
typedef enum
{
    INPUT_SELECT_BYPASS = 2,    // codec input bypass       
    INPUT_SELECT_ADC    = 0,
    INPUT_SELECT_I2S_RX = 1,

    INPUT_ROUTING_ASRC0_GPF0_ALC_ADCFF = 0,    /* IN -> ASRC0 -> GPF0 -> ALC -> ADC_FIFO */
    INPUT_ROUTING_GPF0_ALC_ADCFF       = 1,    /* IN -> GPF0 -> ALC -> ADC_FIFO */
}enum_Codec_Input_Config_t;

/* Codec output Config */
typedef enum
{
    OUTPUT_SELECT_BYPASS = 2,    // codec output bypass   
    OUTPUT_SELECT_DAC    = 0,
    OUTPUT_SELECT_I2S_TX = 1,

    OUTPUT_ROUTING_DACFFLR_ASRC1_GPF1_DRC         = 0,    /* DACFIFO_LR -> ASRC1 -> GPF1 -> DRC -> OUT */
    OUTPUT_ROUTING_DACFFLR_GPF1_DRC               = 1,    /* DACFIFO_LR -> GPF1 -> DRC -> OUT */
    OUTPUT_ROUTING_DACFFLR_DACFF01_ASRC1_GPF1_DRC = 2,    /* DACFIFO_LR & DACFIFO_01 -> ASRC1 -> GPF1 -> DRC -> OUT */
    OUTPUT_ROUTING_DACFFLR_DACFF01_GPF1_DRC       = 3,    /* DACFIFO_LR & DACFIFO_01 -> GPF1 -> DRC -> OUT */
}enum_Codec_Output_Config_t;

/* Codec FIFO Data Format */
typedef enum
{
    CODEC_FIFO_FORMAT_8BIT,
    CODEC_FIFO_FORMAT_16BIT,
    CODEC_FIFO_FORMAT_24BIT,
}enum_Codec_FIFO_Format_t;

/* MCLK source */
typedef enum
{
    MCLK_OUT_DISABLE      = 0,
    MCLK_OUT_ENABLE       = 1,

    MCLK_SOURCE_24M_MODE  = 0,
    MCLK_SOURCE_AUPLL     = 1,
    MCLK_SOURCE_EXTERN    = 2,

    MCLK_DIV_MODE_INTEGER = 0,
    MCLK_DIV_MODE_FLOAT   = 1,
}enum_Codec_MCLK_Config_t;

/* Codec ADC/DAC Clock source */
typedef enum
{
    CODEC_CLOCK_SOURCE_24M_MODE = 0,
    CODEC_CLOCK_SOURCE_AUPLL    = 1,
    CODEC_CLOCK_SOURCE_EXTERN   = 2,
}enum_Codec_Clcok_Src_t;

/* Codec Sample Rate */
typedef enum
{
    CODEC_SAMPLE_RATE_8000      = 0x00,
    CODEC_SAMPLE_RATE_12000     = 0x01,
    CODEC_SAMPLE_RATE_16000     = 0x02,
    CODEC_SAMPLE_RATE_24000     = 0x03,
    CODEC_SAMPLE_RATE_32000     = 0x04,
    CODEC_SAMPLE_RATE_48000     = 0x05,
    CODEC_SAMPLE_RATE_96000     = 0x06,
    CODEC_SAMPLE_RATE_192000    = 0x07,
    CODEC_SAMPLE_RATE_80124     = 0x08,
    CODEC_SAMPLE_RATE_11025     = 0x09,
    CODEC_SAMPLE_RATE_22050     = 0x0A,
    CODEC_SAMPLE_RATE_44100     = 0x0B,
    CODEC_SAMPLE_RATE_88200     = 0x0C,
    CODEC_SAMPLE_RATE_176400    = 0x0D,
}enum_Codec_SampleRate_t;

/* Codec oversampling level */
typedef enum
{
    CODEC_OVERSAMPLING_LOW,         // oversampling low level support to all SampleRate.
    CODEC_OVERSAMPLING_MIDDLE,      // oversampling middle level support up to 96K.
    CODEC_OVERSAMPLING_HIGH,        // oversampling high level support up to 48K.
}enum_Codec_Oversampling_level_t;

/* Codec I2S config */
typedef enum
{
    CODEC_I2S_MODE_SLAVE  = 0,
    CODEC_I2S_MODE_MASTER = 1,

    CODEC_I2S_STANDARD_LSB     = 0,
    CODEC_I2S_STANDARD_MSB     = 1,
    CODEC_I2S_STANDARD_PHILIPS = 2,
    CODEC_I2S_STANDARD_PCM     = 3,

    CODEC_I2S_DATA_FORMAT_16BIT = 0,
    CODEC_I2S_DATA_FORMAT_20BIT = 1,
    CODEC_I2S_DATA_FORMAT_24BIT = 2,

    CODEC_I2S_RATE_8000   = 8000,
    CODEC_I2S_RATE_11025  = 11025,
    CODEC_I2S_RATE_12000  = 12000,
    CODEC_I2S_RATE_16000  = 16000,
    CODEC_I2S_RATE_22050  = 22050,
    CODEC_I2S_RATE_24000  = 24000,
    CODEC_I2S_RATE_32000  = 32000,
    CODEC_I2S_RATE_44100  = 44100,
    CODEC_I2S_RATE_48000  = 48000,
    CODEC_I2S_RATE_80124  = 80124,
    CODEC_I2S_RATE_88200  = 88200,
    CODEC_I2S_RATE_96000  = 96000,
    CODEC_I2S_RATE_176400 = 176400,
    CODEC_I2S_RATE_192000 = 192000,

    CODEC_I2S_CHANNEL_COPY_DISABLE = 0,
    CODEC_I2S_CHANNEL_COPY_ENABLE  = 1,
}enum_Codec_I2S_Config_t;

/* Codec FIFO interrupt status */
typedef enum
{
    CODEC_INT_ASRC0_LOCK    = (1<<0),
    CODEC_INT_ASRC0_UNLOCK  = (1<<1),
    CODEC_INT_ASRC0_OF      = (1<<2),
    CODEC_INT_ASRC0_RCV     = (1<<3),
    CODEC_INT_ASRC1_LOCK    = (1<<4),
    CODEC_INT_ASRC1_UNLOCK  = (1<<5),
    CODEC_INT_ASRC1_OF      = (1<<6),
    CODEC_INT_ASRC1_RCV     = (1<<7),
    CODEC_INT_ADCFF_L_FULL   = (1<<8),
    CODEC_INT_ADCFF_R_FULL   = (1<<9),
    CODEC_INT_ADCFF_L_EMPTY  = (1<<10),
    CODEC_INT_ADCFF_R_EMPTY  = (1<<11),
    CODEC_INT_ADCFF_L_AFULL  = (1<<12),
    CODEC_INT_ADCFF_R_AFULL  = (1<<13),
    CODEC_INT_DACFF_L_FULL   = (1<<14),
    CODEC_INT_DACFF_R_FULL   = (1<<15),
    CODEC_INT_DACFF_L_EMPTY  = (1<<16),
    CODEC_INT_DACFF_R_EMPTY  = (1<<17),
    CODEC_INT_DACFF_L_AEMPTY = (1<<18),
    CODEC_INT_DACFF_R_AEMPTY = (1<<19),
    CODEC_INT_DACFF_0_FULL   = (1<<20),
    CODEC_INT_DACFF_1_FULL   = (1<<21),
    CODEC_INT_DACFF_0_EMPTY  = (1<<22),
    CODEC_INT_DACFF_1_EMPTY  = (1<<23),
    CODEC_INT_DACFF_0_AEMPTY = (1<<24),
    CODEC_INT_DACFF_1_AEMPTY = (1<<25),
}enum_Codec_INT_Status_t;

/** 
  * @brief  Masks for codec module reset.
  */
#define CODEC_RESET_ADC             (0x00000001U)
#define CODEC_RESET_DAC             (0x00000002U)
#define CODEC_RESET_I2S_TX          (0x00000004U)
#define CODEC_RESET_I2S_RX          (0x00000008U)
#define CODEC_RESET_ADCFF           (0x00000070U)
#define CODEC_RESET_DACFF_LR        (0x00000380U)
#define CODEC_RESET_DACFF_01        (0x00001C00U)
#define CODEC_RESET_ASRC0           (0x00002000U)
#define CODEC_RESET_ASRC1           (0x00004000U)
#define CODEC_RESET_GPF0            (0x00008000U)
#define CODEC_RESET_GPF1            (0x00010000U)
#define CODEC_RESET_ALC             (0x00020000U)
#define CODEC_RESET_DRC             (0x00040000U)

/* Analog default config */
#define CODEC_ANALOG0_CFG    (0x00004080)
#define CODEC_ANALOG1_CFG    (0x47628100)
#define CODEC_ANALOG2_CFG    (0x000d1FCF)
#define CODEC_ANALOG3_CFG    (0x04000000)

/* ADC/DAC data format */
typedef union 
{
    volatile void      *p_data;
    volatile uint8_t   *p_u8;
    volatile uint16_t  *p_u16;
    volatile uint32_t  *p_u32;
}union_DataFormat_t;

/*
 * @brief Codec Init Structure definition
 */
typedef struct
{
    uint32_t Codec_Input_sel;               /*!< Specifies the input source selcet.
                                                 This parameter can be a value of @ref enum_Codec_Input_config_t. */
    uint32_t Codec_Input_Routing_sel;       /*!< Specifies the input routing selcet.
                                                 This parameter can be a value of @ref enum_Codec_Input_config_t. */

    uint32_t Codec_Output_sel;              /*!< Specifies the output selcet.
                                                 This parameter can be a value of @ref enum_Codec_Output_Config_t. */
    uint32_t Codec_Output_Routing_sel;      /*!< Specifies the output routing selcet.
                                                 This parameter can be a value of @ref enum_Codec_Output_Config_t. */

    uint32_t ADC_DataFormat;                /*!< Specifies the ADC FIFO Data Format.
                                                 This parameter can be a value of @ref enum_Codec_FIFO_Format_t. */

    uint32_t DAC_LR_DataFormat;             /*!< Specifies the DAC FIFO left/right Data Format.
                                                 This parameter can be a value of @ref enum_Codec_FIFO_Format_t. */
    uint32_t DAC_01_DataFormat;             /*!< Specifies the DAC FIFO 0/1 Data Format.
                                                 This parameter can be a value of @ref enum_Codec_FIFO_Format_t. */
}struct_CodecInit_t;

/*
 * @brief Codec input ADC/I2S_RX parameters config
 */
typedef struct
{
    /* ------------------------------------------------------- */
    /* Set the following parameters when input select ADC mode */
    /* ------------------------------------------------------- */
    uint32_t ADC_ClockSource;               /*!< Specifies the codec ADC Clcok Source.
                                                 This parameter can be a value of @ref enum_Codec_Clcok_Src_t. */

    uint32_t ADC_SampleRate;                /*!< Specifies the codec ADC Sample Rate.
                                                 This parameter can be a value of @ref enum_Codec_SampleRate_t. */

    uint32_t ADC_Oversampling_Level;        /*!< Specifies the codec ADC Oversampling level.
                                                 This parameter can be a value of @ref enum_Codec_Oversampling_level_t. */

    /* ---------------------------------------------------------- */
    /* Set the following parameters when input select I2S_Rx mode */
    /* ---------------------------------------------------------- */
    uint32_t I2S_RX_Mode;                    /*!< Specifies the I2S operating mode.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_RX_Standard;                /*!< Specifies the communication standard.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_RX_DataFormat;              /*!< Specifies the I2S data format.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_RX_AudioFreq;               /*!< Specifies the frequency selected for the I2S communication.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_RX_ChannelCopy;             /*!< Specifies the I2S Channel Copy Enable.(Left Data copy to right)
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */
}struct_InputConfig_t;

/*
 * @brief Codec output DAC/I2S_TX parameter config
 */
typedef struct
{
    /* -------------------------------------------------------- */
    /* Set the following parameters when output select DAC mode */
    /* -------------------------------------------------------- */
    uint32_t DAC_ClockSource;               /*!< Specifies the codec DAC Clcok Source.
                                                 This parameter can be a value of @ref enum_Codec_Clcok_Src_t. */
    
    uint32_t DAC_SampleRate;                /*!< Specifies the codec DAC Sample Rate.
                                                 This parameter can be a value of @ref enum_Codec_SampleRate_t. */

    uint32_t DAC_Oversampling_Level;        /*!< Specifies the codec DAC Oversampling level.
                                                 This parameter can be a value of @ref enum_Codec_Oversampling_level_t. */

    /* ----------------------------------------------------------- */
    /* Set the following parameters when output select I2S_Tx mode */
    /* ----------------------------------------------------------- */
    uint32_t I2S_TX_Mode;                    /*!< Specifies the I2S operating mode.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_TX_Standard;                /*!< Specifies the communication standard.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_TX_DataFormat;              /*!< Specifies the I2S data format.
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */

    uint32_t I2S_TX_AudioFreq;               /*!< Specifies the frequency selected for the I2S communication.
                                                  This parameter can be a value of @ref enum_Codec_SampleRate_t */

    uint32_t I2S_TX_ChannelCopy;             /*!< Specifies the I2S Channel Copy Enable.(Left Data copy to right)
                                                  This parameter can be a value of @ref enum_Codec_I2S_Config_t */
}struct_OutputConfig_t;

/*
 * @brief MCLK parameter config
 */
typedef struct
{
    uint32_t MCLK_Out_Enable;    /*!< Specifies the MCLK output.
                                    This parameter can be a value of @ref enum_Codec_MCLK_Config_t. */

    uint32_t MCLK_Source;        /*!< Specifies the MCLK source select.
                                      This parameter can be a value of @ref enum_Codec_MCLK_Config_t. */

    uint32_t MCLK_DIV_Mode;      /*!< Specifies the MCLK DIV mode select.
                                      This parameter can be a value of @ref enum_Codec_MCLK_Config_t. */

                                /// note: select MCLK_DIV_MODE_INTEGER. MCLK = MCLK_Source / (MCLK_DIV + 1)
                                ///       select MCLK_DIV_MODE_FLOAT.   MCLK = MCLK_Source / ((MCLK_DIV + 1) / 2)

    uint32_t MCLK_DIV;           /*!< Specifies the MCLK DIV.
                                      This parameter can be a 10-bit value. */
}struct_MCLKConfig_t;

/*
 * @brief Codec handle Structure definition
 */
typedef struct
{
    struct_CodecInit_t        Init;                 /*!< Codec initialization parameters */

    struct_InputConfig_t      InputConfig;          /*!< Codec input parameter config */

    struct_OutputConfig_t     OutputConfig;         /*!< Codec output parameter config */

    struct_MCLKConfig_t       MCLKConfig;           /*!< MCLK config. This parameter is valid when the I2S_Tx/I2S_Rx mode is selected */
}CODEC_HandleTypeDef;

/* ################################ Initialization Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Codec I2S control */
#define __CODEC_I2S_TX_BCLKINV_ENABLE()                         (CODEC->I2STxCtrl.BCLK_INV = 1)
#define __CODEC_I2S_TX_BCLKINV_DISABLE()                        (CODEC->I2STxCtrl.BCLK_INV = 0)
#define __CODEC_I2S_TX_LRSWAP_ENABLE()                          (CODEC->I2STxCtrl.LR_SWAP  = 1)
#define __CODEC_I2S_TX_LRSWAP_DISABLE()                         (CODEC->I2STxCtrl.LR_SWAP  = 0)
#define __CODEC_I2S_TX_LRP_ENABLE()                             (CODEC->I2STxCtrl.LR_POL   = 1)
#define __CODEC_I2S_TX_LRP_DISABLE()                            (CODEC->I2STxCtrl.LR_POL   = 0)

#define __CODEC_I2S_RX_BCLKINV_ENABLE()                         (CODEC->I2SRxCtrl.BCLK_INV = 1)
#define __CODEC_I2S_RX_BCLKINV_DISABLE()                        (CODEC->I2SRxCtrl.BCLK_INV = 0)
#define __CODEC_I2S_RX_LRSWAP_ENABLE()                          (CODEC->I2SRxCtrl.LR_SWAP  = 1)
#define __CODEC_I2S_RX_LRSWAP_DISABLE()                         (CODEC->I2SRxCtrl.LR_SWAP  = 0)
#define __CODEC_I2S_RX_LRP_ENABLE()                             (CODEC->I2SRxCtrl.LR_POL   = 1)
#define __CODEC_I2S_RX_LRP_DISABLE()                            (CODEC->I2SRxCtrl.LR_POL   = 0)

/* Module clock enable/disable */
#define __CODEC_ADC_CLK_ENABLE()                                (CODEC->ClockEnable.s.CLK_CDC_ADC       = 1)
#define __CODEC_DAC_CLK_ENABLE()                                (CODEC->ClockEnable.s.CLK_CDC_DAC       = 1)
#define __CODEC_I2S_TX_CLK_ENABLE()                             (CODEC->ClockEnable.s.CLK_I2STX         = 1)
#define __CODEC_I2S_RX_CLK_ENABLE()                             (CODEC->ClockEnable.s.CLK_I2SRX         = 1)
#define __CODEC_ADCFIFO_CLK_ENABLE()                            (CODEC->ClockEnable.s.CLK_ADCFF         = 1)
#define __CODEC_DACFIFO_LR_CLK_ENABLE()                         (CODEC->ClockEnable.s.CLK_DACFFLR       = 1)
#define __CODEC_DACFIFO_01_CLK_ENABLE()                         (CODEC->ClockEnable.s.CLK_DACFF01       = 1)
#define __CODEC_ASRC0_CLK_ENABLE()                              (CODEC->ClockEnable.s.CLK_ASRC0         = 1)
#define __CODEC_ASRC1_CLK_ENABLE()                              (CODEC->ClockEnable.s.CLK_ASRC1         = 1)
#define __CODEC_GPF0_CLK_ENABLE()                               (CODEC->ClockEnable.s.CLK_GPF0          = 1)
#define __CODEC_GPF1_CLK_ENABLE()                               (CODEC->ClockEnable.s.CLK_GPF1          = 1)
#define __CODEC_ALC_CLK_ENABLE()                                (CODEC->ClockEnable.s.CLK_ALC           = 1)
#define __CODEC_DRC_CLK_ENABLE()                                (CODEC->ClockEnable.s.CLK_DRC           = 1)
#define __CODEC_ASRC0_OUT_LVD_CLK_ENABLE()                      (CODEC->ClockEnable.s.CLK_ASRC0_OUT_LVD = 1)
#define __CODEC_ASRC1_OUT_LVD_CLK_ENABLE()                      (CODEC->ClockEnable.s.CLK_ASRC1_OUT_LVD = 1)
#define __CODEC_ASRC0_INPUT_SAMPLE_CLK_ENABLE()                 (CODEC->ClockEnable.s.CLK_ASRC0_IN_SR   = 1)
#define __CODEC_ASRC0_OUTPUT_SAMPLE_CLK_ENABLE()                (CODEC->ClockEnable.s.CLK_ASRC0_OUT_SR  = 1)
#define __CODEC_ASRC1_INPUT_SAMPLE_CLK_ENABLE()                 (CODEC->ClockEnable.s.CLK_ASRC1_IN_SR   = 1)
#define __CODEC_ASRC1_OUTPUT_SAMPLE_CLK_ENABLE()                (CODEC->ClockEnable.s.CLK_ASRC1_OUT_SR  = 1)

#define __CODEC_ADC_CLK_DISABLE()                               (CODEC->ClockEnable.s.CLK_CDC_ADC       = 0)
#define __CODEC_DAC_CLK_DISABLE()                               (CODEC->ClockEnable.s.CLK_CDC_DAC       = 0)
#define __CODEC_I2S_TX_CLK_DISABLE()                            (CODEC->ClockEnable.s.CLK_I2STX         = 0)
#define __CODEC_I2S_RX_CLK_DISABLE()                            (CODEC->ClockEnable.s.CLK_I2SRX         = 0)
#define __CODEC_ADCFIFO_CLK_DISABLE()                           (CODEC->ClockEnable.s.CLK_ADCFF         = 0)
#define __CODEC_DACFIFO_LR_CLK_DISABLE()                        (CODEC->ClockEnable.s.CLK_DACFFLR       = 0)
#define __CODEC_DACFIFO_01_CLK_DISABLE()                        (CODEC->ClockEnable.s.CLK_DACFF01       = 0)
#define __CODEC_ASRC0_CLK_DISABLE()                             (CODEC->ClockEnable.s.CLK_ASRC0         = 0)
#define __CODEC_ASRC1_CLK_DISABLE()                             (CODEC->ClockEnable.s.CLK_ASRC1         = 0)
#define __CODEC_GPF0_CLK_DISABLE()                              (CODEC->ClockEnable.s.CLK_GPF0          = 0)
#define __CODEC_GPF1_CLK_DISABLE()                              (CODEC->ClockEnable.s.CLK_GPF1          = 0)
#define __CODEC_ALC_CLK_DISABLE()                               (CODEC->ClockEnable.s.CLK_ALC           = 0)
#define __CODEC_DRC_CLK_DISABLE()                               (CODEC->ClockEnable.s.CLK_DRC           = 0)
#define __CODEC_ASRC0_OUT_LVD_CLK_DISABLE()                     (CODEC->ClockEnable.s.CLK_ASRC0_OUT_LVD = 0)
#define __CODEC_ASRC1_OUT_LVD_CLK_DISABLE()                     (CODEC->ClockEnable.s.CLK_ASRC1_OUT_LVD = 0)
#define __CODEC_ASRC0_INPUT_SAMPLE_CLK_DISABLE()                (CODEC->ClockEnable.s.CLK_ASRC0_IN_SR   = 0)
#define __CODEC_ASRC0_OUTPUT_SAMPLE_CLK_DISABLE()               (CODEC->ClockEnable.s.CLK_ASRC0_OUT_SR  = 0)
#define __CODEC_ASRC1_INPUT_SAMPLE_CLK_DISABLE()                (CODEC->ClockEnable.s.CLK_ASRC1_IN_SR   = 0)
#define __CODEC_ASRC1_OUTPUT_SAMPLE_CLK_DISABLE()               (CODEC->ClockEnable.s.CLK_ASRC1_OUT_SR  = 0)

#define __CODEC_ALL_CLOCK_ENABLE()                              (CODEC->ClockEnable.CLK_EN = 0xFFFFFFFF)
#define __CODEC_ALL_CLOCK_DISABLE()                             (CODEC->ClockEnable.CLK_EN = 0x00000000)

/* Module reset */
#define __CODEC_ADC_RESET()                                     (CODEC->Reset.s.Rst_CDC_ADC = 1)
#define __CODEC_DAC_RESET()                                     (CODEC->Reset.s.Rst_CDC_DAC = 1)
#define __CODEC_I2S_TX_RESET()                                  (CODEC->Reset.s.Rst_I2STX = 1)
#define __CODEC_I2S_RX_RESET()                                  (CODEC->Reset.s.Rst_I2SRX = 1)
#define __CODEC_ADCFIFO_RESET()                              do{ CODEC->Reset.s.Rst_ADCFF_O = 1; \
                                                                 CODEC->Reset.s.Rst_ADCFF_I = 1; \
                                                                 CODEC->Reset.s.Rst_ADCFF   = 1; } while(0)
#define __CODEC_DACFIFO_LR_RESET()                           do{ CODEC->Reset.s.Rst_DACFFLR_O = 1; \
                                                                 CODEC->Reset.s.Rst_DACFFLR_I = 1; \
                                                                 CODEC->Reset.s.Rst_DACFFLR   = 1;} while(0)
#define __CODEC_DACFIFO_01_RESET()                           do{ CODEC->Reset.s.Rst_DACFF01_O = 1; \
                                                                 CODEC->Reset.s.Rst_DACFF01_I = 1; \
                                                                 CODEC->Reset.s.Rst_DACFF01   = 1;} while(0)
#define __CODEC_ASRC0_RESET()                                   (CODEC->Reset.s.Rst_ASRC0 = 1)
#define __CODEC_ASRC1_RESET()                                   (CODEC->Reset.s.Rst_ASRC1 = 1)
#define __CODEC_GPF0_RESET()                                    (CODEC->Reset.s.Rst_GPF0 = 1)
#define __CODEC_GPF1_RESET()                                    (CODEC->Reset.s.Rst_GPF1 = 1)
#define __CODEC_ALC_RESET()                                     (CODEC->Reset.s.Rst_ALC = 1)
#define __CODEC_DRC_RESET()                                     (CODEC->Reset.s.Rst_DRC = 1)

#define __CODEC_SET_RESET(__RST__)                              (CODEC->Reset.RESET = __RST__)
#define __CODEC_ALL_MODULE_RESET()                              (CODEC->Reset.RESET = 0xFFFFFFFF)
#define __CODEC_GET_RESET_STATUS()                              (CODEC->Reset.RESET)

/* Module enable/disable */
#define __CODEC_ADC_ENABLE()                                    (CODEC->Enable.CDC_ADC = 1)
#define __CODEC_DAC_ENABLE()                                    (CODEC->Enable.CDC_DAC = 1)
#define __CODEC_I2S_TX_ENABLE()                                 (CODEC->Enable.I2STX   = 1)
#define __CODEC_I2S_RX_ENABLE()                                 (CODEC->Enable.I2SRX   = 1)
#define __CODEC_DAC_FIFO_LR_ENABLE()                            (CODEC->Enable.DACFFLR   = 1)
#define __CODEC_DAC_FIFO_01_ENABLE()                            (CODEC->Enable.DACFF01   = 1)
#define __CODEC_ASRC0_ENABLE()                                  (CODEC->Enable.ASRC0   = 1)
#define __CODEC_ASRC1_ENABLE()                                  (CODEC->Enable.ASRC1   = 1)
#define __CODEC_GPF0_ENABLE()                                   (CODEC->Enable.GPF0    = 1)
#define __CODEC_GPF1_ENABLE()                                   (CODEC->Enable.GPF1    = 1)
#define __CODEC_DRC_ENABLE()                                    (CODEC->Enable.DRC     = 1)
#define __CODEC_ALC_ENABLE()                                    (CODEC->Enable.ALC     = 1)
#define __CODEC_TXOUT_ENABLE()                                  (CODEC->Enable.CDC_TXOUT = 1)

#define __CODEC_ADC_DISABLE()                                   (CODEC->Enable.CDC_ADC = 0)
#define __CODEC_DAC_DISABLE()                                   (CODEC->Enable.CDC_DAC = 0)
#define __CODEC_I2S_TX_DISABLE()                                (CODEC->Enable.I2STX   = 0)
#define __CODEC_I2S_RX_DISABLE()                                (CODEC->Enable.I2SRX   = 0)
#define __CODEC_DAC_FIFO_LR_DISABLE()                           (CODEC->Enable.DACFFLR   = 0)
#define __CODEC_DAC_FIFO_01_DISABLE()                           (CODEC->Enable.DACFF01   = 0)
#define __CODEC_ASRC0_DISABLE()                                 (CODEC->Enable.ASRC0   = 0)
#define __CODEC_ASRC1_DISABLE()                                 (CODEC->Enable.ASRC1   = 0)
#define __CODEC_GPF0_DISABLE()                                  (CODEC->Enable.GPF0    = 0)
#define __CODEC_GPF1_DISABLE()                                  (CODEC->Enable.GPF1    = 0)
#define __CODEC_DRC_DISABLE()                                   (CODEC->Enable.DRC     = 0)
#define __CODEC_ALC_DISABLE()                                   (CODEC->Enable.ALC     = 0)
#define __CODEC_TXOUT_DISABLE()                                 (CODEC->Enable.CDC_TXOUT = 0)

#define __CODEC_ALL_DISABLE()                                   (*(volatile uint32_t *)&CODEC->Enable = 0)

/* Set audio pll GPF    divider */
/* Set audio pll ASRC   divider */
/* Set audio pll SAMPLE divider */
#define __CODEC_SET_AUPLL_DIV_GPF(__DIV__)                      (CODEC->AudioPLLPrediv.AUPLL_DIV_GPF    = __DIV__ - 1)
#define __CODEC_SET_AUPLL_DIV_ASRC(__DIV__)                     (CODEC->AudioPLLPrediv.AUPLL_DIV_ASRC   = __DIV__ - 1)
#define __CODEC_SET_AUPLL_DIV_SAMPLE(__DIV__)                   (CODEC->AudioPLLPrediv.AUPLL_DIV_SAMPLE = __DIV__ - 1)

/* Set system pll GPF  divider */
/* Set system pll ASRC divider */
#define __CODEC_SET_SYSTEM_PLL_DIV_GPF(__DIV__)                 (CODEC->SystemPLLPrediv.SPLL_DIV_GPF  = __DIV__)
#define __CODEC_SET_SYSTEM_PLL_DIV_ASRC(__DIV__)                (CODEC->SystemPLLPrediv.SPLL_DIV_ASRC = __DIV__)

#define __CODEC_MCLK_ENABLE()                                   (CODEC->MCLKCfg.EN = 1)
#define __CODEC_MCLK_DISABLE()                                  (CODEC->MCLKCfg.EN = 0)
#define __CODEC_MCLK_SOURCE_SELECT(__SELECT__)                  (CODEC->MCLKCfg.MCLK_SRC = __SELECT__)
#define __CODEC_MCLK_DIV_TYPE(__TYPE__)                         (CODEC->MCLKCfg.DIV_TYPE = __TYPE__)
#define __CODEC_MCLK_DIV(__DIV__)                               (CODEC->MCLKCfg.DIV = __DIV__)

/* Set codec ADC/DAC volume */
#define __CODEC_SET_ADC_VOLUME(__VOLUME__)                      (CODEC->AdcVolume.VOLUME = __VOLUME__)
#define __CODEC_SET_DAC_VOLUME(__VOLUME__)                      (CODEC->DacVolume.VOLUME = __VOLUME__)

/* FIFO shot mode enable/disable */
#define __CODEC_ADCFF_SHOT_MODE_ENABLE()                        (CODEC->FifoOpMode.ADCFF = 1)
#define __CODEC_ADCFF_SHOT_MODE_DISABLE()                       (CODEC->FifoOpMode.ADCFF = 0)
#define __CODEC_DACFF_LR_SHOT_MODE_ENABLE()                     (CODEC->FifoOpMode.DACFFLR = 1)
#define __CODEC_DACFF_LR_SHOT_MODE_DISABLE()                    (CODEC->FifoOpMode.DACFFLR = 0)
#define __CODEC_DACFF_01_SHOT_MODE_ENABLE()                     (CODEC->FifoOpMode.DACFF01 = 1)
#define __CODEC_DACFF_01_SHOT_MODE_DISABLE()                    (CODEC->FifoOpMode.DACFF01 = 0)
/* FIFO threshold config */
#define __CODEC_ADCFF_L_FULL_THRESHOLD(__THRE__)                (CODEC->FifoADCThd.LEFT_F  = __THRE__)
#define __CODEC_ADCFF_R_FULL_THRESHOLD(__THRE__)                (CODEC->FifoADCThd.RIGHT_F = __THRE__)
#define __CODEC_DACFF_L_EMPTY_THRESHOLD(__THRE__)               (CODEC->FifoDACThd.FFLR_LEFT_E  = __THRE__)
#define __CODEC_DACFF_R_EMPTY_THRESHOLD(__THRE__)               (CODEC->FifoDACThd.FFLR_RIGHT_E = __THRE__)
#define __CODEC_DACFF_0_EMPTY_THRESHOLD(__THRE__)               (CODEC->FifoDACThd.FF01_LEFT_E  = __THRE__)
#define __CODEC_DACFF_1_EMPTY_THRESHOLD(__THRE__)               (CODEC->FifoDACThd.FF01_RIGHT_E = __THRE__)
/* Read/Write FIFO */
#define __CODEC_ADCFF_L_READ()                                  (CODEC->ADCDataL)
#define __CODEC_ADCFF_R_READ()                                  (CODEC->ADCDataR)
#define __CODEC_DACFF_L_WRITE(__DATA__)                         (CODEC->DACLRDataL = __DATA__)
#define __CODEC_DACFF_R_WRITE(__DATA__)                         (CODEC->DACLRDataR = __DATA__)
#define __CODEC_DACFF_0_WRITE(__DATA__)                         (CODEC->DAC01DataL = __DATA__)
#define __CODEC_DACFF_1_WRITE(__DATA__)                         (CODEC->DAC01DataL = __DATA__)

/* Codec input select ADC */
/* Codec input select I2S RX */
#define __CODEC_INPUT_SELECT_ADC()                              (CODEC->CodecRoute.ADC_SEL = 0)
#define __CODEC_INPUT_SELECT_I2S_RX()                           (CODEC->CodecRoute.ADC_SEL = 1)

/* Codec output select DAC */
/* Codec output select I2S TX */
#define __CODEC_OUTPUT_SELECT_DAC()                             (CODEC->CodecRoute.DAC_SEL = 0)
#define __CODEC_OUTPUT_SELECT_I2S_TX()                          (CODEC->CodecRoute.DAC_SEL = 1)

#define __CODEC_ADCFF_L_SRC_SET_PATH()                          (CODEC->FFRoute.ADCFF_R_SRC = 0)
#define __CODEC_ADCFF_R_SRC_SET_PATH()                          (CODEC->FFRoute.ADCFF_L_SRC = 0)

/* ADC FIFO data width */
/* DAC left/right FIFO data width */
/* DAC 0/1 FIFO data width */
#define __CODEC_ADCFF_DATA_WIDTH(__WIDTH__)                     (CODEC->FFRoute.ADCFF_BITWD    = __WIDTH__)
#define __CODEC_DACFF_LR_DATA_WIDTH(__WIDTH__)                  (CODEC->FFRoute.DACFF_LR_BITWD = __WIDTH__)
#define __CODEC_DACFF_01_DATA_WIDTH(__WIDTH__)                  (CODEC->FFRoute.DACFF_01_BITWD = __WIDTH__)

/* ASRC0 source select */
/* ASRC1 source select */
#define __CODEC_ASRC0_SOURCE_SELECT(__SELECT__)                 (CODEC->ASRCRoute.ASRC0_SRC = __SELECT__)
#define __CODEC_ASRC1_SOURCE_SELECT(__SELECT__)                 (CODEC->ASRCRoute.ASRC1_SRC = __SELECT__)

/* GPF0 channel 0 source select */
/* GPF0 channel 1 source select */
#define __CODEC_GPF0_CH0_SOURCE_SELECT(__SELECT__)              (CODEC->GPF0Route.CH0_SRC = __SELECT__)
#define __CODEC_GPF0_CH1_SOURCE_SELECT(__SELECT__)              (CODEC->GPF0Route.CH1_SRC = __SELECT__)
/* GPF1 channel 0 source select */
/* GPF1 channel 1 source select */
#define __CODEC_GPF1_CH0_SOURCE_SELECT(__SELECT__)              (CODEC->GPF1Route.CH0_SRC = __SELECT__)
#define __CODEC_GPF1_CH1_SOURCE_SELECT(__SELECT__)              (CODEC->GPF1Route.CH1_SRC = __SELECT__)

/* interrupt status enable */
/* interrupt status disable */
#define __CODEC_INT_STATUS_ENABLE(__STATUS__)                   (CODEC->CodecIntEn.STATUS |= (__STATUS__))
#define __CODEC_INT_STATUS_DISABLE(__STATUS__)                  (CODEC->CodecIntEn.STATUS &= ~(__STATUS__))
/* interrupt status get */
#define __CODEC_GET_INT_STATUS()                                (CODEC->CodecIntRawStatus.STATUS)
/* interrupt status clear */
#define __CODEC_CLR_INT_STATUS(__STATUS__)                      (CODEC->CodecIntClear.STATUS |= __STATUS__)

#define __CODEC_ASRC0_BYPASS()                                  (CODEC->ASRC[0].SysCfg.BYPASS = 1)
#define __CODEC_GPF0_BYPASS()                                   (CODEC->GPF[0].SysCfg.BYPASS = 1)
#define __CODEC_ALC_BYPASS()                                    (CODEC->ALC[0].SysCfg.BYPASS = 1)

#define __CODEC_ASRC1_BYPASS()                                  (CODEC->ASRC[1].SysCfg.BYPASS = 1)
#define __CODEC_GPF1_BYPASS()                                   (CODEC->GPF[1].SysCfg.BYPASS = 1)
#define __CODEC_DRC_BYPASS()                                    (CODEC->ALC[1].SysCfg.BYPASS = 1)

/* Exported functions ---------------------------------------------------------*/

void codec_init(CODEC_HandleTypeDef *hcodec);
void codec_deinit(CODEC_HandleTypeDef *hcodec);

/* set ADC/DAC volume */
void codec_Set_ADC_Volume(uint32_t fu32_Volume);
void codec_Set_DAC_Volume(uint32_t fu32_Volume);

/* int status enable/disable/clear */
void codec_int_enable(enum_Codec_INT_Status_t fe_Int_Status);
void codec_int_disable(enum_Codec_INT_Status_t fe_Int_Status);
void codec_init_clear(enum_Codec_INT_Status_t fe_Int_Status);
enum_Codec_INT_Status_t codec_get_int_status(void);

/* read adc fifo */
void codec_read_adc_fifo_left(void *fp_buffer, uint32_t fu32_length);
void codec_read_adc_fifo_right(void *fp_buffer, uint32_t fu32_length);
void codec_read_adc_fifo_left_right(void *fp_buffer, uint32_t fu32_length);
/* write dac LF fifo */
void codec_write_dac_fifo_left(void *fp_buffer, uint32_t fu32_length);
void codec_write_dac_fifo_right(void *fp_buffer, uint32_t fu32_length);
void codec_write_dac_fifo_left_right(void *fp_buffer, uint32_t fu32_length);
/* write dac 01 fifo */
void codec_write_dac_fifo_0(void *fp_buffer, uint32_t fu32_length);
void codec_write_dac_fifo_1(void *fp_buffer, uint32_t fu32_length);
void codec_write_dac_fifo_01(void *fp_buffer, uint32_t fu32_length);

/* mute */
void codec_mute_output(bool fb_mute);

#endif  // __DRIVER_CODEC_H__
