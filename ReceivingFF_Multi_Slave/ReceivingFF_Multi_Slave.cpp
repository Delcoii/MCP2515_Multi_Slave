#include "mbed.h"
#include "MCP2515.h"
// using 3 mbed LPC1768 and 4 MCP2515 module
// main code for receiving two CAN bus signal

Serial pc(USBTX, USBRX);            // for checking received data

SPI spi(p5, p6, p7);                // set SPI ( mosi, miso, sck )

MCP2515 mcp_0(spi, p10);            // MCP2515 ( spi, cs pin )
                                    // MCP2515 is reset
MCP2515 mcp_1(spi, p12);            // MCP2515 ( spi, cs pin )
                                    // MCP2515 is reset

DigitalOut myled(LED2);

int main() {
    myled = 1;
    
    // setting MCP2515 ( cs pin 10 )
    mcp_0.baudConfig(250);          // set CAN bus rate to 250kb/s
    MCP2515Mode mode = NORMAL;      // mode NORMAL
    mcp_0.setMode(mode);
    
    // setting MCP2515 ( cs pin 12 )
    mcp_1.baudConfig(250);          // set bitrate 250kb/s
    mcp_1.setMode(mode);            // mode NORMAL
    
    // declare buffer
    byte received_data[8];          // 8 byte array
    byte received_length;           // can receive the data's length
    unsigned short received_id;     // receive ID
    
    pc.printf("MCP2515 receiving ready!\r\n");
    
    while(1)
    {    
        // extending MCP2515 data read to full frames(pcruce_at_igpp.ucla.edu)
        // data_out should be array of 8-bytes or frame length.
        // void readDATA_ff_0(byte* length_out,byte *data_out, unsigned short *id_out); 
        
        
        // (readStatus() & 0x80) == 0x80 means frame in buffer 0
        if(mcp_0.readStatus() & 0x80 == 0x80)
        {
            mcp_0.readDATA_ff_0(&received_length, received_data, &received_id);
            // read ID, data length, data in buffer
            
            
            pc.printf("ID : %d\r\n", received_id);      // print ID
            
            pc.printf("received data : ");              
            for(int i = 0; i < received_length; i++)    // print data, loop as long as received length
                pc.printf("%d ", received_data[i]);
                
            pc.printf("\r\n\n");   
        }
        
        
        // repeat in MCP2515, cs pin 12
        if(mcp_1.readStatus() & 0x80 == 0x80)
        {
            mcp_1.readDATA_ff_0(&received_length, received_data, &received_id);
            
            
            pc.printf("ID : %d\r\n", received_id);
            
            pc.printf("received data : ");
            for(int i = 0; i < received_length; i++)
                pc.printf("%d ", received_data[i]);
            pc.printf("\r\n\n");
        }
    }
}
