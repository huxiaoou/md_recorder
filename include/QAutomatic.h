#pragma once

#include "QCalendar.h"
#include "QConfig.h"

namespace QUtility
{
    const QSection *match_section(const char *calendarPath);
    class QContractsReader
    {
    private:
        char** contracts;
        unsigned _size;

    public:
        QContractsReader(const char *subscribedPath);
        char **GetContracts() { return contracts; }
        unsigned GetSize() { return _size; }
        void Display() const;
    };
}
