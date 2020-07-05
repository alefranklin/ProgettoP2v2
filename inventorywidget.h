#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include <QWidget>
#include <QVector>
#include "itemwidget.h"

#include "container.h"
#include "item.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>

class InventoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InventoryWidget(QWidget *parent = nullptr): QWidget(parent)
    {
        scroll = new QScrollArea(this);
        layout = new QVBoxLayout(this);

//        QPushButton *p;
//        for (int i =0 ; i < 20; i++) {
//            p = new QPushButton(QString::number(i), this);
//            layout->addWidget(p);
//        }

        setLayout(layout);
        //scroll->setLayout(layout);
    }

signals:
    void selectItem(int id);
    void deleteItem(int id);
private slots:
    void onSelectedItem(int id) {
        emit selectItem(id);
    }
    void onDeletedItem(int id) {
        emit deleteItem(id);
    }

public slots:
    void refresh(const Container<Item*> &inv) {

        clear();

        for(auto it = inv.cbegin(); it != inv.cend(); ++it) {
            ItemWidget *i = new ItemWidget(this);
            i->setItem((*it)->getAttributes());

            connect(i, &ItemWidget::selectedItem, this, &InventoryWidget::onSelectedItem);
            connect(i, &ItemWidget::deletedItem, this, &InventoryWidget::onDeletedItem);

            itemsW.push_back(i);
            //scroll->setWidget(i);
            layout->addWidget(i);
        }
    }

    void clear() {
        for (auto &elem : itemsW ) {
            if(elem) delete elem;
        }
        itemsW.clear();
    }

private:
    QVector<ItemWidget*> itemsW;
    QScrollArea *scroll;
    QVBoxLayout *layout;

};

#endif // INVENTORYWIDGET_H
