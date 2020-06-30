#include "movewidget.h"

MoveWidget::MoveWidget(QWidget *parent) : QWidget(parent) {

    //creo griglia e imposto layout
    grid = new QGridLayout(this);
    setLayout(grid);

    //creo bottoni e li connetto allo slot di MoveWidget
    UP = new MoveButton('W',this);
    UP->setShortcut(QKeySequence(Qt::Key_W));
    connect(UP, &MoveButton::buttonClicked, this, &MoveWidget::dirPressed);

    LEFT = new MoveButton('A',this);
    LEFT->setShortcut(QKeySequence(Qt::Key_A));
    connect(LEFT, &MoveButton::buttonClicked, this, &MoveWidget::dirPressed);

    DOWN = new MoveButton('S',this);
    DOWN->setShortcut(QKeySequence(Qt::Key_S));
    connect(DOWN, &MoveButton::buttonClicked, this, &MoveWidget::dirPressed);

    RIGHT = new MoveButton('D',this);
    RIGHT->setShortcut(QKeySequence(Qt::Key_D));
    connect(RIGHT, &MoveButton::buttonClicked, this, &MoveWidget::dirPressed);

    //inserisco i bottoni creati sopra nel layout
    grid->addWidget(UP,0,1);
    grid->addWidget(DOWN,1,1);
    grid->addWidget(LEFT,1,0);
    grid->addWidget(RIGHT,1,2);
}

void MoveWidget::dirPressed(char dir) {
    emit emitDir(dir);
}

void MoveWidget::setEnabled(bool enable){
    UP->setEnabled(enable);
    DOWN->setEnabled(enable);
    RIGHT->setEnabled(enable);
    LEFT->setEnabled(enable);
}
