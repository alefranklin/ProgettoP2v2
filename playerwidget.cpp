#include "playerwidget.h"

#include "item.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent){
    setHidden(true);
    layout = new QVBoxLayout(this);
    layout->setMargin(0);

    //nome
    nome = new QLabel(this);
    nome->setStyleSheet("font-weight: bold; text-decoration: underline;");

    //hp
    QHBoxLayout *hpLayout = new QHBoxLayout(nullptr);
    hpLayout->addWidget(new QLabel("HP"));
    hp = new QProgressBar(this);
    hp->setOrientation(Qt::Orientation::Horizontal);
    hp->setFixedHeight(20);
    hp->setFixedWidth(200);
    hp->setTextVisible(false);
    QPalette hpPalette = QPalette();
    hpPalette.setColor(QPalette::Highlight, Qt::green);
    hp->setPalette(hpPalette);
    hpLayout->addWidget(hp);
    hpLabel = new QLabel(this);
    hpLabel->setFixedWidth(25);
    hpLayout->addWidget(hpLabel);

    //mp
    QHBoxLayout *mpLayout = new QHBoxLayout(nullptr);
    mpLayout->addWidget(new QLabel("MP"));
    mp = new QProgressBar(this);
    mp->setOrientation(Qt::Orientation::Horizontal);
    mp->setFixedHeight(20);
    mp->setFixedWidth(200);
    mp->setTextVisible(false);
    QPalette mpPalette = QPalette();
    mpPalette.setColor(QPalette::Highlight, Qt::blue);
    mp->setPalette(mpPalette);
    mpLayout->addWidget(mp);
    mpLabel = new QLabel(this);
    mpLabel->setFixedWidth(25);
    mpLayout->addWidget(mpLabel);
    //weapon widget
    weapon = new ItemWidget();
    armor = new ItemWidget();

    setFixedWidth(270);
    //setto tutto
    setLayout(layout);
    layout->addWidget(nome);
    layout->addLayout(hpLayout);
    layout->addLayout(mpLayout);
    layout->addWidget(weapon);
    layout->addWidget(armor);
}

void PlayerWidget::clear(){
    setHidden(true);
    nome->clear();
    hp->setValue(hp->maximum());
    mp->setValue(hp->maximum());
    hpLabel->clear();
    mpLabel->clear();
    weapon->clear();
    armor->clear();
}

void PlayerWidget::setFields(Character *c){
    clear();

    setHidden(false);

    //nome
    nome->setText(QString::fromStdString(c->getName()));

    //hp
    int hpNum = c->getVitaMax();
    hp->setRange(0,hpNum);
    hp->setValue(c->getVita());
    hpLabel->setText(QString::number(hpNum));

    //mp
    int mpNum = c->getManaMax();
    mp->setRange(0,mpNum);
    mp->setValue(c->getMana());
    mpLabel->setText(QString::number(mpNum));

    //equip widget
    weapon->setItem(c->getWeapon()->getAttributes());
    weapon->disable(true);
    armor->setItem(c->getArmor()->getAttributes());
    armor->disable(true);
}
