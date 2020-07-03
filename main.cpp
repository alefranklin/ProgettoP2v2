#include "mainview.h"
#include "prova_main.h"
#include "controller.h"
#include "game.h"
#include "main_dialog.h"
#include "entergame.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //mostro lo splash screen
    QPixmap pixmap(":/splash/splash_img");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    //splash.show();

    //Game g;
    //MainView w(&g);
    //Controller c(&g, &w);

    //QTimer::singleShot(200, &splash, SLOT(close()));   // chiudo lo spalsh screen
    //QTimer::singleShot(200, &w, SLOT(show()));         // e poi apro la finestra


    //QTimer::singleShot(500, &splash, SLOT(close()));   // chiudo lo spalsh screen

    Player *player = nullptr;
    EnterGame *enter = new EnterGame(&player);


    //enter->cleanLabel();
    //enter->exec();

    //qDebug() << player->getName();
//    if(player){
//        Game *g2 = new Game();
//        Main_dialog w2(g2);
//        Controller c2(&w2, g2);
//        QTimer::singleShot(200, &w2, SLOT(show()));
//        a.exec();// e poi apro la finestra
//    }

    bool exit = false;
    while(!exit){
        enter->cleanLabel();
        enter->exec();
        if(player) {
            bool new_game = false;
            Game *g2 = new Game();
            Main_dialog w(new_game, g2);
            Controller c2(&w, g2);
            //w.setWindowModality(Qt::ApplicationModal);
            w.show();
            a.exec();
            if(!new_game) exit = true;
        } else {
            exit = true;
        }
    }
    //if(player != nullptr) delete player;
    return 0;
}
