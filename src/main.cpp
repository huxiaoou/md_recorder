#include <iostream>
#include "QAccount.h"
#include "QOperator.h"
#include "QListener.h"
#include "QAnalyst.h"

int main()
{
    QUtility::Account *account = new QUtility::Account("/home/ubuntu/deploy/account_md");
    account->Display();

    QUtility::QOperatorMsg *operatorMsg = new QUtility::QOperatorMsg("OperatorMsg");
    QUtility::QListenerMd *listenerMd = new QUtility::QListenerMd(operatorMsg);
    QUtility::QAnalyst *analyst = new QUtility::QAnalyst(operatorMsg, listenerMd);
    analyst->init();
    analyst->thread_main();
}
