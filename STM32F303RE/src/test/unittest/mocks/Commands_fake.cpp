#include "Commands_fake.hpp"

onChip_Cmd_Entry CmdTable[10] = \
{
    //Group     Id      Function
    { 0x00,     0x00,   Test0   },
    { 0x00,     0x01,   Test1   },
    { 0x00,     0x02,   Test2   },
    { 0x00,     0x03,   Test3   },
    { 0x00,     0x04,   Test4   },
    { 0x00,     0x05,   Test5   },
    { 0x00,     0x06,   Test6   },
    { 0x00,     0x07,   Test7   },
    { 0x00,     0x08,   Test8   },
    { 0x00,     0x09,   Test9   }
};

Mock<Commands> Commands_mock;

Commands &Commands_fake = Commands_mock.get();

onChip_Status Test0(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(0, pInBuf, pOutRsp);
}

onChip_Status Test1(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(1, pInBuf, pOutRsp);
}

onChip_Status Test2(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(2, pInBuf, pOutRsp);
}

onChip_Status Test3(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(3, pInBuf, pOutRsp);
}

onChip_Status Test4(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(4, pInBuf, pOutRsp);
}

onChip_Status Test5(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(5, pInBuf, pOutRsp);
}

onChip_Status Test6(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(6, pInBuf, pOutRsp);
}

onChip_Status Test7(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(7, pInBuf, pOutRsp);
}

onChip_Status Test8(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(8, pInBuf, pOutRsp);
}

onChip_Status Test9(uint8_t *pInBuf, onChip_Rsp *pOutRsp)
{
    return Commands_fake.CmdTest(9, pInBuf, pOutRsp);
}