// calc_test.cpp
#include <gtest/gtest.h>
#include "calc.hpp"

TEST(CalcTest, Add) {
    ASSERT_EQ(2, add(1, 1));
    ASSERT_EQ(5, add(3, 2));
    ASSERT_EQ(10, add(7, 3));
    std::cout<<"Test123"<<std::endl;
}

TEST(CalcTest, Sub) {
    ASSERT_EQ(3, sub(5, 2));
    ASSERT_EQ(-10, sub(5, 15));
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
    return RUN_ALL_TESTS();
}