#include "mainview.h"
#include "prova_main.h"
#include "controller.h"
#include "game.h"
#include "main_dialog.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //mostro lo splash screen
    QPixmap pixmap(":/splash/splash_img");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    Game g;
    MainView w(&g);
    Controller c(&g, &w);

    QTimer::singleShot(200, &splash, SLOT(close()));   // chiudo lo spalsh screen
    //QTimer::singleShot(200, &w, SLOT(show()));         // e poi apro la finestra

    Game g2;
    Main_dialog w2(&g2);
    //Controller c2(&g2, &w2);

    QTimer::singleShot(200, &splash, SLOT(close()));   // chiudo lo spalsh screen
    QTimer::singleShot(200, &w2, SLOT(show()));         // e poi apro la finestra

    return a.exec();
}
