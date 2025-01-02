#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

namespace QUtility
{
    class ConfigMd
    {
    private:
        char _calendarPath[240];
        char _accountFilePath[240];
        char _mdSaveRootDir[240];
        char _subscribedFile[240];

    public:
        ConfigMd(const char *config_path);
        unsigned match(const char *text_line);
        const char *GetCalendarPath() const { return _calendarPath; }
        const char *GetAccountFilePath() const { return _accountFilePath; }
        const char *GetMdSaveRootDir() const { return _mdSaveRootDir; }
        const char *GetSubscribedFile() const { return _subscribedFile; }
        void display() const;
    };
}