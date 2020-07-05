#include "itemwidget.h"

#include <QIcon>
#include <iostream>
#include <string>
#include <sstream>

ItemWidget::ItemWidget(QWidget *parent): QWidget(parent)
{
    layout = new QVBoxLayout(this);
    QHBoxLayout *bodyLayout = new QHBoxLayout(nullptr);
    QVBoxLayout *btnLayout = new QVBoxLayout(nullptr);

    setFixedSize(270, 100);
    //setStyleSheet("border: solid 1px red;");

    lbl_name = new QLabel(this);
    lbl_name->setStyleSheet("font-weight: bold; text-decoration: underline");
    lbl_name->setFixedHeight(20);

    lbl_img = new QPushButton(this);
    lbl_img->setFlat(true);
    lbl_img->setEnabled(true);
    lbl_img->setFixedSize(50,50);

    lbl_info = new QTextEdit(this);
    lbl_info->setFixedHeight(100);
    lbl_info->setReadOnly(true);
    lbl_info->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lbl_info->setFrameStyle(QFrame::NoFrame);// tolgo il bordo

    btn_sel = new IDButton(this);
    btn_sel->setToolTip("usa Item");
    btn_sel->setIcon(QIcon(":/icon/ok_icon"));

    btn_del = new IDButton(this);
    btn_del->setToolTip("elimina Item");
    btn_del->setIcon(QIcon(":/icon/del_icon"));

    btnLayout->addWidget(btn_sel);
    btnLayout->addWidget(btn_del);

    bodyLayout->addWidget(lbl_img);
    bodyLayout->addWidget(lbl_info);
    bodyLayout->addLayout(btnLayout);

    layout->addWidget(lbl_name);
    layout->addLayout(bodyLayout);



    connect(btn_del, &IDButton::buttonClicked, this, &ItemWidget::onClickDelete);
    connect(btn_sel, &IDButton::buttonClicked, this, &ItemWidget::onClickSelect);

}

void ItemWidget::setItem(vector<Entity::Attribute> attributes) {

    clear();
    QString nome;

    for(auto &att : attributes) {
        if(att.name == "Immagine") {
                lbl_img->setIcon(QIcon(QString::fromStdString(att.name)));
        } else if(att.name == "Nome")
        {
            nome = QString::fromStdString(att.val);
            lbl_name->setText(nome);
        } else if(att.name == "Tipo")
        {
            nome += "["+QString::fromStdString(att.val)+"]";
        } else if(att.name == "ID")
        {
            int i;
            std::istringstream(att.val) >> i;
            btn_del->setID(i);
            btn_sel->setID(i);
        }
        else {
            lbl_info->append(QString::fromStdString(att.name)+": "+QString::fromStdString(att.val));
        }
    }

    lbl_name->setText(nome);
}

void ItemWidget::clear(){
    lbl_name->clear();
    lbl_img->setIcon(QIcon());
    lbl_info->clear();
}

void ItemWidget::onClickSelect(int id) {
    emit selectedItem(id);
}

void ItemWidget::onClickDelete(int id) {
    emit deletedItem(id);
}

IDButton::IDButton(QWidget *parent): QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &IDButton::handleClick);
}

void IDButton::setID(int id)
{
    _id = id;
}

void IDButton::handleClick(){
    emit buttonClicked(_id);
}
