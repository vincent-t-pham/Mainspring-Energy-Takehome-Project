// calc_test.cpp
#include <gtest/gtest.h>
#include "../src/uart_buffer.hpp"

int value = 0;
int *reference = &value;

TEST(CalcTest, Add) {
    ASSERT_EQ(2, 2);
    ASSERT_EQ(5, 5);
    ASSERT_EQ(5, 5);
    std::cout<<"Test123"<<std::endl;
}


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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    std::thread t1(looper, reference);
    // std::thread t2(ISR);
    cout<<"Can input data here"<<endl;
    //wait for thread to initialize
    sleep(2);
    ISR();
    t1.join();
    // *reference = 5;
    // ISR();
    // *reference = 3;
    // ISR();
    // *reference = 5;
    // ISR();
    return RUN_ALL_TESTS();
}