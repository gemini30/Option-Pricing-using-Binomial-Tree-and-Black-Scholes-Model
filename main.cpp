#include <iostream>
#include "option.h"

int main(int argc, const char * argv[]) {



    AmericanCall AmCallBt(100, 1, 0.1348, 0.06);
    std::cout << "American Call price using Binomial Tree Model: " << AmCallBt.getBinomialTreeValue(100, 3) << std::endl;
    
    AmericanCall AmCallBS(100, 1, 0.1348, 0.06);
    std::cout << "American Call price using Black Scholes Model: " << AmCallBS.getBlackScholesValue(100) << std::endl;

    AmericanPut AmPutBt(52, 2, 0.3, 0.05);
    std::cout << "American price using Binomial Tree Model: " << AmPutBt.getBinomialTreeValue(50, 2) << std::endl;
    
    AmericanPut AmPutBs(52, 2, 0.3, 0.05);
    std::cout << "American Put price using Black Scholes Model: " << AmPutBs.getBlackScholesValue(50) << std::endl;

    AmericanCall AmCallwDy(100, 1, 0.1348, 0.06);
    std::cout << "American Call with dividend: " << AmCallwDy.getBinomialTreeValue(105, 3,0.02) << std::endl;

    AmericanPut AmPutwDy(100, 1.5, 0.2579, 0.05);
    std::cout << "American Put with dividend: " << AmPutwDy.getBinomialTreeValue(96, 3,0.02) << std::endl;

    EuropeanCall EuCallBs(800, 0.5, 0.20, 0.025);
    std::cout << "European Call price using Black Scholes Model: " << EuCallBs.getBlackScholesValue(810) << std::endl;

    EuropeanCall EuCallBt(800, 0.5, 0.20, 0.025);
    std::cout << "European Call price using Binomial Tree Model: " << EuCallBt.getBinomialTreeValue(810,2) << std::endl;

    EuropeanPut EuPutBs(63.75, 1, 0.2, 0.04);
    std::cout << "European put price using Black Scholes Model: " << EuPutBs.getBlackScholesValue(75) << std::endl;
    
    EuropeanPut EuPutBt(63.75, 1, 0.2, 0.04);
    std::cout << "European put price using Binomial Tree Model: " << EuPutBt.getBinomialTreeValue(75,3) << std::endl;

    KnockOutCall koCall(120, 1, 0.3, 0.06, 130);
    std::cout << "Knockout Call: " << koCall.getBinomialTreeValue(125, 500) << std::endl;

    KnockOutPut koPut(80, 0.5, 0.25, 0.04, 75);
    std::cout << "Knockout Put: " << koPut.getBinomialTreeValue(70, 300) << std::endl;

    return 0;
}
