#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "USART_fake.hpp"
#include "Commands_fake.hpp"
#include "../onChip/onChip.h"

TEST_CASE( "onChip Init", "[init]" ) 
{
    onChip_Cfg cfg;

    SECTION("Pass with correct argument")
    {
        cfg = {USART_write_char, USART_read_char};
        REQUIRE(ONCHIP_STATUS_SUCCESS == onChip_init(&cfg));
    }

    SECTION("Test null argument")
    {
        cfg = {NULL, USART_read_char};
        REQUIRE(ONCHIP_STATUS_FAIL == onChip_init(&cfg));
    }

    SECTION("Test null argument")
    {
        cfg = {USART_write_char, NULL};
        REQUIRE(ONCHIP_STATUS_FAIL == onChip_init(&cfg));
    }
}

TEST_CASE("Test onChip_receive_cmd") 
{
    onChip_Cfg cfg;
    onChip_Status status;
    uint8_t buf[100];

    USART_mock.Reset();
    
    // init onChip module
    cfg = {USART_write_char, \
           USART_read_char};

    onChip_init(&cfg);

    SECTION("Receive string with length=1")
    {
        // Mock to receive length + endCmd char
        When(Method(USART_mock, read_char)).Return(0x01,'\n');

        // Receive command
        status = onChip_receive_cmd(buf);
        
        // Check for success and length matching
        REQUIRE(ONCHIP_STATUS_SUCCESS == status);
        REQUIRE(0x01 == ((onChip_in *)buf)->length);
    }

    SECTION("Receive string with length=6")
    {   
        // Mock to receive length + endCmd char
        When(Method(USART_mock, read_char)).Return(0x06,0xFF,0xFF,0xFF,0xFF,0xFF,'\n');

        // Receive command
        status = onChip_receive_cmd(buf);
        
        // Check for success and length matching
        REQUIRE(ONCHIP_STATUS_SUCCESS == status);
        REQUIRE(0x06 == ((onChip_in *)buf)->length);
    }

    SECTION("Receive string with length=100")
    {   
        // Mock to receive length + endCmd char
        When(Method(USART_mock, read_char)).Return(100 ,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
                                                   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,'\n');

        // Receive command
        status = onChip_receive_cmd(buf);
        
        // Check for success and length matching
        REQUIRE(ONCHIP_STATUS_SUCCESS == status);
        REQUIRE(100 == ((onChip_in *)buf)->length);

        // Check that Group\Id was received correctly
        REQUIRE(0x00 == ((onChip_in *)buf)->command.group);
        REQUIRE(0x01 == ((onChip_in *)buf)->command.id);

        // Checl data field was received correctly
        for (uint8_t i=0; i<97; i++)
        {
            REQUIRE(((onChip_in *)buf)->command.data[i] == 0xFF);
        }  
    }

    SECTION("Fail with string empty -> length=0")
    {
        // Mock to receive length + endCmd char
        When(Method(USART_mock, read_char)).Return('\n');

        // Receive command
        status = onChip_receive_cmd(buf);
        
        // Check for success and length matching
        REQUIRE(ONCHIP_STATUS_ERROR_CMD_EMPTY == status);
    }

    SECTION("Fail with wrong length")
    {   
        // Mock to receive length + endCmd char
        When(Method(USART_mock, read_char)).Return(0x02,0xFF,0xFF,0xFF,'\n');

        // Receive command
        status = onChip_receive_cmd(buf);
        
        // Check for success and length matching
        REQUIRE(ONCHIP_STATUS_ERROR_CMD_LENGTH_MISMATCH == status);
    }
}

