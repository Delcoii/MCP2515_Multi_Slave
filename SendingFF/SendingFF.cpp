#include "mbed.h"
#include "MCP2515.h"

Serial pc(USBTX, USBRX);

SPI spi(p5, p6, p7);
MCP2515 mcp(spi, p10);

DigitalOut myled(LED2);

int main() {
    myled = 1;
    mcp.baudConfig(250);
    MCP2515Mode mode = NORMAL;
    mcp.setMode(mode);
    
    byte data1[8] = {11, 22, 33, 44, 55, 66, 77, 88};
    byte data2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    byte data3[8] = {12, 34, 56, 78, 91, 87, 65, 43};
    
    pc.printf("MCP2515 sending ready!\r\n");
    
    while(1)
    {    
        // extending MCP2515 write to full frame(pcruce_at_igpp.ucla.edu)
        // Identifier should be a value between 0 and 2^11-1, longer identifiers will be truncated
        // (ie does not support extended frames)
        // void load_ff_0(byte length,unsigned short identifier,byte *data);
        
         
        mcp.load_ff_0(8, 1010, data1);
        mcp.send_0();               //transmits buffer 0
        pc.printf("ID : 1010, Data frame is 11, 22, ... 88   sent!\r\n\n");
        //wait(1);
        
        mcp.load_ff_0(8, 1010, data2);
        mcp.send_0();               //transmits buffer 0
        pc.printf("ID : 1010, Data frame is 1, 2, 3, 4, ..   sent!\r\n\n");
        //wait(1);
        
        mcp.load_ff_0(8, 1010, data3);
        mcp.send_0();               //transmits buffer 0
        pc.printf("ID : 1010, Data frame is 12, 34, 56, ..   sent!\r\n\n");
        //wait(1);
        
        
        
        myled != myled;             // check blink
    }
    
}
