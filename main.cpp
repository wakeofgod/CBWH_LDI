#include "mainwindow.h"

#include <QApplication>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef Q_OS_WIN
#if defined(DEBUG) || defined(_DEBUG)
    AllocConsole();
    // 重定向标准输出和标准错误到控制台
    FILE *dummy;
    freopen_s(&dummy, "CONOUT$", "w", stdout);
    freopen_s(&dummy, "CONOUT$", "w", stderr);
#endif
#endif
    //加载样式文件
    QFile file(":/resource/css/blus.css");
    if(file.open(QFile::ReadOnly))
    {
        QString qss = file.readAll();
        file.close();
        a.setStyleSheet(qss);
    }
    MainWindow w;
    //w.show();
    w.showMaximized();
    return a.exec();
}
