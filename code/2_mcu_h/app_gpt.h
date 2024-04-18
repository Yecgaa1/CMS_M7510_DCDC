#ifndef __APP_GPT_H__
#define __APP_GPT_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "BAT32G439.h"
typedef struct stc_PwmDtCalc{
    int16_t i16cycleCfg;
    int16_t i16cycleCfg_G;
    int16_t i16cycleCfgHalf;
    int16_t i16Duty;
    int16_t i16Duty_Old;
    int16_t i16lTimeCfg;
    int16_t i16dTimeCfg;
    int16_t i16a_on;
    int16_t i16b_on;
    int16_t i16c_on;
    int16_t i16d_on;
}stc_pwmdt_calc_t;
extern stc_pwmdt_calc_t M1_stcPwmDtCalc;
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
#define  GTP_BASE           (0x40090000)

#define  GPT00              (0)
#define  GPT01              (1)
#define  GPT02              (2)
#define  GPT03              (3)
#define  GPT10              (4)
#define  GPT11              (5)
#define  GPT12              (6)
#define  GPT13              (7)
#define  GPT14              (8)
#define  GPT15              (9)
#define  GPT16             (10)
#define  GPT17             (11)

							
/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/
typedef struct {
    __IO uint32_t GTWP;        /*0x0000, 0x00000000  */
    __IO uint32_t GTSTR;       /*0x0004, 0x00000000  */
    __IO uint32_t GTSTP;       /*0x0008, 0xFFFFFFFF  */
    __IO uint32_t GTCLR;       /*0x000C, 0x00000000  */
    __IO uint32_t GTSSR;       /*0x0010, 0x00000000  */
    __IO uint32_t GTPSR;       /*0x0014, 0x00000000  */
    __IO uint32_t GTCSR;       /*0x0018, 0x00000000  */
    __IO uint32_t GTUPSR;      /*0x001C, 0x00000000  */
    __IO uint32_t GTDNSR;      /*0x0020, 0x00000000  */
    __IO uint32_t GTICASR;     /*0x0024, 0x00000000  */
    __IO uint32_t GTICBSR;     /*0x0028, 0x00000000  */  
    __IO uint32_t GTCR;        /*0x002C, 0x00000000  */
    __IO uint32_t GTUDDTYC;    /*0x0030, 0x00000000  */
    __IO uint32_t GTIOR;       /*0x0034, 0x00000000  */ 
    __IO uint32_t GTINTAD;     /*0x0038, 0x00000000  */
    __IO uint32_t GTST;        /*0x003C, 0x00008000  */
    __IO uint32_t GTBER;       /*0x0040, 0x00000000  */
    __IO uint32_t GTCNT;       /*0x0048, 0x00000000  */
    __IO uint32_t GTCCRA;      /*0x004C, 0xFFFFFFFF  */
    __IO uint32_t GTCCRB;      /*0x0050, 0xFFFFFFFF  */ 
    __IO uint32_t GTCCRC;      /*0x0054, 0xFFFFFFFF  */ 
    __IO uint32_t GTCCRE;      /*0x0058, 0xFFFFFFFF  */
    __IO uint32_t GTCCRD;      /*0x005C, 0xFFFFFFFF  */
    __IO uint32_t GTCCRF;      /*0x0060, 0xFFFFFFFF  */
    __IO uint32_t GTPR;        /*0x0064, 0xFFFFFFFF  */
    __IO uint32_t GTPBR;       /*0x0068, 0xFFFFFFFF  */
    __I  uint32_t RES0[8];     /*0x006C~0x0084       */
    __IO uint32_t GTDTCR;      /*0x0088, 0x00000000  */
    __IO uint32_t GTDVU;       /*0x008C, 0xFFFFFFFF  */
    __I  uint32_t RES1[28];    /*0x0090~0x00FC       */
}GPT_REG_T;

typedef struct {
    GPT_REG_T  GPT[12];
}GPT_T;


#define GPT         ((GPT_REG_T *)GTP_BASE)
#define GPT_OPSCR   (*(__IO uint32_t *)0x4009BFF0)

//#define POEGGA      (*(__IO uint32_t *)0x40042000)
//#define POEGGB      (*(__IO uint32_t *)0x40042100)

