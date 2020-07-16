#include <QGridLayout>
#include "movewidget.h"

MoveWidget::MoveWidget(QWidget *parent) : QWidget(parent)
{
    //creo griglia e imposto layout
    grid = new QGridLayout(this);

    //creo bottoni e li connetto allo slot di MoveWidget
    UP = new QPushButton(this);
    LEFT = new QPushButton(this);
    DOWN = new QPushButton(this);
    RIGHT = new QPushButton(this);

    UP->setText("W");
    LEFT->setText("A");
    DOWN->setText("S");
    RIGHT->setText("D");

    UP->setShortcut(QKeySequence(Qt::Key_W));
    LEFT->setShortcut(QKeySequence(Qt::Key_A));
    DOWN->setShortcut(QKeySequence(Qt::Key_S));
    RIGHT->setShortcut(QKeySequence(Qt::Key_D));

    connect(UP, &QPushButton::clicked, this, &MoveWidget::clickedUP);
    connect(LEFT, &QPushButton::clicked, this, &MoveWidget::clickedLEFT);
    connect(DOWN, &QPushButton::clicked, this, &MoveWidget::clickedDOWN);
    connect(RIGHT, &QPushButton::clicked, this, &MoveWidget::clickedRIGHT);

    //inserisco i bottoni creati sopra nel layout
    grid->addWidget(UP,0,1);
    grid->addWidget(DOWN,1,1);
    grid->addWidget(LEFT,1,0);
    grid->addWidget(RIGHT,1,2);

    setFixedWidth(300);
    
    setLayout(grid);
}

MoveWidget::~MoveWidget()
{
    delete grid;
    delete UP;
    delete DOWN;
    delete LEFT;
    delete RIGHT;
}

void MoveWidget::setEnabled(bool enable){
    UP->setEnabled(enable);
    DOWN->setEnabled(enable);
    RIGHT->setEnabled(enable);
    LEFT->setEnabled(enable);
}

void MoveWidget::clickedUP() {
    emit emitDir('W');
}

void MoveWidget::clickedDOWN() {
    emit emitDir('S');
}

void MoveWidget::clickedRIGHT() {
    emit emitDir('D');
}

void MoveWidget::clickedLEFT() {
    emit emitDir('A');
}
