#include "QAutomatic.h"

namespace QUtility
{
    const QSection *match_section(const char *calendarPath)
    {
        QTimestamp now;
        char prev_date[12] = "";
        char this_date[12] = "";
        match_trade_date(now, this_date, prev_date, calendarPath);
        std::cout << "Now = " << now << ", it is in \n"
                  << "('" << prev_date << "', '" << this_date << "')" << std::endl;
        QSection *secD = new QSection(this_date, prev_date, 'D');
        QSection *secN = new QSection(this_date, prev_date, 'N');
        QSection *sec = NULL;
        if (secD->hasTimepoint(&now))
        {
            std::cout << *secD << "is chosen" << std::endl;
            sec = secD;
            delete secN;
        }
        else if (secN->hasTimepoint(&now))
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

    QContractsReader::QContractsReader(const char *subscribedPath)
    {
        FILE *file = fopen(subscribedPath, "r");
        if (file == NULL)
        {
            std::cout << subscribedPath << "Does not exist, please check again" << std::endl;
            exit(EXIT_FAILURE);
        }

        contracts = new char *[800];
        char line[24];
        char tmp[8];
        _size = 0;
        while (fgets(line, sizeof(line), file))
        {
            if (std::sscanf(line, "%s\r\n", tmp) == 1)
            {
                contracts[_size] = new char[8];
                strcpy(contracts[_size], tmp);
                _size++;
            }
        }
        fclose(file);
    }

    void QContractsReader::Display() const
    {
        std::cout << _size << " contracts are loaded" << std::endl;
        for (unsigned i = 0; i < _size; i++)
            std::cout << contracts[i] << std::endl;
    }

    // ---------------------
    // ------ QWriter ------
    // ---------------------

    QWriter::QWriter(const char *mdSaveRootDir, const QSection *section)
    {
        _section = section;
        _watch = new QTimestamp();
        std::strcpy(_mdSaveRootDir, mdSaveRootDir);

        char pathFile[240];
        std::strcpy(pathFile, _mdSaveRootDir);
        if (pathFile[std::strlen(pathFile) - 1] != '/')
            std::strcat(pathFile, "/");
        // pathFile = "/mnt/data/trade/ticks/"

        std::strncat(pathFile, _section->GetTradeDate(), 4);
        std::strcat(pathFile, "/");
        checkAndMkdir(pathFile);
        // pathFile = "/mnt/data/trade/ticks/2025/"

        std::strncat(pathFile, _section->GetTradeDate() + 4, 2);
        std::strcat(pathFile, "/");
        checkAndMkdir(pathFile);
        // pathFile = "/mnt/data/trade/ticks/2025/01/"

        char filename[20] = "YYYYMMDD.ticks.csv";
        std::strncpy(filename, _section->GetTradeDate(), 8);
        std::strcat(pathFile, filename);
        // pathFile = "/mnt/data/trade/ticks/2025/01/20250109.ticks.csv"

        std::cout << "... data is saved in:" << pathFile << std::endl;
        file = fopen(pathFile, "a");
    }

    bool QWriter::Check(CThostFtdcDepthMarketDataField *pDmd) const
    {
        _watch->reSync();
        if (!_section->isValid(_watch))
            return false;

        if ((pDmd->Volume < 0) || (pDmd->BidVolume1 < 0) || (pDmd->AskVolume1 < 0))
            return false;

        if (pDmd->UpdateMillisec < 0 || pDmd->UpdateMillisec > 1000)
            return false;

        // Bid and Ask price
        if (pDmd->BidPrice1 > 1e9)
            pDmd->BidPrice1 = -1;
        if (pDmd->AskPrice1 > 1e9)
            pDmd->AskPrice1 = -1;

        // Highest and Lowest price
        if (pDmd->HighestPrice > 1e9)
            pDmd->HighestPrice = -1;
        if (pDmd->LowestPrice > 1e9)
            pDmd->LowestPrice = -1;

        return true;
    }

    const char *QWriter::GetActionDate(const char *update_time) const
    {
        if (_section->GetType() == 'N')
        {
            if (std::strcmp(update_time, "03:00:00") < 0)
                return _section->GetSecLblNgt1();
            else
                return _section->GetSecLblNgt0();
        }
        else
            return _section->GetSecLblDay();
    }

    void QWriter::Write(CThostFtdcDepthMarketDataField *pDmd)
    {
        if (Check(pDmd))
        {
            const char *action_date = GetActionDate(pDmd->UpdateTime);
            fprintf(
                file, "%ld,%s,%s.%03d,%s,%.4f,%d,%.2f,%.2f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%.4f,%d\n",
                _watch->getTs(), action_date, pDmd->UpdateTime, pDmd->UpdateMillisec,
                pDmd->InstrumentID,
                pDmd->LastPrice,
                pDmd->Volume,
                pDmd->Turnover,
                pDmd->OpenInterest,
                pDmd->HighestPrice,
                pDmd->LowestPrice,
                pDmd->UpperLimitPrice,
                pDmd->LowerLimitPrice,
                pDmd->BidPrice1,
                pDmd->BidVolume1,
                pDmd->AskPrice1,
                pDmd->AskVolume1);
        }
    }

    void QWriter::Close()
    {
        fclose(file);
    }
}