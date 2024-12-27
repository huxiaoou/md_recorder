#include <iostream>
#include "QOperator.h"
#include "QListener.h"
#include "QAnalyst.h"

int main()
{
    QUtility::QOperatorMsg *operatorMsg = new QUtility::QOperatorMsg("OperatorMsg");
    QUtility::QListenerMd *listenerMd = new QUtility::QListenerMd(operatorMsg);
    QUtility::QAnalyst *analyst = new QUtility::QAnalyst(operatorMsg, listenerMd);
    analyst->init();
    analyst->thread_main();
}