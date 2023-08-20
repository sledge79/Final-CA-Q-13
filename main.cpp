/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"


BufferedSerial pc(USBTX, USBRX);
BufferedSerial dev(D1, D0);
DigitalOut myled(LED1);

void dev_recv(){
    while(1) {
        char recv_data;
        if (dev.read(&recv_data, 1) > 0)
        {pc.write(&recv_data, 1);

        }
    }
}

void pc_recv(){
    while(1) {
        char recv_data;
        if (pc.read(&recv_data, 1) > 0) {
        dev.write(&recv_data, 1);
        }
    }
}
        

int main(){
    dev.set_baud(115200);
    pc.set_baud(9600);
    Thread dev_thread;
    Thread pc_thread;

    dev_thread.start(dev_recv);
    pc_thread.start(pc_recv);

    printf("Hello!! \r\n");

    while (1) {
        myled = !myled;
        wait_us (1000);

    }
}