#define GPT_MODE_Pos                    (16u)
#define GPT_MODE_Msk                    (0x07u)
#define GPT_CLK_PRE_Pos                 (24u)   
#define GPT_CLK_PRE_Msk                 (0x07u)
#define GPT_CNT_DIRECTION_Pos           (0u)
#define GPT_CNT_DIRECTION_Msk           (0x01u)
#define GPT_CNT_FORCE_DIRECTION_Pos     (1u)
#define GPT_CNT_FORCE_DIRECTION_Msk     (0x01u)
#define CPT_GTIOA_OUT_MD_Pos            (0u)
#define GPT_GTIOA_OUT_MD_Msk            (0x1fu)
#define GPT_GTIOA_OADFLT_Pos            (6u)
#define GPT_GTIOA_OADFLT_Msk            (0x01u)
#define GPT_GTIOA_OAHLD_Pos             (7u)
#define GPT_GTIOA_OAHLD_Msk             (0x01u)
#define GPT_GTIOA_OUT_EN_Pos            (8u)
#define GPT_GTIOA_OUT_EN_Msk            (0x01u)
#define GPT_GTIOA_OADF_Pos              (9u)
#define GPT_GTIOA_OADF_Msk              (0x03u)
#define GPT_GTIOA_FILTER_EN_Pos         (13u)
#define GPT_GTIOA_FILTER_EN_Msk         (0x01u)
#define GPT_GTIOA_FILTER_Pos            (14u)
#define GPT_GTIOA_FILTER_Msk            (0x03u)
#define CPT_GTIOB_OUT_MD_Pos            (16u)
#define GPT_GTIOB_OUT_MD_Msk            (0x1fu)
#define GPT_GTIOB_OBDFLT_Pos            (22u)
#define GPT_GTIOB_OBDFLT_Msk            (0x01u)
#define GPT_GTIOB_OBHLD_Pos             (23u)
#define GPT_GTIOB_OBHLD_Msk             (0x01u)
#define GPT_GTIOB_OUT_EN_Pos            (24u)
#define GPT_GTIOB_OUT_EN_Msk            (0x01u)
#define GPT_GTIOB_OBDF_Pos              (25u)
#define GPT_GTIOB_OBDF_Msk              (0x03u)
#define GPT_GTIOB_FILTER_EN_Pos         (29u)
#define GPT_GTIOB_FILTER_EN_Msk         (0x01u)
#define GPT_GTIOB_FILTER_Pos            (30u)
#define GPT_GTIOB_FILTER_Msk            (0x03u)
#define GPT_POEG_GRP_Pos                (24u)
#define GPT_POEG_GRP_Msk                (0x03u)
#define GPT_POEG_GRPMD_Pos              (29u)
#define GPT_POEG_GRPMD_Msk              (0x03u)
#define GPT_BUF_EN_Pos                  (0u)
#define GPT_BUF_EN_Msk                  (0x03u)
#define GPT_BUF_CCRA_MD_Pos             (16u)  
#define GPT_BUF_CCRA_MD_Msk             (0x03u)  
#define GPT_BUF_CCRB_MD_Pos             (18u)  
#define GPT_BUF_CCRB_MD_Msk             (0x03u)  
#define GPT_BUF_PR_MD_Pos               (20u)  
#define GPT_BUF_PR_MD_Msk               (0x03u) 
#define GPT_BUF_FORCE_Pos               (22u)
#define GPT_BUF_FORCE_Msk               (0x01u)
#define GPT_DEADTIME_EN_Pos             (0u)
#define GPT_DEADTIME_EN_Msk             (0x01u)
#define GPT_INT_SOURCE_Pos              (0u)
#define GPT_INT_SOURCE_Msk              (0xFFu)

#define GTUPSR_MODE_Pos                 (8u)
#define GTUPSR_MODE_Mask                (0xFFu)
#define GTDNSR_MODE_Pos                 (8u)
#define GTDNSR_MODE_Mask                (0xFFu)

