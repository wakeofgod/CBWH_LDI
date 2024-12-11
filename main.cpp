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
    MainWindow w;
    //w.show();
    w.showMaximized();
    return a.exec();
}
