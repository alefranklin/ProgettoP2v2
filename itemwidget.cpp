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
    stat3Name = new QLabel("Stat 3");
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
    stats->addLayout(s3Layout);}

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