#define GPT_MD_S_WAVE                       (0u << GPT_MODE_Pos)  //��ݲ�����˫����
#define GPT_MD_S_WAVE_ONE_SHOOT             (1u << GPT_MODE_Pos)  //���ξ�ݲ����̶�����
#define GPT_MD_TWAVE_ONE                    (4u << GPT_MODE_Pos)  //���ǲ�1�����ȴ���,��˫����
#define GPT_MD_TWAVE_TWO                    (5u << GPT_MODE_Pos)  //���ǲ�2�����Ȳ��崫��,��˫����
#define GPT_MD_TWAVE_THREE                  (6u << GPT_MODE_Pos)  //���ǲ�3�����ȴ���,�̶�����
//GPTʱ�ӷ�Ƶ 
#define GPT_CLK_PRE_1                       (0u << GPT_CLK_PRE_Pos) 
#define GPT_CLK_PRE_4                       (1u << GPT_CLK_PRE_Pos)   
#define GPT_CLK_PRE_16                      (2u << GPT_CLK_PRE_Pos)   
#define GPT_CLK_PRE_64                      (3u << GPT_CLK_PRE_Pos)   
#define GPT_CLK_PRE_256                     (4u << GPT_CLK_PRE_Pos)
#define GPT_CLK_PRE_1024                    (5u << GPT_CLK_PRE_Pos) 
#define GPT_CNT_DN                          (0u << GPT_CNT_DIRECTION_Pos) //���¼���
#define GPT_CNT_UP                          (1u << GPT_CNT_DIRECTION_Pos) //���ϼ���
#define GPT_CNT_DIRECT_FORCE                (1u << GPT_CNT_FORCE_DIRECTION_Pos)
#define GPT_OADFLT_LOW                      (0u << GPT_GTIOA_OADFLT_Pos) //ֹͣ���������
#define GPT_OADFLT_HIGH                     (1u << GPT_GTIOA_OADFLT_Pos) //ֹͣ���������
#define GPT_OAHLD_HOLD                      (1u << GPT_GTIOA_OADF_Pos)  //������ʼ/ֹͣ�����ƽ����
#define GPT_OAHLD_RESIGTR                   (0u << GPT_GTIOA_OADF_Pos) //������ʼ/ֹͣ�����ƽ��ѭ�Ĵ��� 
#define GPT_GTIOA_OUT_ENABLE                (1u << GPT_GTIOA_OUT_EN_Pos)//ʹ��A�����
#define GPT_GTIOB_OUT_ENABLE                (1u << GPT_GTIOB_OUT_EN_Pos)//ʹ��B�����
#define GTIO_OUT_INIT_HIGH                  (1u  << 4) //��ʼ�����
#define GTIO_OUT_INIT_LOW                   (0u  << 4) //��ʼ�����
#define GTIO_OUT_RETAIN_PERIOD              (0u  << 2) //���ڽ����������
#define GTIO_OUT_0_PERIOD                   (1u  << 2) //���ڽ��������0
#define GTIO_OUT_1_PERIOD                   (2u  << 2) //���ڽ��������1
#define GTIO_OUT_SW_PERIOD                  (3u  << 2) //���ڽ������л�
#define GTIO_OUT_RETAIN_COMPARE             (0u  << 0) //�Ƚ�ƥ��ʱ�������
#define GTIO_OUT_0_COMPARE                  (1u  << 0) //�Ƚ�ƥ��ʱ�����
#define GTIO_OUT_1_COMPARE                  (2u  << 0) //�Ƚ�ƥ��ʱ�����
#define GTIO_OUT_SW_COMPARE                 (3u  << 0) //�Ƚ�ƥ��ʱ����л�
#define GTIO_OADF_OUTPUT_DIS                (0u  << GPT_GTIOA_OADF_Pos)//A�˽�ֹ�����������
#define GTIO_OADF_OUTPUT_HIZ                (1u  << GPT_GTIOA_OADF_Pos)//A�˽�������󣬶˿ڸ���̬
#define GTIO_OADF_OUTPUT_0                  (2u  << GPT_GTIOA_OADF_Pos)//A�˽�������󣬶˿������
#define GTIO_OADF_OUTPUT_1                  (3u  << GPT_GTIOA_OADF_Pos)//A�˽�������󣬶˿������
#define GTIO_OBDF_OUTPUT_DIS                (0u  << GPT_GTIOB_OBDF_Pos)//B�˽�ֹ�����������
#define GTIO_OBDF_OUTPUT_HIZ                (1u  << GPT_GTIOB_OBDF_Pos)//B�˽�������󣬶˿ڸ���̬
#define GTIO_OBDF_OUTPUT_0                  (2u  << GPT_GTIOB_OBDF_Pos)//B�˽�������󣬶˿������
#define GTIO_OBDF_OUTPUT_1                  (3u  << GPT_GTIOB_OBDF_Pos)//B�˽�������󣬶˿������

