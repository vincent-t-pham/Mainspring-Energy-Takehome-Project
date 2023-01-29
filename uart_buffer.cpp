#include <iostream>
#include<bits/stdc++.h>
using namespace std;

bool fullISR = false;
struct peripheralBufferStruct 
{
    queue<uint_fast8_t> q;
    int validCount = 0;
    // Or use q.size?
    int size = 0;
};

struct peripheralBufferStruct peripheralBuffer;

void push(peripheralBufferStruct &peripheralBuffer, uint_fast8_t in);   // Push with FIFO constraint
void printQueue(queue<uint_fast8_t> q);
void fullISRhandler();
//void push to queue and determine size constraint?

// What's in the queue? I'm going to put uint_fast8_t so it can be parsed by 2 hex digits per index
// Why do we use queue struct vs other stuff? Queue had functionality to push pop in FIFO manner, 
// but missed the size constraint

//test harness (test cases)
uint_fast8_t inp1[] = {0x12, 0x34, 0x56, 0x78, 0xA5, 0x5A, 0x9A, 0xA2};

int main(){
    for(uint_fast8_t i=0; i<8; i++)
    {
        cout << unsigned(i) << " ";
        push(peripheralBuffer, inp1[i]);
    }
    
    // ERROR HANDLING //
    cout << endl <<  "Elements: " << endl;
    printQueue(peripheralBuffer.q);
    cout << "Size: "  << peripheralBuffer.q.size() << endl;

    cout << endl;

    // CONTROL LOOP //
    // How do we know when sequence is complete? O isr is called, find how many sequences by parsing entire struct
    while(1)
    {
        cout << "Control Loop: " << endl;
        sleep(10);
        if(fullISR)
        {
            for(uint_fast8_t i = 0; i<8; i++)
            {
                // if(peripheralBuffer.q[i])
                cout << peripheralBuffer.q[i] << endl;
            }
            ISR14 = false;
        }
    }
    
    return 0;
}









void push(peripheralBufferStruct &peripheralBuffer, uint_fast8_t in)
{
    //edge cases
    peripheralBuffer.q.push(in);

    // queue size of 8 with 1 byte width or 16 with 1 nibble width..? see line 26
    if (peripheralBuffer.q.size() == 16)
    {
        // temporary ISR
        fullISRhandler();
        // clear struct function
    }
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

// temporary ISRhandler
void fullISRhandler()
{
    fullISR = true;
}
