#ifndef DRIVER_ADC
#define DRIVER_ADC

#include "Ifx_Types.h"
#include "IfxVadc.h"
#include "IfxVadc_Adc.h"

typedef struct
{
    IfxVadc_Adc vadc; /* VADC handle */
    IfxVadc_Adc_Group adcGroup;
} App_VadcAutoScan;

IFX_EXTERN App_VadcAutoScan g_VadcAutoScan;

extern void Driver_Adc_Init(void);
extern void Driver_Adc0_ConvStart(void);
extern uint32_t Driver_Adc0_DataObtain(void);
// 실습 2번
extern void Driver_Adc1_Init(void);
extern void Driver_Adc1_ConvStart(void);
extern uint32_t Driver_Adc1_DataObtain(void);

#endif /* DRIVER_STM */
