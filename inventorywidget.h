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
#include <QListWidget>

class InventoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InventoryWidget(QWidget *parent = nullptr);

signals:
    void selectItem(int id);
    void deleteItem(int id);
private slots:
    void onSelectedItem(int id);
    void onDeletedItem(int id);

public slots:
    void refresh(const Container<Item*> &inv);

    void clear();

private:
    QVector<ItemWidget*> itemsW;
    QVBoxLayout *layout;

};

#endif // INVENTORYWIDGET_H