TEST_CASE( "Test onChip_transmit_rsp") 
{
    onChip_Cfg cfg;
    onChip_Status status;
    onChip_out outString;

    USART_mock.Reset();
    
    // init onChip module
    cfg = {USART_write_char, \
           USART_read_char};

    onChip_init(&cfg);

    SECTION("Check various transfer length")
    {
        auto rspLength = GENERATE(0,1,2,5,10,20,100);

        Fake(Method(USART_mock, write_char));
        
        // Init response
        outString.status = ONCHIP_STATUS_SUCCESS;
        outString.response.length = (uint8_t) rspLength;

        // Fill response with data
        for (uint32_t i=0; i<(uint8_t)rspLength; i++)
        {
            outString.response.data[i] = 0xFF;
        }

        // Transfer response
        onChip_transmit_rsp(&outString);

        // Check that all bytes have been sent
        Verify(Method(USART_mock, write_char)).Exactly(rspLength+2);

        // Check sequence of transfer
        if (rspLength > 0)
        {
            Verify(Method(USART_mock,write_char).Using(outString.response.length +2) + \
                   Method(USART_mock,write_char).Using(outString.status)             + \
                   Method(USART_mock,write_char).Using(0xFF) * rspLength).Exactly(1);
        }
        else //rspLength == 0
        {
            Verify(Method(USART_mock,write_char).Using(outString.response.length +2) + \
                   Method(USART_mock,write_char).Using(outString.status)).Exactly(1);
        }

        // Check that no other write have been made
        VerifyNoOtherInvocations(Method(USART_mock,write_char));
    }
}

TEST_CASE( "Test onChip_command_handler") 
{
    onChip_Cfg cfg;
    onChip_Status status;
    onChip_in  inString;
    onChip_out outString;
    uint8_t i;

    USART_mock.Reset();
    Commands_mock.Reset();
    
    // init onChip module
    cfg = {USART_write_char, \
           USART_read_char};

    onChip_init(&cfg);

    SECTION("Call all entries in the CmdTable")
    {
        /* Test all commands in the CmdTable 
         * with various input length */
        auto ID     = GENERATE(0,1,2,3,4,5,6,7,8,9);
        auto LENGTH = GENERATE(take(10, random(0,99)));
        
        // Mock the Test<ID> to copy input buffer into output buffer
        When(Method(Commands_mock, CmdTest)).Do([](uint8_t n, uint8_t *pInBuf, onChip_Rsp *pOutRsp)->onChip_Status
        {  
            // Read input length 
            uint8_t len = pInBuf[0];

            // Invert input data to output
            for (uint8_t i=1; i<=len; i++)
            {
                pOutRsp->data[i] = ~pInBuf[i];
            }
            
            // Update response length
            pOutRsp->length  = len;

            // Update response status
            return ONCHIP_STATUS_SUCCESS;
        });

        // Init input string to call "Test<ID>"
        inString.command.group = 0x00;
        inString.command.id    = ID;

        // First byte is length
        inString.command.data[0] = LENGTH;

        // Fill input buffer with random data
        for (i=1; i<= LENGTH; i++)
        {
            inString.command.data[i] = (uint8_t)random();
        }

        // Decode input string and call handler
        onChip_command_handler(&inString, &outString);

        // Check that "Test<ID>" was called with right parameters
        Verify(Method(Commands_mock, CmdTest).Using((uint8_t)ID, (uint8_t *)&inString.command.data[0], (onChip_Rsp *)&outString.response)).Exactly(1);

        // Check response and status returned
        REQUIRE(outString.response.length  == LENGTH);
        REQUIRE(outString.status == ONCHIP_STATUS_SUCCESS);
        for (i=1; i<=LENGTH; i++)
        {
            REQUIRE(outString.response.data[i] == (uint8_t)~inString.command.data[i]);
        }
    }

    SECTION("Check command not found")
    {
        /* Generate Group\Id pairs that 
         * are NOT present in the CmdTable */
        auto GROUP  = GENERATE(1,2,3,4,5,6,7,8,9);
        auto ID     = GENERATE(0,1,2,3,4,5,6,7,8,9);

        // Init input command
        inString.command.group = GROUP;
        inString.command.id    = ID;

        // Fake the Test<ID>
        Fake(Method(Commands_mock, CmdTest));

        // Decode input string and call handler
        onChip_command_handler(&inString, &outString);

        // Check if no function was called 
        VerifyNoOtherInvocations(Method(Commands_mock, CmdTest));

        // Check response and status returned
        REQUIRE(outString.status == ONCHIP_STATUS_ERROR_CMD_NOT_EXIST);
        REQUIRE(outString.response.length == 0);
    }
}


