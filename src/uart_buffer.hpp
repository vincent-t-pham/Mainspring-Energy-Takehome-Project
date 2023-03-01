#ifndef UART_BUFFER_HPP_
#define UART_BUFFER_HPP_

#include <iostream>
#include<bits/stdc++.h>

using namespace std;

struct peripheralBufferStruct 
{
    std::queue<uint_fast8_t> q;
    int validCount = 0;
    // Or use q.size?
    int size = 0;
};

void looper(int* reference);
void ISR();
void fullISRhandler();
void push(peripheralBufferStruct &peripheralBuffer, uint_fast8_t in);   // Push with FIFO constraint
void printQueue(queue<uint_fast8_t> q);



#endif