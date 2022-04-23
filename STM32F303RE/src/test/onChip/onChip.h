#ifndef __ONCHIP_DEVICE_HEADER__
#define __ONCHIP_DEVICE_HEADER__

#include "STM32F303RE.h"

#define ONCHIP_BUF_SIZE 100

typedef enum
{
    ONCHIP_STATUS_SUCCESS = 0,
    ONCHIP_STATUS_FAIL,
    ONCHIP_STATUS_ERROR_CMD_EMPTY,
    ONCHIP_STATUS_ERROR_CMD_LENGTH_MISMATCH,
    ONCHIP_STATUS_ERROR_CMD_NOT_EXIST,
} onChip_Status;

#ifdef UNIT_TEST
    #pragma pack(1)
#endif

typedef struct __attribute__((packed))
{
    void (*pSerialTxChar_func)(uint8_t);
    void (*pSerialRxChar_func)(uint8_t *);
} onChip_Cfg;

typedef struct __attribute__((packed))
{
    uint8_t         group;
    uint8_t         id;
    uint8_t         data[ONCHIP_BUF_SIZE];    
} onChip_Cmd;

typedef struct __attribute__((packed))
{
    uint8_t         length;
    uint8_t         data[ONCHIP_BUF_SIZE];    
} onChip_Rsp;

typedef struct __attribute__((packed))
{
    uint8_t         length;
    onChip_Cmd      command;   
} onChip_in;

typedef struct __attribute__((packed))
{
    onChip_Status   status;
    onChip_Rsp      response;   
} onChip_out;

typedef struct __attribute__((packed))
{
    uint8_t group;
    uint8_t id;
    onChip_Status (*func)(uint8_t *pInBuf, onChip_Rsp *pOutRsp);    
} onChip_Cmd_Entry;

#ifdef UNIT_TEST
    #pragma pack()
#endif

extern onChip_Cmd_Entry CmdTable[10];

onChip_Status onChip_init(onChip_Cfg *pCfg);
onChip_Status onChip_receive_cmd(uint8_t *pInBuf);
onChip_Status onChip_command_handler(onChip_in *pInString, onChip_out *pOutString);
void          onChip_transmit_rsp(onChip_out *pOutString);
onChip_Status onChip_transceive(uint8_t *pInBuf, uint8_t *pOutBuf);

#endif
