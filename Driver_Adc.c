#include "Driver_Adc.h"

static void Driver_Adc0_Init(void);
static void Driver_Adc1_Init(void);

App_VadcAutoScan g_VadcAutoScan;
IfxVadc_Adc_ChannelConfig adcChannelConfig[8];
IfxVadc_Adc_Channel   adcChannel[8];
uint32_t adcDataResult[8] = {0u,};

// A0 ADCL.1 SAR4.7/P32.3 group 4에 7번 채널
static void Driver_Adc0_Init(void)
{
    uint32_t    chnIx = 7;

    // 구조체 선언 및 변수 초기화
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    // 모듈 초기화
    IfxVadc_Adc_initModule(&g_VadcAutoScan.vadc, &adcConfig);

    // 그룹 변수 선언 및 초기화
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcAutoScan.vadc);

    // 그룹 4 사용 설정
    adcGroupConfig.groupId = IfxVadc_GroupId_4;
    adcGroupConfig.master = adcGroupConfig.groupId;
    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;
    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;
    adcGroupConfig.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;
    IfxVadc_Adc_initGroup(&g_VadcAutoScan.adcGroup, &adcGroupConfig);
    IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &g_VadcAutoScan.adcGroup);
    adcChannelConfig[chnIx].channelId       = (IfxVadc_ChannelId)(chnIx);
    adcChannelConfig[chnIx].resultRegister  = (IfxVadc_ChannelResult)(chnIx);

    IfxVadc_Adc_initChannel(&adcChannel[chnIx], &adcChannelConfig[chnIx]);

    unsigned channels   = (1 << adcChannelConfig[chnIx].channelId);
    unsigned mask       = channels;
    IfxVadc_Adc_setScan(&g_VadcAutoScan.adcGroup, channels, mask);
}

void Driver_Adc_Init(void)
{
    /*ADC0 Converter Init*/
    Driver_Adc0_Init();

    /*ADC0 Converter Start*/
    Driver_Adc0_ConvStart();
    //실습 2번
//    Driver_Adc1_Init();
//    Driver_Adc0_ConvStart();
}

void Driver_Adc0_ConvStart(void)
{
    IfxVadc_Adc_startScan(&g_VadcAutoScan.adcGroup);
}


uint32_t Driver_Adc0_DataObtain(void)
{
    uint32_t    chnIx = 7;
    Ifx_VADC_RES conversionResult;
    do
    {
        conversionResult = IfxVadc_Adc_getResult(&adcChannel[chnIx]);
    } while(!conversionResult.B.VF);
    adcDataResult[chnIx] = conversionResult.B.RESULT;
    return adcDataResult[chnIx];
}

//실습 2번
// A1 ADCL.2 SAR4.6/P32.4 group 4에 6번 채널, G4CH6, AN38, P40.8 (X)
void Driver_Adc1_Init(void)
{
    uint32_t    chnIx = 6;

    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    IfxVadc_Adc_initModule(&g_VadcAutoScan.vadc, &adcConfig);

    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcAutoScan.vadc);

    adcGroupConfig.groupId = IfxVadc_GroupId_4;
    adcGroupConfig.master = adcGroupConfig.groupId;
    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;
    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;
    adcGroupConfig.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;
    IfxVadc_Adc_initGroup(&g_VadcAutoScan.adcGroup, &adcGroupConfig);
    IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &g_VadcAutoScan.adcGroup);
    adcChannelConfig[chnIx].channelId       = (IfxVadc_ChannelId)(chnIx);
    adcChannelConfig[chnIx].resultRegister  = (IfxVadc_ChannelResult)(chnIx);

    IfxVadc_Adc_initChannel(&adcChannel[chnIx], &adcChannelConfig[chnIx]);

    unsigned channels   = (1 << adcChannelConfig[chnIx].channelId);
    unsigned mask       = channels;
    IfxVadc_Adc_setScan(&g_VadcAutoScan.adcGroup, channels, mask);
}

void Driver_Adc1_ConvStart(void)
{
    IfxVadc_Adc_startScan(&g_VadcAutoScan.adcGroup);
}


uint32_t Driver_Adc1_DataObtain(void)
{
    uint32_t    chnIx = 6;
    Ifx_VADC_RES conversionResult;
    do
    {
        conversionResult = IfxVadc_Adc_getResult(&adcChannel[chnIx]);
    } while(!conversionResult.B.VF);
    adcDataResult[chnIx] = conversionResult.B.RESULT;
    return adcDataResult[chnIx];
}
