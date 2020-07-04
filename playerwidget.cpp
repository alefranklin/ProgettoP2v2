#include "playerwidget.h"



PlayerWidget::PlayerWidget(Character *c, QWidget *parent) : QWidget(parent){
    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    //nome
    nome = new QLabel(c->getName());
    int hpNum = c->getVita();
    int mpNum = c->getMana();
    nome->setStyleSheet("font-weight: bold; text-decoration: underline;");
    //hp
    QHBoxLayout *hpLayout = new QHBoxLayout(nullptr);
    hpLayout->addWidget(new QLabel("HP"));
    hp = new QProgressBar(this);
    hp->setOrientation(Qt::Orientation::Horizontal);
    hp->setRange(0,hpNum);
    hp->setValue(hp->maximum());
    hp->setFixedHeight(20);
    hp->setFixedWidth(200);
    hp->setTextVisible(false);
    QPalette hpPalette = QPalette();
    hpPalette.setColor(QPalette::Highlight, Qt::green);
    hp->setPalette(hpPalette);
    hpLayout->addWidget(hp);
    hpLabel = new QLabel(this);
    hpLabel->setText(QString::number(hpNum));
    hpLabel->setFixedWidth(25);
    hpLayout->addWidget(hpLabel);
    //mp
    QHBoxLayout *mpLayout = new QHBoxLayout(nullptr);
    mpLayout->addWidget(new QLabel("MP"));
    mp = new QProgressBar(this);
    mp->setOrientation(Qt::Orientation::Horizontal);
    mp->setRange(0,mpNum);
    mp->setValue(mp->maximum());
    mp->setFixedHeight(20);
    mp->setFixedWidth(200);
    mp->setTextVisible(false);
    QPalette mpPalette = QPalette();
    mpPalette.setColor(QPalette::Highlight, Qt::blue);
    mp->setPalette(mpPalette);
    mpLayout->addWidget(mp);
    mpLabel = new QLabel(this);
    mpLabel->setText(QString::number(mpNum));
    mpLabel->setFixedWidth(25);
    mpLayout->addWidget(mpLabel);
    //weapon widget
    weapon = new ItemWidget(c->getWeapon());
    armor = new ItemWidget(c->getArmor());
    setFixedWidth(270);
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
    mp->setValue(hp->maximum());
    hpLabel->clear();
    mpLabel->clear();
    weapon->clear();
    armor->clear();
}

void PlayerWidget::onShowDetailOf(QVector<Entity*> e){

}
