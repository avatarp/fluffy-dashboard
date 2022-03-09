#include <QApplication>
#include <iostream>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if __cplusplus >= 202002L
    // C++20 (and later) code
    std::cout << "C++20 (and later)" << std::endl;
#endif
    std::cout<<__cplusplus<<std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
