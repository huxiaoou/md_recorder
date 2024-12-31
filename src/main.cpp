#include <iostream>
#include "QConfig.h"
#include "QAccount.h"
#include "QOperator.h"
#include "QListener.h"
#include "QAnalyst.h"

int main()
{
    char config_path[60] = "../conf/md.conf";

    QUtility::ConfigMd *configMd = new QUtility::ConfigMd(config_path);
    QUtility::QAccount *account = new QUtility::QAccount(configMd->GetAccountFilePath());
    account->Display();

    QUtility::QOperatorMsg *operatorMsg = new QUtility::QOperatorMsg("OperatorMsg");
    QUtility::QListenerMd *listenerMd = new QUtility::QListenerMd(operatorMsg);
    QUtility::QAnalyst *analyst = new QUtility::QAnalyst(operatorMsg, listenerMd, account);
    analyst->init();
    analyst->thread_main();
}
