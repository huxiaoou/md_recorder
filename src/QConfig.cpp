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
        if (res != 7)
        {
            std::cout << "Fail to initialize configuration" << std::endl;
            std::cout << "Please check again" << std::endl;
            std::exit(-1);
        }
    }

    void ConfigMd::display() const
    {
        std::cout << "MD CONFIG SUMMARY:" << std::endl;
        std::cout << "------ACCOUNT FILE PATH:" << _accountFilePath << std::endl;
        std::cout << "------MD SAVE ROOT DIR :" << _mdSaveRootDir << std::endl;
        std::cout << "------SUBSCRIBED FILE  :" << _subscribedFile << std::endl;
    }

    unsigned ConfigMd::match(const char *text_line)
    {
        char var_name[240];
        char var_val[240];
        sscanf(text_line, "%[^=]=%s", var_name, var_val);
        if (std::strcmp(var_name, "accountFilePath") == 0)
        {
            strcpy(_accountFilePath, var_val);
            return 1;
        }
        if (std::strcmp(var_name, "mdSaveRootDir") == 0)
        {
            strcpy(_mdSaveRootDir, var_val);
            return 2;
        }
        if (std::strcmp(var_name, "subscribedFile") == 0)
        {
            strcpy(_subscribedFile, var_val);
            return 4;
        }
        return 0;
    }
}