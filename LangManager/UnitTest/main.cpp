#include <QCoreApplication>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "langmng.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string str = "";
    std::string out = "";
    uint32_t id = 0;
    for (;;)
    {
        str = "";
        out = "";
        id = 0;
        std::cout << "\"exit\"入力で終了\n文字列ID:";
        std::cin >> str;
        if (str == "exit" || str == "q")
        {
            break;
        }
        else if (str == "english")
        {
            std::cout << "Change Disp Langage to English.\n";
            LangMng::GetInstance()->setCurrentLang(1);
        }
        else if (str == "japanese")
        {
            std::cout << "表示言語を日本語に設定\n";
            LangMng::GetInstance()->setCurrentLang(0);
        }
        else if (!std::all_of(str.cbegin(), str.cend(), isdigit))
        {
            std::cout << "Input is not Digit.\n";
        }
        else
        {
            id = std::atoi(str.c_str());
            out = LangMng::GetInstance()->getStr(id);
            std::cout << out;
        }
        std::cout << "\n";
    }
    return a.exec();
}
