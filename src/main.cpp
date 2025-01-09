#include <iostream>
#include "QAccount.h"
#include "QCalendar.h"
#include "QConfig.h"
#include "QAutomatic.h"
#include "QOperator.h"
#include "QListener.h"
#include "QAnalyst.h"

int main()
{
    char config_path[60] = "../conf/md.conf";
    QUtility::ConfigMd *configMd = new QUtility::ConfigMd(config_path);
    configMd->Display();
    QUtility::QContractsReader *contractsReader = new QUtility::QContractsReader(configMd->GetSubscribedFile());
    const QUtility::QSection *section = QUtility::match_section(configMd->GetCalendarPath());
    if (section != NULL)
    {
        QUtility::QAccount *account = new QUtility::QAccount(configMd->GetAccountFilePath());
        account->Display();
        QUtility::QWriter *writer = new QUtility::QWriter(configMd->GetMdSaveRootDir(), section);
        QUtility::QOperatorMsg *operatorMsg = new QUtility::QOperatorMsg("OperatorMsg");
        QUtility::QListenerMd *listenerMd = new QUtility::QListenerMd(operatorMsg);

        // --- core
        QUtility::QAnalyst *analyst = new QUtility::QAnalyst(
            operatorMsg, listenerMd, account, contractsReader, writer, section);
        analyst->go();
    }
}
