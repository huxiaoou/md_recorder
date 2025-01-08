#pragma once

#include "ThostFtdcUserApiStruct.h"
#include "QCalendar.h"
#include "QWidgets.h"
#include "QConfig.h"

namespace QUtility
{
    const QSection *match_section(const char *calendarPath);
    class QContractsReader
    {
    private:
        char **contracts;
        unsigned _size;

    public:
        QContractsReader(const char *subscribedPath);
        char **GetContracts() { return contracts; }
        unsigned GetSize() { return _size; }
        void Display() const;
    };

    class QWriter
    {
    private:
        char _trade_date[12];
        char _mdSaveRootDir[240];
        FILE *file;

    public:
        QWriter(const char *trade_date, const char *mdSaveRootDir);
        void Write(const CThostFtdcDepthMarketDataField *pDmd);
    };
}
