#include <iostream>
#include "QOperator.h"
#include "QListener.h"

int main()
{
    QUtility::QOperatorMsg *operatorMsg = new QUtility::QOperatorMsg("OperatorMsg");
    QUtility::QListenerMd *listenerMd = new QUtility::QListenerMd(operatorMsg);
    std::cout << "Googbye" << std::endl;
}