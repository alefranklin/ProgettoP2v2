#include "mainview.h"
#include "prova_main.h"
#include "controller.h"
#include "game.h"
#include "main_dialog.h"
#include "entergame.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include <QFile>

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

    bool exitLoop = false;
    bool new_game = true;

    while(!exitLoop){
        //se avvio una nuova partita
        if(new_game) {
            enter->cleanLabel();
            enter->exec();
        }

        if(player) {
            new_game = false;
            Game *g2 = new Game(player);
            Main_dialog w(new_game, g2);
            Controller c2(&w, g2);
            //partita iniziata -> se decido di uscire non aprirà di nuovo

            w.setWindowModality(Qt::ApplicationModal);
            w.show();
            a.exec();
            //TODO spostare dentro if(new_game)
            player = nullptr; //TODO cambiare in delete player;
            //successvivamente player sarà istanziato attraverso game e verrà eliminato una volta chiusa la finestra di gioco
            //l'istruzione sopra non sarà più necessaria
        } else {
            exitLoop = true;
        }
    }
    //if(player != nullptr) delete player;
    return 0;
}
