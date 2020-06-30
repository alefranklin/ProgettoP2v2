#include "controller.h"

Controller::Controller(Game *g, MainView* v, QObject *parent) : QObject(parent), model(g), view(v)
{
    /*
     connetto i vari segnali agli slot
     connect(&emitter,  &MyEmitter::somethingChanged,
            &receiver, &MyHandler::onSomethingChanged);
    */

    // collego sistema di dialogo
    connect(model, &Game::dialogOut, this, &Controller::onDialogOut);

    // collego sistema di scelte
    connect(model, &Game::choiceOut, this, &Controller::onChoiceOut);   // gestisco scelte da model a view
    connect(view, &MainView::emitChoice, this, &Controller::onChoiceIn);  // gestisco la scelta fatta da view a model

    // avvio il dialogo quando arriva il segnale da view
    connect(view, &MainView::emitDialog, this, &Controller::avviaDialogo);

}

Controller::~Controller()
{
    delete model;
    delete view;
}

void Controller::onDialogOut(QString s)
{
    view->printString(s);
}

void Controller::onChoiceOut(Choice c)
{
    view->showChoice(c);
}

void Controller::onChoiceIn(Choice c)
{
    model->choiceDone(c);
}

void Controller::avviaDialogo()
{
    model->dialog("dialogo avviato");
}
