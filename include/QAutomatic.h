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
        char _mdSaveRootDir[240];
        const QSection* _section;
        QTimestamp* _watch;
        FILE *file;

    public:
        QWriter(const char *mdSaveRootDir, const QSection* section);
        void Write(const CThostFtdcDepthMarketDataField *pDmd);
    };
}
