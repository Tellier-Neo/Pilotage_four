#include "Four.h"
#include <QtWidgets/QApplication>
#include "Include/Dask64.h"
#include <conio.h>
#include <iostream>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Four w;
    w.show();

    return a.exec();
}