#define GBER_BUF_A_NONE                     (0u  << GPT_BUF_CCRA_MD_Pos) //�Ƚ�ƥ��Ĵ���A�޻���
#define GBER_BUF_A_SINGLE                   (1u  << GPT_BUF_CCRA_MD_Pos) //�Ƚ�ƥ��Ĵ���A������GTCCRC
#define GBER_BUF_A_DOUBLE                   (2u  << GPT_BUF_CCRA_MD_Pos) //�Ƚ�ƥ��Ĵ���A˫����GTCCRC��GTCCRD
#define GBER_BUF_B_NONE                     (0u  << GPT_BUF_CCRB_MD_Pos) //�Ƚ�ƥ��Ĵ���B�޻���
#define GBER_BUF_B_SINGLE                   (1u  << GPT_BUF_CCRB_MD_Pos) //�Ƚ�ƥ��Ĵ���B������GTCCRE
#define GBER_BUF_B_DOUBLE                   (2u  << GPT_BUF_CCRB_MD_Pos) //�Ƚ�ƥ��Ĵ���B˫����GTCCRE��GTCCRF
#define GBER_BUF_AB_FORCE                   (1u  << GPT_BUF_FORCE_Pos) //ǿ������һ�λ��崫��
#define GBER_BUF_PERIOD_NONE                (0u  << GPT_BUF_PR_MD_Pos) //�����޻���
#define GBER_BUF_PERIOD_SIGNLE              (1u  << GPT_BUF_PR_MD_Pos) //���ڵ�����GTPBR
#define GBER_BUF_GTCCR_DISABLE              (1u  << GPT_BUF_EN_Pos) //���ñȽ�ƥ��Ĵ�������������
#define GBER_BUF_GTCCR_ENABLE               (0u  << GPT_BUF_EN_Pos) //���ñȽ�ƥ��Ĵ�������������
#define GBER_BUF_PR_ENABLE                  (0u  << GPT_BUF_EN_Pos) //�������ڼĴ�������������
#define GBER_BUF_PR_DISABLE                 (2u  << GPT_BUF_EN_Pos)//�������ڼĴ�������������
#define GTDCTR_DEADTIME_ENABLE              (1u  << GPT_DEADTIME_EN_Pos) //ʹ���Զ���������ʱ��

#define GTINTAD_POEG_GRP_A                   (0u  << GPT_POEG_GRP_Pos) //ѡ��POEGA������������
#define GTINTAD_POEG_GRP_B                   (1u  << GPT_POEG_GRP_Pos) //ѡ��POEGB������������
#define GTINTAD_POEG_GRP_C                   (2u  << GPT_POEG_GRP_Pos) //ѡ��POEGC������������
#define GTINTAD_POEG_GRP_D                   (3u  << GPT_POEG_GRP_Pos) //ѡ��POEGD������������
#define GTINTAD_POEG_MD_GRPABH               (1u  << GPT_POEG_GRPMD_Pos)  //AB��ͬʱ�����ߵ�ƽ�����ɽ����������
#define GTINTAD_POEG_MD_GRPABL               (2u  << GPT_POEG_GRPMD_Pos)  //AB��ͬʱ�����͵�ƽ�����ɽ����������

#define GTINTAD_INT_GTCCRA                   (1u  <<  0)//GTCCRA INT
#define GTINTAD_INT_GTCCRB                   (1u  <<  1)//GTCCRB INT
#define GTINTAD_INT_GTCCRC                   (1u  <<  2)//GTCCRC INT
#define GTINTAD_INT_GTCCRD                   (1u  <<  3)//GTCCRD INT
#define GTINTAD_INT_GTCCRE                   (1u  <<  4)//GTCCRE INT
#define GTINTAD_INT_GTCCRF                   (1u  <<  5)//GTCCRF INT
#define GTINTAD_INT_UP_FLOW                  (1u  <<  6)//cnt up flow INT
#define GTINTAD_INT_DN_FLOW                  (2u  <<  6)//cnt dn flow INT
#define GTINTAD_INT_UPDN_FLOW                (3u  <<  6)//cnt up and dn flow INT

#define POEG_SOFT_ENABLE_Pos                 (3u) 
#define POEG_GTETRG_ENABLE_Pos               (4u) 
#define POEG_GPT_ENABLE_Pos                  (5u) 
#define POEG_OSC_STOP_ENABLE_Pos             (6u)
#define POEG_CMP_ENABLE_Pos                  (8u)
#define POEG_GTETRG_INVERTED_Pos             (28u)
#define POEG_NFEN_ENABLE_Pos                 (29u)