TEST_CASE( "Test command receive + decoding + response transmit") 
{
    onChip_Cfg cfg;
    onChip_Status status;
    uint8_t inBuf[100];
    uint8_t outBuf[100];

    // Reset mocks
    USART_mock.Reset();
    Commands_mock.Reset();
    
    // init onChip module
    cfg = {USART_write_char, USART_read_char};
    onChip_init(&cfg);

    SECTION("Call all entries in the CmdTable")
    {
        // Test all command in the CmdTable
        uint8_t GROUP = 0x00;
        auto    ID    = GENERATE(0,1,2,3,4,5,6,7,8,9);
        
        // Trigger command assigned to {Group=0, Id = <ID>} with no data
        When(Method(USART_mock, read_char)).Return(0x03, GROUP, (uint8_t)ID, '\n');
        Fake(Method(USART_mock, write_char));

        // Mock all test function to return with success and 0 length
        When(Method(Commands_mock, CmdTest)).Do([](uint8_t n, uint8_t *pInBuf, onChip_Rsp *pOutRsp)->onChip_Status
        {
            pOutRsp->length = 0;
            return ONCHIP_STATUS_SUCCESS;
        });

        // Test complete receive + decode + transmit
        status = onChip_transceive(inBuf, outBuf);

        // Check that return status is OK
        REQUIRE(status == ONCHIP_STATUS_SUCCESS);

        // Check that "Test<ID>" was called with right parameters
        Verify(Method(Commands_mock, CmdTest).Using((uint8_t) ID, &((onChip_in *)inBuf)->command.data[0], &((onChip_out *)outBuf)->response)).Exactly(1);

        // Check that only length + status was trasnmitted
        Verify(Method(USART_mock,write_char)).Exactly(2);

        // Check that length + status was transmitted in the right order
        Verify(Method(USART_mock,write_char).Using(((onChip_out *)outBuf)->response.length +2) + \
               Method(USART_mock,write_char).Using(((onChip_out *)outBuf)->status)).Exactly(1);

        // Check response and status returned
        REQUIRE( ((onChip_out *)outBuf)->response.length == 0);
        REQUIRE( ((onChip_out *)outBuf)->status == ONCHIP_STATUS_SUCCESS);
    }

    SECTION("Copy input string data to output response")
    {
        // Test all command in the CmdTable
        uint8_t GROUP = 0x00;
        auto    ID    = GENERATE(0,1,2,3,4,5,6,7,8,9);

        uint8_t len  = 50;
        
        // Trigger command assigned to {Group=0, Id = <ID>} with data
        When(Method(USART_mock, read_char)).Return(len , GROUP,   ID, 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                   0xFF,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,          
                                                   0xFF,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                   0xFF,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                   0xFF,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, '\n');
        Fake(Method(USART_mock, write_char));

        // Mock all test function to echo the input string data
        When(Method(Commands_mock, CmdTest)).Do([](uint8_t n, uint8_t *pInBuf, onChip_Rsp *pOutRsp)->onChip_Status
        {
            // First byte is total number of data bytes
            pOutRsp->length = pInBuf[0];

            // Copy input to output
            for (uint8_t i=0; i<pOutRsp->length; i++)
            {
                pOutRsp->data[i] = pInBuf[i];
            }

            return ONCHIP_STATUS_SUCCESS;
        });

        // Test complete receive + decode + transmit
        status = onChip_transceive(inBuf, outBuf);

        // Check that return status is OK
        REQUIRE(status == ONCHIP_STATUS_SUCCESS);

        // Check that "Test<ID>" was called with right parameters
        Verify(Method(Commands_mock, CmdTest).Using((uint8_t) ID, &((onChip_in *)inBuf)->command.data[0], &((onChip_out *)outBuf)->response)).Exactly(1);

        // Check that only length + status + data was trasnmitted
        Verify(Method(USART_mock,write_char)).Exactly(49);

        // Check that length + status + data was transmitted in the right order
        Verify(Method(USART_mock,write_char).Using(((onChip_out *)outBuf)->response.length +2) + \
               Method(USART_mock,write_char).Using(((onChip_out *)outBuf)->status)             + \
               Method(USART_mock,write_char) * 0x2F).Exactly(1);

        // Check response and status returned
        REQUIRE(((onChip_out *)outBuf)->response.length  == 47);
        REQUIRE(((onChip_out *)outBuf)->status == ONCHIP_STATUS_SUCCESS);
    }

}