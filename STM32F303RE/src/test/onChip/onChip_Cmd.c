#include "onChip_Cmd.h"

onChip_Cmd_Entry CmdTable[10] = \
{
    //Group     Id      Function
    { 0x00,     0x00,   Test   },
    { 0x00,     0x01,   Test   },
    { 0x00,     0x02,   Test   },
    { 0x00,     0x03,   Test   },
    { 0x00,     0x04,   Test   },
    { 0x00,     0x05,   Test   },
    { 0x00,     0x06,   Test   },
    { 0x00,     0x07,   Test   },
    { 0x00,     0x08,   Test   },
    { 0x00,     0x09,   Test   }
};

onChip_Status Test(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    switch (*pInBuf)
    {
        case 0x1A:
            pOutRsp->data[0] = 0xAA;
            pOutRsp->length = 1;
            return ONCHIP_STATUS_SUCCESS;
        
        case 0x2B:
            pOutRsp->data[0] = 0xBB;
            pOutRsp->data[1] = 0xBB;
            pOutRsp->length = 2;
            return ONCHIP_STATUS_SUCCESS;

        case 0x3C:
            pOutRsp->data[0] = 0xCC;
            pOutRsp->data[1] = 0xCC;
            pOutRsp->data[2] = 0xCC;
            pOutRsp->length = 3;
            return ONCHIP_STATUS_SUCCESS;

        default:
            pOutRsp->data = (uint8_t *) NULL;
            pOutRsp->length = 0;
            return ONCHIP_STATUS_FAIL;
    } 
}