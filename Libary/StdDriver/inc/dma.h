/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dma.h
* @brief   This file implements device driver for DTC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef DMA_H
#define DMA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Bit Position of DMACR
*/
#define SZ_Pos       6
#define RPTINT_Pos   5
#define CHNE_Pos     4
#define DAMOD_Pos    3
#define SAMOD_Pos    2
#define RPTSEL_Pos   1
#define MODE_Pos     0

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
   DMA_VECTOR_0                 =  0U,
   DMA_VECTOR_1	                =  1U,
   DMA_VECTOR_2	                =  2U,
   DMA_VECTOR_3	                =  3U,
   DMA_VECTOR_4	                =  4U,
   DMA_VECTOR_5	                =  5U,
   DMA_VECTOR_6	                =  6U,
   DMA_VECTOR_7	                =  7U,
   DMA_VECTOR_8	                =  8U,
   DMA_VECTOR_9                 =  9U,
   DMA_VECTOR_10                = 10U,
   DMA_VECTOR_11                = 11U,
   DMA_VECTOR_12                = 12U,
   DMA_VECTOR_13                = 13U,
   DMA_VECTOR_14                = 14U,
   DMA_VECTOR_15                = 15U,

} dma_vector_t;

typedef enum {
	DMA_SIZE_BYTE, 				/*  8bits transfer */ 
	DMA_SIZE_HALF,  			/* 16bits transfer */
	DMA_SIZE_WORD   			/* 32bits transfer */
} dma_size_t;

typedef enum {
	DMA_MODE_NORMAL, 			/* Normal mode */ 
	DMA_MODE_REPEAT   			/* Repeat mode */
} dma_mode_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#if 1
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, dma_mode_t mode, dma_size_t size, uint16_t count, void *src_adr, void *dst_adr);
#else
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, DMAVEC_CTRL_Type ctrl_data);
#endif
void DMA_Enable(dma_vector_t vect_num);
void DMA_Stop(dma_vector_t vect_num);
void DMA_Trigger(dma_vector_t vect_num);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