#define POEG_SOFT_ENABLE                     (1 << POEG_SOFT_ENABLE_Pos)  //ʹ���������GPT�������
#define POEG_GTETRG_ENABLE                   (1 << POEG_GTETRG_ENABLE_Pos)//ʹ��GTETRG���Ž���GPT�������
#define POEG_GPT_ENABLE                      (1 << POEG_GPT_ENABLE_Pos)   //ʹ��GPT��������GPT�������
#define POEG_OSC_STOP_ENABLE                 (1 << POEG_OSC_STOP_ENABLE_Pos)//ʹ��ʱ��ͣ���������GPT�������
#define POEG_CMP0_ENABLE                     (1 << POEG_CMP_ENABLE_Pos)//
#define POEG_CMP1_ENABLE                     (2 << POEG_CMP_ENABLE_Pos)//
#define POEG_CMP2_ENABLE                     (4 << POEG_CMP_ENABLE_Pos)//
#define POEG_CMP3_ENABLE                     (8 << POEG_CMP_ENABLE_Pos)//
#define POEG_GTETRG_INVERTED_ENABLE          (1 << POEG_GTETRG_INVERTED_Pos)//ʹ��GTETRG���뷴ת
#define POEG_NFEN_ENABLE                     (1 << POEG_NFEN_ENABLE_Pos)//ʹ��POEG�˲�
#define POEG_FILTER_CLK                      (0 << 30)//PCLK  
#define POEG_FILTER_CLK_8                    (1 << 30)//PCLK/8
#define POEG_FILTER_CLK_32                   (2 << 30)//PCLK/32
#define POEG_FILTER_CLK_128                  (3 << 30)//PCLK/128  

#define POEG_GTETRG_FLG_Msk                  (1 << 0)
#define POEG_GPT_FLG_Msk                     (1 << 1)
#define POEG_OSC_STOP_FLG_Msk                (1 << 2)

#define GTUPSR_MODE_USCARBL                  (0x01 << GTUPSR_MODE_Pos)//B��Ϊ�ͣ�A�������ص���
#define GTUPSR_MODE_USCARBH                  (0x02 << GTUPSR_MODE_Pos)//B��Ϊ�ߣ�A�������ص���
#define GTUPSR_MODE_USCAFBL                  (0x04 << GTUPSR_MODE_Pos)//B��Ϊ�ͣ�A���½��ص���
#define GTUPSR_MODE_USCAFBH                  (0x08 << GTUPSR_MODE_Pos)//B��Ϊ�ߣ�A���½��ص���
#define GTUPSR_MODE_USCBRAL                  (0x10 << GTUPSR_MODE_Pos)//A��Ϊ�ͣ�B�������ص���
#define GTUPSR_MODE_USCBRAH                  (0x20 << GTUPSR_MODE_Pos)//A��Ϊ�ߣ�B�������ص���
#define GTUPSR_MODE_USCBFAL                  (0x40 << GTUPSR_MODE_Pos)//A��Ϊ�ͣ�B���½��ص���
#define GTUPSR_MODE_USCBFAH                  (0x80 << GTUPSR_MODE_Pos)//A��Ϊ�ߣ�B���½��ص���

#define GTDNSR_MODE_DSCARBL                  (0x01 << GTDNSR_MODE_Pos)//B��Ϊ�ͣ�A�������صݼ�
#define GTDNSR_MODE_DSCARBH                  (0x02 << GTDNSR_MODE_Pos)//B��Ϊ�ߣ�A�������صݼ�
#define GTDNSR_MODE_DSCAFBL                  (0x04 << GTDNSR_MODE_Pos)//B��Ϊ�ͣ�A���½��صݼ�
#define GTDNSR_MODE_DSCAFBH                  (0x08 << GTDNSR_MODE_Pos)//B��Ϊ�ߣ�A���½��صݼ�
#define GTDNSR_MODE_DSCBRAL                  (0x10 << GTDNSR_MODE_Pos)//A��Ϊ�ͣ�B�������صݼ�
#define GTDNSR_MODE_DSCBRAH                  (0x20 << GTDNSR_MODE_Pos)//A��Ϊ�ߣ�B�������صݼ�
#define GTDNSR_MODE_DSCBFAL                  (0x40 << GTDNSR_MODE_Pos)//A��Ϊ�ͣ�B���½��صݼ�
#define GTDNSR_MODE_DSCBFAH                  (0x80 << GTDNSR_MODE_Pos)//A��Ϊ�ߣ�B���½��صݼ�
/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************/
/* local inline function declarations */
/*****************************************************************************/




/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
void Motor1_EnableEPWM(void);
void Motor1_DisableEPWM(void);
void Motor1_ConfigEPWM(void);
void Motor1_ChgFrqEPWM(void);
void Motor1_SetADCTrig(void);
void Motor1_Timer_Run(void);
void Motor1_UpdateEPWM(int16_t a_on,int16_t b_on); 
#endif /* __APP_GPT_H__ */

