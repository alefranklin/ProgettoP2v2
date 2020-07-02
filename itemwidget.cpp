#include "itemwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

ItemWidget::ItemWidget(QWidget *parent): QWidget(parent){
    nome = new QLabel("");
    tipo = new QLabel("");
    stat1Name = new QLabel("");
    stat1 = new QLabel("");
    stat2Name = new QLabel("");
    stat2 = new QLabel("");
    stat3Name = new QLabel("");
    stat3 = new QLabel("");

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

    clear();
}

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

ItemWidget::ItemWidget(Item *i, QWidget *parent) : QWidget(parent){
    if(Game::isArmor(i)){
        const Armor *a = dynamic_cast<const Armor*>(i);
        nome = new QLabel(a->getNome());
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
        nome = new QLabel(b->getNome());
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
        nome = new QLabel(s->getNome());
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
        nome = new QLabel(mw->getNome());
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
        nome = new QLabel(p->getNome());
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

void ItemWidget::change(Item *i){
    if(Game::isArmor(i)){
        const Armor *a = dynamic_cast<const Armor*>(i);
        nome->setText(a->getNome());
        tipo->setText("Armatura");
        stat1Name->setText("Difesa");
        stat1->setText(QString::number((a->getArmatura())));
        stat2Name->clear();
        stat2->clear();
        stat3Name->clear();
        stat3->clear();
    }
    if(Game::isBow(i)){
        const Bow *b = dynamic_cast<const Bow*>(i);
        nome->setText(b->getNome());
        tipo->setText("Arco");
        stat1Name->setText("Danno");
        stat1->setText(QString::number(b->getDamage()));
        stat2Name->setText("Frecce");
        stat2->setText(QString::number(b->getArrow()));
        stat3Name->clear();
        stat3->clear();
    }
    if(Game::isSword(i)){
        const Sword *s = dynamic_cast<const Sword*>(i);
        nome->setText(s->getNome());
        tipo->setText("Spada");
        stat1Name->setText("Danno");
        stat1->setText(QString::number(s->getDamage()));
        stat2Name->setText("Range");
        stat2->setText(QString::number(s->getRange()));
        stat3Name->clear();
        stat3->clear();
    }
    if(Game::isMagicWeapon(i)){
        const MagicWeapon *mw = dynamic_cast<const MagicWeapon*>(i);
        nome->setText(mw->getNome());
        tipo->setText("Arma Magica");
        stat1Name->setText("Danno");
        stat1->setText(QString::number(mw->getDamage()));
        stat2Name->setText("Effetto");
        stat2->setText(QString::number(mw->getEffect()));
        stat3Name->setText("Mana");
        stat3->setText(QString::number(mw->getMana()));
    }
}


