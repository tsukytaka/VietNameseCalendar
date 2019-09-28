#include <QCoreApplication>
#include <stdio.h>
#include <string>
#include <iostream>
#include <qimage.h>
#include "resourcemanager.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string str;
    QImage img;
    QString qstr;
    for (;;)
    {
        cout << "Input file name.(q:exit)\nInput:";
        cin >> str;
        if (str == "q")
        {
            return 0;
        }
        else if(str == "exit")
        {
            return 1;
        }
        img = ResourceManager::GetInstance()->getImage(str);
        if (img.isNull())
        {
            cout << "TheImage is not foumd.\n";
        }
        else
        {
            str = "../Output/" + str + ".png";
            qstr = QString::fromStdString(str);
            img.save(qstr);
            cout << "Save the image in Output Folder.\n";
        }
        cout << "\n";
    }
    return a.exec();
}
