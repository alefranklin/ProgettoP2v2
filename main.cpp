#include "mainview.h"
#include "controller.h"
#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game g;
    MainView w(&g);
    Controller c(&g, &w);
    w.show();
    return a.exec();
}
