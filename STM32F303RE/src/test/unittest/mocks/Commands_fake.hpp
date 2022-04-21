#include "STM32F303RE.h"
#include "onChip.h"
#include "fakeit.hpp"

using namespace fakeit;

struct Commands 
{
   virtual onChip_Status CmdTest(uint8_t tableEntry, uint8_t *pInBuf, onChip_Rsp *pOutRsp) = 0;   
};

extern Mock<Commands> Commands_mock;

onChip_Status Test0(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test1(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test2(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test3(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test4(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test5(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test6(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test7(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test8(uint8_t *pInBuf, onChip_Rsp *pOutRsp);
onChip_Status Test9(uint8_t *pInBuf, onChip_Rsp *pOutRsp);