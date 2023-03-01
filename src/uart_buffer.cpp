#include <iostream>
#include<bits/stdc++.h>
#include <gtest/gtest.h>
#include "uart_buffer.hpp"
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;

bool fullISR = false;

struct peripheralBufferStruct peripheralBuffer;

//void push to queue and determine size constraint?

// What's in the queue? I'm going to put uint_fast8_t so it can be parsed by 2 hex digits per index
// Why do we use queue struct vs other stuff? Queue had functionality to push pop in FIFO manner, 
// but missed the size constraint

//test harness (test cases)
uint_fast8_t inp1[] = {0x12, 0x34, 0x56, 0x78, 0xA5, 0x5A, 0x9A, 0xA2};

// int main(){
//     uint_fast8_t first, second;
//     for(uint_fast8_t i=0; i<8; i++)
//     {
//         cout << unsigned(i) << " ";
//         push(peripheralBuffer, inp1[i]);
//     }
    
//     // ERROR HANDLING //
//     cout << endl <<  "Elements: " << endl;
//     printQueue(peripheralBuffer.q);
//     cout << "Size: "  << peripheralBuffer.q.size() << endl;

//     cout << endl;

//     // CONTROL LOOP //
//     // How do we know when sequence is complete? O isr is called, find how many sequences by parsing entire struct
//     while(1)
//     {
//         cout << "Control Loop: " << endl;
//         sleep(2);

//         if(peripheralBuffer.q.size()==8){
//             // FIFO Buffer is full
//             cout << "CLEAR BUFFER" << endl;
//             sleep(1); //handle
//             first = peripheralBuffer.q.front();
//             peripheralBuffer.q.pop();
//             second = peripheralBuffer.q.front();
//             peripheralBuffer.q.pop();

//             // Parse data for valid sequence
//             for(uint_fast8_t i = 0; i<7; i++)
//             {
//                 printf("Case %d\n\t0x%X\n\t0x%X\n", i, first, second);

//                 if(first==0xA5 && second==0x5A){
//                     cout<<"\n\tHit!\n";
//                     peripheralBuffer.validCount++;
//                 }
//                 first = second;
//                 second = peripheralBuffer.q.front();
//                 peripheralBuffer.q.pop();


//                 // if(peripheralBuffer.q[i])
//                 // cout << peripheralBuffer.q[i] << endl;
//                 cout << "Size: "  << peripheralBuffer.q.size() << endl;
//                 cout<<"Test"<<endl;
//             }
//             push(peripheralBuffer, 0x55);            
//             push(peripheralBuffer, 0x55);
//             cout << "Size: "  << peripheralBuffer.q.size() << endl;
//             printf("0x%X ", peripheralBuffer.q.front());

//         }

//         // if(fullISR)
//         // {
//         //     for(uint_fast8_t i = 0; i<8; i++)
//         //     {
//         //         // if(peripheralBuffer.q[i])
//         //         // cout << peripheralBuffer.q[i] << endl;
//         //         cout<<"Test"<<endl;
//         //     }
//         //     fullISR = false;
//         // }
//     }
    
//     return 0;
// }


// int uart(peripheralBufferStruct *peripheralBuffer){
//     uint_fast8_t first, second;
//     for(uint_fast8_t i=0; i<8; i++)
//     {
//         cout << unsigned(i) << " ";
//         push(peripheralBuffer, inp1[i]);
//     }
    
//     // ERROR HANDLING //
//     cout << endl <<  "Elements: " << endl;
//     printQueue(peripheralBuffer.q);
//     cout << "Size: "  << peripheralBuffer.q.size() << endl;

//     cout << endl;

//     // CONTROL LOOP //
//     // How do we know when sequence is complete? O isr is called, find how many sequences by parsing entire struct
//     while(1)
//     {
//         cout << "Control Loop: " << endl;
//         sleep(2);

//         if(peripheralBuffer.q.size()==8){
//             // FIFO Buffer is full
//             cout << "CLEAR BUFFER" << endl;
//             sleep(1); //handle
//             first = peripheralBuffer.q.front();
//             peripheralBuffer.q.pop();
//             second = peripheralBuffer.q.front();
//             peripheralBuffer.q.pop();

//             // Parse data for valid sequence
//             for(uint_fast8_t i = 0; i<7; i++)
//             {
//                 printf("Case %d\n\t0x%X\n\t0x%X\n", i, first, second);

//                 if(first==0xA5 && second==0x5A){
//                     cout<<"\n\tHit!\n";
//                     peripheralBuffer.validCount++;
//                 }
//                 first = second;
//                 second = peripheralBuffer.q.front();
//                 peripheralBuffer.q.pop();


//                 // if(peripheralBuffer.q[i])
//                 // cout << peripheralBuffer.q[i] << endl;
//                 cout << "Size: "  << peripheralBuffer.q.size() << endl;
//                 cout<<"Test"<<endl;
//             }
//             push(peripheralBuffer, 0x55);            
//             push(peripheralBuffer, 0x55);
//             cout << "Size: "  << peripheralBuffer.q.size() << endl;
//             printf("0x%X ", peripheralBuffer.q.front());

//         }

//         // if(fullISR)
//         // {
//         //     for(uint_fast8_t i = 0; i<8; i++)
//         //     {
//         //         // if(peripheralBuffer.q[i])
//         //         // cout << peripheralBuffer.q[i] << endl;
//         //         cout<<"Test"<<endl;
//         //     }
//         //     fullISR = false;
//         // }
//     }
// }

mutex uart_mutex;
condition_variable locker;

void looper(int* reference)
{
    while(*reference<2)
    {
    cout<<"Thread initialized"<<endl;
    unique_lock<mutex> lk(uart_mutex);
    cout<<"Waiting.."<<endl;
    locker.wait(lk, []{return fullISR==true;});
    *reference= *reference + 1 ;
    cout<<"Wait interrupted - Performing Queue arithmetic\tValue: " << *reference <<endl<<endl;
    fullISR = false;
    cout<<"Thread closed"<<endl;    
    }
}

void ISR()
{
    //constant polling vs test harness calling ISR but w/e
    cout<<"Interrupting"<<endl;
    fullISR=true;
    locker.notify_one();        
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
