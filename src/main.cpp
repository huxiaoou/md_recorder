#include "QOperator.h"
#include <iostream>

int main(){
    QUtility::OperatorMsg* operatorMsg = new QUtility::OperatorMsg();
    operatorMsg->Init("OperatorMsg");
    std::cout << "hello, world" << std::endl;
}