#include "movebutton.h"

MoveButton::MoveButton(char d, QWidget *parent): QPushButton(parent), dir(d){
    setText(QString(dir));
    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void MoveButton::handleClick(){
    emit buttonClicked(dir);
}
