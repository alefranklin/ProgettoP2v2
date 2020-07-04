#include "itemwidget.h"

ItemWidget::ItemWidget(QString n, QString t, int s1, int s2, int s3, QWidget *parent) : QWidget(parent)
{
    nome = new QLabel(n);
    tipo = new QLabel(t);
    stat1Name = new QLabel("Stat 1");
    stat1 = new QLabel(QString::number(s1));
    stat2Name = new QLabel("Stat 2");
    stat2 = new QLabel(QString::number(s2));
    stat3Name = new QLabel("Stat 3");
    stat3 = new QLabel(QString::number(s3));

    QVBoxLayout *main = new QVBoxLayout(this);
    setMinimumWidth(200);
    setLayout(main);
    nome->setStyleSheet("font-weight: bold;");
    main->addWidget(nome);

    QHBoxLayout *body = new QHBoxLayout();
    main->addLayout(body);
    body->addWidget(tipo);
    tipo->setMaximumWidth(70);

    QVBoxLayout *stats = new QVBoxLayout();
    body->addLayout(stats);

    QHBoxLayout *s1Layout = new QHBoxLayout();
    s1Layout->addWidget(stat1Name);
    s1Layout->addWidget(stat1);

    QHBoxLayout *s2Layout = new QHBoxLayout();
    s2Layout->addWidget(stat2Name);
    s2Layout->addWidget(stat2);

    QHBoxLayout *s3Layout = new QHBoxLayout();
    s3Layout->addWidget(stat3Name);
    s3Layout->addWidget(stat3);

    stats->addLayout(s1Layout);
    stats->addLayout(s2Layout);
    stats->addLayout(s3Layout);
}

void ItemWidget::clear(){
    nome->clear();
    tipo->clear();
    stat1Name->clear();
    stat2Name->clear();
    stat3Name->clear();
    stat1->clear();
    stat2->clear();
    stat3->clear();
}


//aggiunta per gui dinamica

ItemWidget::ItemWidget(Item *i, QWidget *parent) : QWidget(parent){
    if(Game::isArmor(i)){
        const Armor *a = dynamic_cast<const Armor*>(i);
        nome = new QLabel(QString::fromStdString(a->getNome()));
        tipo = new QLabel("Armatura");
        stat1Name = new QLabel("Difesa");
        stat1 = new QLabel(QString::number((a->getArmatura())));
        stat2Name = new QLabel("");
        stat2 = new QLabel("");
        stat3Name = new QLabel("");
        stat3 = new QLabel("");
    }
    if(Game::isBow(i)){
        const Bow *b = dynamic_cast<const Bow*>(i);
        nome = new QLabel(QString::fromStdString(b->getNome()));
        tipo = new QLabel("Arco");
        stat1Name = new QLabel("Danno");
        stat1 = new QLabel(QString::number(b->getDamage()));
        stat2Name = new QLabel("Frecce");
        stat2 = new QLabel(QString::number(b->getArrow()));
        stat3Name = new QLabel("");
        stat3 = new QLabel("");
    }
    if(Game::isSword(i)){
        const Sword *s = dynamic_cast<const Sword*>(i);
        nome = new QLabel(QString::fromStdString(s->getNome()));
        tipo = new QLabel("Spada");
        stat1Name = new QLabel("Danno");
        stat1 = new QLabel(QString::number(s->getDamage()));
        stat2Name = new QLabel("Range");
        stat2 = new QLabel(QString::number(s->getRange()));
        stat3Name = new QLabel("");
        stat3 = new QLabel("");
    }
    if(Game::isMagicWeapon(i)){
        const MagicWeapon *mw = dynamic_cast<const MagicWeapon*>(i);
        nome = new QLabel(QString::fromStdString(mw->getNome()));
        tipo = new QLabel("Arma Magica");
        stat1Name = new QLabel("Danno");
        stat1 = new QLabel(QString::number(mw->getDamage()));
        stat2Name = new QLabel("Effetto");
        stat2 = new QLabel(QString::number(mw->getEffect()));
        stat3Name = new QLabel("Mana");
        stat3 = new QLabel(QString::number(mw->getMana()));
    }
    if(Game::isPotion(i)){
        const Potion *p = dynamic_cast<const Potion*>(i);
        nome = new QLabel(QString::fromStdString(p->getNome()));
        tipo = new QLabel("Pozione");
        stat1Name = new QLabel("Effetto");
        stat1 = new QLabel(QString::number((p->getEffect())));
        stat2Name = new QLabel("");
        stat2 = new QLabel("");
        stat3Name = new QLabel("");
        stat3 = new QLabel("");
    }
    QVBoxLayout *main = new QVBoxLayout(this);
    setMinimumWidth(200);
    setLayout(main);
    nome->setStyleSheet("font-weight: bold;");
    main->addWidget(nome);
    QHBoxLayout *body = new QHBoxLayout(this);
    main->addLayout(body);
    body->addWidget(tipo);
    tipo->setMaximumWidth(70);
    QVBoxLayout *stats = new QVBoxLayout(this);
    body->addLayout(stats);
    QHBoxLayout *s1Layout = new QHBoxLayout(this);
    s1Layout->addWidget(stat1Name);
    s1Layout->addWidget(stat1);
    QHBoxLayout *s2Layout = new QHBoxLayout(this);
    s2Layout->addWidget(stat2Name);
    s2Layout->addWidget(stat2);
    QHBoxLayout *s3Layout = new QHBoxLayout(this);
    s3Layout->addWidget(stat3Name);
    s3Layout->addWidget(stat3);
    stats->addLayout(s1Layout);
    stats->addLayout(s2Layout);
    stats->addLayout(s3Layout);
}
