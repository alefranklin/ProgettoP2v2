#include "movementbuttoncontainer.h"

#include <QGridLayout>
#include<QPushButton>
#include <QDebug>

#include <QSignalMapper>
MovementButtonContainer::MovementButtonContainer(QWidget *parent) : QWidget(parent)
{
    //setto layout
    grid = new QGridLayout(this);
    setLayout(grid);
    //creo bottoni
    dir[0] = new QPushButton(QString("up"),this);
    dir[1] = new QPushButton(QString("down"),this);
    dir[2] = new QPushButton(QString("left"),this);
    dir[3] = new QPushButton(QString("right"),this);
    //inserisco bottoni nel layout
    grid->addWidget(dir[0],0,1);
    grid->addWidget(dir[1],1,1);
    grid->addWidget(dir[2],1,2);
    grid->addWidget(dir[3],1,0);
    //connetto i bottoni alla funzione che gestisce il click
    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect (dir[0],SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect (dir[1],SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect (dir[2],SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect (dir[3],SIGNAL(clicked()),signalMapper,SLOT(map()));

    signalMapper->setMapping(dir[0],QString('w'));
    signalMapper->setMapping(dir[1],QString('s'));
    signalMapper->setMapping(dir[2],QString('a'));
    signalMapper->setMapping(dir[3],QString('d'));

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(handleClick(QString)));
}


void MovementButtonContainer::handleClick(QString dir){
    emit buttonClicked(dir);
}
