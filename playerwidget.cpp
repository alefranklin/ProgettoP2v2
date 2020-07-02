#include "playerwidget.h"


PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent){
    layout = new QVBoxLayout(this);
    //nome
    nome = new QLabel("Nome Giocatore");
    nome->setStyleSheet("font-weight: bold; text-decoration: underline;");
    //hp
    QHBoxLayout *hpLayout = new QHBoxLayout(this);
    hpHead = new QLabel("HP");
    hpHead->setFixedWidth(20);
    hpLayout->addWidget(hpHead);
    hp = new QProgressBar(this);
    hp->setOrientation(Qt::Orientation::Horizontal);
    hp->setRange(0,100);
    hp->setValue(40);
    hp->setFixedHeight(20);
    hp->setFixedWidth(200);
    hp->setTextVisible(false);
    QPalette hpPalette = QPalette();
    hpPalette.setColor(QPalette::Highlight, Qt::green);
    hp->setPalette(hpPalette);
    hpLayout->addWidget(hp);
    hpLabel = new QLabel(this);
    hpLabel->setText("400");
    hpLabel->setFixedWidth(25);
    hpLayout->addWidget(hpLabel);
    //mp bar
    QHBoxLayout *mpLayout = new QHBoxLayout(this);
    mpHead = new QLabel("MP");
    mpHead->setFixedWidth(20);
    mpLayout->addWidget(mpHead);
    mp = new QProgressBar(this);
    mp->setOrientation(Qt::Orientation::Horizontal);
    mp->setRange(0,300);
    mp->setValue(40);
    mp->setFixedHeight(20);
    mp->setFixedWidth(200);
    mp->setTextVisible(false);
    QPalette mpPalette = QPalette();
    mpPalette.setColor(QPalette::Highlight, Qt::blue);
    mp->setPalette(mpPalette);
    mpLayout->addWidget(mp);
    mpLabel = new QLabel(this);
    mpLabel->setText("400");
    mpLabel->setFixedWidth(25);
    mpLayout->addWidget(mpLabel);
    //weapon widget
    weapon = new ItemWidget("Spada suprema","Arma",40,21,2);
    armor = new ItemWidget("Armatura della morte","Armatura",40);
    weapon->setFixedWidth(245);
    armor->setFixedWidth(245);

    //setto tutto
    setLayout(layout);
    layout->addWidget(nome);
    layout->addLayout(hpLayout);
    layout->addLayout(mpLayout);
    layout->addWidget(weapon);
    layout->addWidget(armor);
}

void PlayerWidget::setHealth(int h){
    hp->setValue(h);
    hpLabel->setText(QString::fromStdString(std::to_string(h)));
}

void PlayerWidget::setMana(int m){
    mp->setValue(m);
    mpLabel->setText(QString::fromStdString(std::to_string(m)));
}

void PlayerWidget::setMaximumHealth(int maxhp){
    hp->setMaximum(maxhp);
}

void PlayerWidget::setMaximumMana(int maxmp){
    mp->setMaximum(maxmp);
}

void PlayerWidget::setNome(QString name){
    nome->setText(name);
}

void PlayerWidget::clear(){
    nome->clear();
    hp->setValue(hp->maximum());
    mp->setValue(mp->maximum());
    hpLabel->clear();
    mpLabel->clear();
    weapon->clear();
    armor->clear();
}