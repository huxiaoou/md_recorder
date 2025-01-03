#include "QAutomatic.h"

namespace QUtility
{
    const QUtility::QSection *match_section(const char *calendarPath)
    {
        QUtility::QTimePoint *now = new QUtility::QTimePoint();

        char prev_date[12] = "";
        char this_date[12] = "";
        QUtility::match_trade_date(now->getTs(), this_date, prev_date, calendarPath);
        std::cout << "Now = " << *now << ", it is in \n"
                  << "('" << prev_date << "', '" << this_date << "')" << std::endl;
        QUtility::QSection *secD = new QUtility::QSection(this_date, prev_date, 'D');
        QUtility::QSection *secN = new QUtility::QSection(this_date, prev_date, 'N');
        QUtility::QSection *sec = NULL;
        if (secD->hasTimepoint(now))
        {
            std::cout << *secD << "is chosen" << std::endl;
            sec = secD;
            delete secN;
        }
        else if (secN->hasTimepoint(now))
        {
            std::cout << *secN << "is chosen" << std::endl;
            sec = secN;
            delete secD;
        }
        else
        {
            std::cout << "Section Night = " << *secN
                      << "Section Dday  = " << *secD
                      << "Now is in neither section, so a NULL pointer will be returned." << std::endl;
            delete secN;
            delete secD;
        }
        return sec;
    }
}