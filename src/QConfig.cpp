#include "QConfig.h"

namespace QUtility
{
    ConfigMd::ConfigMd(const char * config_path)
    {
        char text_line[240];
        std::ifstream fin;
        fin.open(config_path, std::ios_base::in);
        unsigned res = 0;
        while (fin.peek() != EOF)
        {
            fin.getline(text_line, sizeof(text_line));
            res += match(text_line);
        }
        display();
        if (res != 15) // 15 = 1 + 2 + 4 + 8
        {
            std::cout << "Failed to initialize configuration" << std::endl;
            std::cout << "Please check again" << std::endl;
            std::exit(-1);
        }
    }

    void ConfigMd::display() const
    {
        std::cout << "MD CONFIG SUMMARY:" << std::endl;
        std::cout << "------CALENDAR PATH    :" << _calendarPath << std::endl;
        std::cout << "------ACCOUNT FILE PATH:" << _accountFilePath << std::endl;
        std::cout << "------MD SAVE ROOT DIR :" << _mdSaveRootDir << std::endl;
        std::cout << "------SUBSCRIBED FILE  :" << _subscribedFile << std::endl;
    }

    unsigned ConfigMd::match(const char *text_line)
    {
        char key[240];
        char val[240];
        sscanf(text_line, "%[^=]=%s", key, val);
        if (std::strcmp(key, "calendarPath") == 0)
        {
            strcpy(_calendarPath, val);
            return 1;
        }
        if (std::strcmp(key, "accountFilePath") == 0)
        {
            strcpy(_accountFilePath, val);
            return 2;
        }
        if (std::strcmp(key, "mdSaveRootDir") == 0)
        {
            strcpy(_mdSaveRootDir, val);
            return 4;
        }
        if (std::strcmp(key, "subscribedFile") == 0)
        {
            strcpy(_subscribedFile, val);
            return 8;
        }
        return 0;
    }
}