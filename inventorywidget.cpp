#include "inventorywidget.h"
#include <QLayout>

InventoryWidget::InventoryWidget(QWidget *parent): QWidget(parent)
{
    layout = new QVBoxLayout(this);
    setLayout(layout);
}

void InventoryWidget::onSelectedItem(int id) {
    emit selectItem(id);
}

void InventoryWidget::onDeletedItem(int id) {
    emit deleteItem(id);
}

void InventoryWidget::refresh(const Container<Item *> &inv) {

    clear();
    int pos = 0;
    for(auto it = inv.cbegin(); it != inv.cend(); ++it) {

        ItemWidget *i = new ItemWidget(this);
        i->setItem((*it)->getAttributes());

        connect(i, &ItemWidget::selectedItem, this, &InventoryWidget::onSelectedItem);
        connect(i, &ItemWidget::deletedItem, this, &InventoryWidget::onDeletedItem);

        itemsW.push_back(i);
        //layout->addWidget(i);
        layout->addWidget(i,pos);
        ++pos;
    }
}

void InventoryWidget::clear() {
    for (auto &elem : itemsW ) {
        if(elem) delete elem;
    }
    itemsW.clear();
}
