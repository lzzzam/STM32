#include "onChip.h"
#include "onChip_Cmd.h"

static void (*onChip_read_char)(uint8_t *data);
static void (*onChip_write_char)(uint8_t data);

onChip_Status onChip_init(onChip_Cfg *pCfg)
{
    if ((pCfg->pSerialRxChar_func == NULL) || 
        (pCfg->pSerialTxChar_func == NULL))
    {
        return ONCHIP_STATUS_FAIL;
    }
    
    onChip_read_char  = pCfg->pSerialRxChar_func;
    onChip_write_char = pCfg->pSerialTxChar_func;

    return ONCHIP_STATUS_SUCCESS;
}

onChip_Status onChip_receive_cmd(uint8_t *pInBuf)
{
    uint8_t data;
    uint8_t counter = 0;
    onChip_in *inString;

    do
    {
        // Read new data (blocking)
        onChip_read_char(&data);

        // Update input buffer
        if (data != '\n')
        {
            pInBuf[counter] = data;
            
            // Increment counter
            counter++;
        }

    } while (data != '\n');

    // Access input buffer as command string
    inString = (onChip_in *)pInBuf;

    // Sanity check on number of received bytes
    if (counter == 0)
    {
        return ONCHIP_STATUS_ERROR_CMD_EMPTY;
    }
    else if (inString->length != counter)
    {
        return ONCHIP_STATUS_ERROR_CMD_LENGTH_MISMATCH;
    }

    return ONCHIP_STATUS_SUCCESS;
}

void onChip_transmit_rsp(onChip_out *pOutString)
{
    uint8_t length = pOutString->response.length;
    uint8_t *buf = pOutString->response.data;
    onChip_Status status = pOutString->status;
   
    // Write length = (response data length + status field)
    onChip_write_char(length+2);

    // Write status
    onChip_write_char((uint8_t)status);

    // Write data payload
    for(uint8_t i=0; i< length; i++)
    {
        onChip_write_char(buf[i]);
    }
}

onChip_Status onChip_command_handler(onChip_in *pInString, onChip_out *pOutString)
{
    uint8_t cmdFound = 0;
    
    // Search from command Group & ID
    uint8_t group = pInString->command.group;
    uint8_t id    = pInString->command.id;

    for (uint8_t i=0; i<10; i++)
    {
        if ((group == CmdTable[i].group) && (id == CmdTable[i].id))
        {
            // Call command and pass input data and output struct
            pOutString->status = CmdTable[i].func(pInString->command.data, 
                                                  &(pOutString->response));

            // Updated flag
            cmdFound = 1;

            break;
        }
    } 

    // Check if command exist
    if (!cmdFound)
    {
        pOutString->status = ONCHIP_STATUS_ERROR_CMD_NOT_EXIST;
        pOutString->response.data = (uint8_t *)NULL;
        pOutString->response.length = 0;

        return ONCHIP_STATUS_ERROR_CMD_NOT_EXIST;
    }

    return ONCHIP_STATUS_SUCCESS;
}

onChip_Status onChip_transceive(onChip_in *pInString, onChip_out *pOutString)
{
    onChip_Status status;

    // Listen for new command
    status = onChip_receive_cmd((uint8_t *)pInString);

    // Decode and execute
    if (status == ONCHIP_STATUS_SUCCESS)
    {
        status = onChip_command_handler(pInString, pOutString);
    }
    else
    {
        // In case of error format response
        pOutString->status = status;
        pOutString->response.data = (uint8_t *)NULL;
        pOutString->response.length = 0;
    }

    // Send response
    onChip_transmit_rsp(pOutString);

    return status;
}