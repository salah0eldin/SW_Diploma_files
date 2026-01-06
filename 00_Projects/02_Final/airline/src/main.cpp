#include "airline.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    airline w;
    w.show();
    return a.exec();
}
