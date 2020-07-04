#include "mainview.h"
#include "main_view.h"
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

    Game* game = new Game(nullptr);
    EnterGame *enter = new EnterGame(&game);

    //qDebug() << "enter game _ main 1 : " << &game;

    bool exitLoop = false;
    bool new_game = true;

    while(!exitLoop){
        //avvio una nuova partita
        if(new_game) {
            //if(!game) game = new Game(nullptr)
            //enter->setGame(&game);
            enter->cleanEnter();
            enter->exec();
        }

        //se istanzio player allora avvio la partita
        if(game->getPlayer()) {
            new_game = false;

            Main_dialog w(new_game, game);
            //Controller c2(&w, game);
            //partita iniziata -> se decido di uscire non aprirà di nuovo

            w.setWindowModality(Qt::ApplicationModal);
            w.show();
            a.exec();

            //TROVARE UN MODO PER CANCELLARE LE COSE NON ESSENZIALI DA GAME SE SI FA NEW GAME
            //MEMEORY LEAK -> game non distrugge player

            //forse fixato il memory leak
            game->setPgNull();
            //qDebug() << "enter game _ main 2 : " << &game;
            //successvivamente player sarà istanziato attraverso game e verrà eliminato una volta chiusa la finestra di gioco
            //l'istruzione sopra non sarà più necessaria
        } else {
            exitLoop = true;
        }
    }
    return 0;
}
