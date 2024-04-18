#ifndef __APP_CMP_H
#define __APP_CMP_H
#include "BAT32G439.h"
void ACMP0_Config(void);
void ACMP1_Config(void);
void ACMP2_Config(void);
void ACMP3_Config(void);
void DAC0_Init(uint16_t vol);//mv
void DAC1_Init(uint16_t vol);//mv

#define CMP_ENABLE_CTRL_Pos (0u)
#define CMP_CMPSEL_Pos      (6u)
#define CMP_CREFS0_Pos      (0u)
#define CMP_C0OTWMD_Pos     (7u)
#define CMP_OUT_PHASE_Pos   (2u)
#define CMP_OUT_CTRL_Pos    (1u)
#define CMP_INT_CTRL_Pos    (0u)
#define CMP_EDGE_CTRL_Pos   (2u)
#define CMP_FILTER_CTRL_Pos (0u)
#define CMP_HY_VALUE_Pos    (4u)
#define CMP_HY_MODE_Pos     (0u)

#define CMP0_CMPSEL_PA00    (0 << CMP_CMPSEL_Pos)
#define CMP0_CMPSEL_PGA00   (1 <<   )
#define CMP0_CMPSEL_PA04    (2 << CMP_CMPSEL_Pos)
#define CMP0_CMPSEL_PGA11   (3 << CMP_CMPSEL_Pos)

#define CMP0_CREFS0_PB08    (0 << CMP_CREFS0_Pos)
#define CMP0_CREFS0_PB05    (1 << CMP_CREFS0_Pos)
#define CMP0_CREFS0_DAC0    (2 << CMP_CREFS0_Pos)
#define CMP0_CREFS0_DAC1    (3 << CMP_CREFS0_Pos)

#define CMP1_CMPSEL_PA03    (0 << CMP_CMPSEL_Pos)
#define CMP1_CMPSEL_PGA10   (1 << CMP_CMPSEL_Pos)
#define CMP1_CMPSEL_PA05    (2 << CMP_CMPSEL_Pos)
#define CMP1_CMPSEL_PGA12   (3 << CMP_CMPSEL_Pos)

#define CMP1_CREFS0_PB08    (0 << CMP_CREFS0_Pos)
#define CMP1_CREFS0_PB05    (1 << CMP_CREFS0_Pos)
#define CMP1_CREFS0_DAC0    (2 << CMP_CREFS0_Pos)
#define CMP1_CREFS0_DAC1    (3 << CMP_CREFS0_Pos)

#define CMP2_CMPSEL_PA04    (0 << CMP_CMPSEL_Pos)
#define CMP2_CMPSEL_PGA11   (1 << CMP_CMPSEL_Pos)
#define CMP2_CMPSEL_PA00    (2 << CMP_CMPSEL_Pos)
#define CMP2_CMPSEL_PGA00   (3 << CMP_CMPSEL_Pos)

#define CMP2_CREFS0_PB08    (0 << CMP_CREFS0_Pos)
#define CMP2_CREFS0_PB05    (1 << CMP_CREFS0_Pos)
#define CMP2_CREFS0_DAC0    (2 << CMP_CREFS0_Pos)
#define CMP2_CREFS0_DAC1    (3 << CMP_CREFS0_Pos)

#define CMP3_CMPSEL_PA05    (0 << CMP_CMPSEL_Pos)
#define CMP3_CMPSEL_PGA12   (1 << CMP_CMPSEL_Pos)
#define CMP3_CMPSEL_PA03    (2 << CMP_CMPSEL_Pos)
#define CMP3_CMPSEL_PGA10   (3 << CMP_CMPSEL_Pos)

#define CMP3_CREFS0_PB08    (0 << CMP_CREFS0_Pos)
#define CMP3_CREFS0_PB05    (1 << CMP_CREFS0_Pos)
#define CMP3_CREFS0_DAC0    (2 << CMP_CREFS0_Pos)
#define CMP3_CREFS0_DAC1    (3 << CMP_CREFS0_Pos)

#define CMP1_C0OTWMD_EN     (1 << CMP_C0OTWMD_Pos)
#define CMP1_C0OTWMD_Dis    (0 << CMP_C0OTWMD_Pos)

#define CMP_OUT_PHASE_Normal   	(0 << CMP_OUT_PHASE_Pos)
#define CMP_OUT_PHASE_Reverse   (1 << CMP_OUT_PHASE_Pos)
#define CMP_OUT_PIN_Enable      (1 << CMP_OUT_CTRL_Pos)
#define CMP_OUT_PIN_Disable     (0 << CMP_OUT_CTRL_Pos)
#define CMP_INT_Disable         (0 << CMP_INT_CTRL_Pos)
#define CMP_INT_Enable          (1 << CMP_INT_CTRL_Pos)

#define CMP_EDGE_UP         		(0 << CMP_EDGE_CTRL_Pos)
#define CMP_EDGE_DN      				(1 << CMP_EDGE_CTRL_Pos)
#define CMP_EDGE_UP_DN     			(2 << CMP_EDGE_CTRL_Pos)

#define CMP_FILTER_NONE         (0 << CMP_FILTER_CTRL_Pos)
#define CMP_FILTER_FCLK         (1 << CMP_FILTER_CTRL_Pos)
#define CMP_FILTER_FCLK_8       (2 << CMP_FILTER_CTRL_Pos)
#define CMP_FILTER_FCLK_32      (3 << CMP_FILTER_CTRL_Pos)

#define CMP_HY_VALUE_0       		(0 << CMP_HY_VALUE_Pos)
#define CMP_HY_VALUE_20         (1 << CMP_HY_VALUE_Pos)
#define CMP_HY_VALUE_40         (2 << CMP_HY_VALUE_Pos)
#define CMP_HY_VALUE_60         (3 << CMP_HY_VALUE_Pos)

#define CMP_HY_None             (0 << CMP_HY_MODE_Pos)
#define CMP_HY_Positive         (1 << CMP_HY_MODE_Pos)
#define CMP_HY_Negitive         (2 << CMP_HY_MODE_Pos)
#define CMP_HY_Bilateral        (3 << CMP_HY_MODE_Pos)

#define CMP_START               (1 << CMP_ENABLE_CTRL_Pos)
#define CMP_STOP                (0 << CMP_ENABLE_CTRL_Pos)
#endif
