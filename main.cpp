#include "mainview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game g;
    MainView w(&g);
    w.show();
    return a.exec();
}
