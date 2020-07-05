#include "itemwidget.h"

#include <QIcon>
#include <iostream>
#include <string>
#include <sstream>

ItemWidget::ItemWidget(QWidget *parent): QWidget(parent)
{
    layout = new QGridLayout(this);
    setLayout(layout);
    setFixedSize(300, 100);

    lbl_name = new QLabel(this);

    lbl_img = new QLabel(this);
    lbl_img->setAlignment(Qt::AlignCenter);

    lbl_info = new QTextEdit(this);
    lbl_info->setReadOnly(true);
    lbl_info->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lbl_info->setFrameStyle(QFrame::NoFrame);   // tolgo il bordo

    btn_sel = new IDButton(this);
    btn_sel->setToolTip("usa Item");

    btn_del = new IDButton(this);
    btn_del->setToolTip("elimina Item");
    btn_del->setIcon(QIcon(":/icon/del_icon"));

    //mettere
    layout->addWidget(lbl_img, 0, 0, 0, 3);
    layout->addWidget(lbl_name, 0, 1, 2, 0);
    layout->addWidget(lbl_info, 1, 1, 2, 2);
    layout->addWidget(btn_sel, 1, 3);
    layout->addWidget(btn_del, 1, 4);

    connect(btn_del, &IDButton::buttonClicked, this, &ItemWidget::onClickDelete);
    connect(btn_sel, &IDButton::buttonClicked, this, &ItemWidget::onClickSelect);

}

void ItemWidget::setItem(vector<Entity::Attribute> attributes) {

    clear();
    QString nome;

    for(auto &att : attributes) {
        if(att.name == "Immagine") {
            if(pix.load(QString::fromStdString(att.val))) {
                // setto l'immagine
                lbl_img->setPixmap(pix);
            }
        } else if(att.name == "Nome")
        {
            nome = QString::fromStdString(att.val);
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
    lbl_img->clear();
    lbl_info->clear();
}

void ItemWidget::onClickSelect(int id) {
    emit selectedItem(id);
}

void ItemWidget::onClickDelete(int id) {
    emit deleteItem(id);
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
