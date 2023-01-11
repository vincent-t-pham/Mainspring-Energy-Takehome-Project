#include <iostream>
#include<bits/stdc++.h>
using namespace std;

struct peripheralBufferStruct 
{
    queue<uint_fast8_t> q;
    int validCount = 0;
    // Or use q.size?
    int size = 0;
};

struct peripheralBufferStruct peripheralBuffer;

void push(peripheralBufferStruct &peripheralBuffer, uint_fast8_t in);
void printQueue(queue<uint_fast8_t> q);
//void push to queue and determine size constraint?

// What's in the queue? I'm going to put uint_fast8_t so it can be parsed by 2 hex digits per index
// Why do we use queue struct vs other stuff? Queue had functionality to push pop in FIFO manner, 
// but missed the size constraint



int main(){
    for(uint_fast8_t i=10; i<15; i++)
    {
        cout << unsigned(i) << " ";
        push(peripheralBuffer, i);
    }

    // CONTROL LOOP //
    // How do we know when sequence is complete? O isr is called, find how many sequences by parsing entire struct

    // ERROR HANDLING //
    cout << endl <<  "Elements: " << endl;
    printQueue(peripheralBuffer.q);
    cout << "Size: "  << peripheralBuffer.q.size() << endl;

    cout << endl;

    
    return 0;
}









void push(peripheralBufferStruct &peripheralBuffer, uint_fast8_t in)
{
    if (peripheralBuffer.q.size() < 16)
    peripheralBuffer.q.push(in);
}

// print the elements of queue
void printQueue(queue<uint_fast8_t> q)
{
    while (!q.empty())
    {
        // cout << unsigned(q.front()) << " ";
        printf("0x%X ", q.front());
        q.pop();
    }
    cout << endl;
}
