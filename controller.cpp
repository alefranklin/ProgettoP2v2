#include "controller.h"

Controller::Controller(Main_dialog* v, Game *g, QObject *parent) : QObject(parent), model(g), view(v)
{
    /*
     connetto i vari segnali agli slot
     connect(&emitter,  &MyEmitter::somethingChanged,
            &receiver, &MyHandler::onSomethingChanged);
    */

    // collego sistema di dialogo
    //connect(model, &Game::dialogOut, view, &MainView::printString);

    // collego sistema di scelte
    //connect(model, &Game::choiceOut, view, &MainView::showChoice);   // gestisco scelte da model a view
    //connect(view, &MainView::emitChoice, model, &Game::choiceDone);  // gestisco la scelta fatta da view a model

    // avvio il dialogo quando arriva il segnale da view
    //connect(view, &MainView::emitDialog, this, &Controller::avviaDialogo);


    //aggiungo la musica
    /*
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/track1"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(50);
    music->play();
    // connetto il segnale della view al cambio di volume
    connect(view, &MainView::volumeChanged, music, &QMediaPlayer::setVolume);
    */


}

Controller::~Controller()
{
    delete model;
    delete view;
}

//void Controller::avviaDialogo()
//{
//    model->dialog("dialogo avviato");
//}
