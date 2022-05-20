# MCP2515_Multi_Slave using LPC1768
It is the test project to receive CAN protocol data generated from motor controller KLS6022H,
4 controller's data at once.

using mbed LPC1768 and MCP2515 module, creating 2 CAN bus and receive data to both buses


I used two mbed and two MCP2515 to make CAN bus that sending signal continously
The data frame is formed by unsigned short(ID) and unsigned char(byte) array size 8.
You can use sendingFF to make CAN bus, and I recommend to change ID or data in code to check receiving data in two buses.

I used one mbed and two MCP2515 to receive CAN bus data, using receiveFF_Multi_Slave

Maybe you need to make program using LPC1768 in mbed.org online compiler, and then load this library or
import library about MCP2515 in mbed ide with small editting.


