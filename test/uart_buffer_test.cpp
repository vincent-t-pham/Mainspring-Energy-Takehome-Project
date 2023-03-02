// calc_test.cpp
#include <gtest/gtest.h>
#include "../src/uart_buffer.hpp"

int value = 0;
int *reference = &value;

peripheralBufferStruct peripheralBuffer;
peripheralBufferStruct* ptr= &peripheralBuffer;

// TEST(CalcTest, Add) {
//     cout<<"Expect reference = 0" << endl;
//     ASSERT_EQ(*reference, 0);
//     ISR();
//     sleep(2);
//     cout<<"Expect reference = 1\t Value is " << *reference<< endl;
//     ASSERT_EQ(*reference, 1);
//     ISR();
//     sleep(2);
//     cout<<"Expect reference = 2" << endl;
//     ASSERT_EQ(*reference, 2);
//     ASSERT_EQ(2, 2);
//     ASSERT_EQ(2, 2);
// }


//test fixture initializes struct with queue
//load test sample (size 32) into struct, how does gtest struct share with src struct, 
//change main to function with argument of pointer to struct?

//initialize struct for queue
//initialize control loop function with struct argument
//load test sample
//8 half-words loaded
//no way control loop here 
//maybe just initialize the data? no, waste of space
//must contain data here as per harness and how to continuously load into function??
//

//

uint_fast8_t inp1[] = {0x12, 0x34, 0x56, 0x78, 0xA5, 0x5A, 0x9A, 0xA2};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    // std::thread t1(looper, reference, ptr);
    for(uint_fast8_t i=0; i<8; i++)
    {
        cout << unsigned(i) << " ";
        push(peripheralBuffer, inp1[i]);
    }
    uart(ptr);
    // std::thread t2(ISR);
    cout<<"Can input data here"<<endl;
    //wait for thread to initialize
    sleep(2);

    return RUN_ALL_TESTS();
}