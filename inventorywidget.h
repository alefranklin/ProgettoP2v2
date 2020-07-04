#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QVBoxLayout>

class InventoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InventoryWidget(QWidget *parent = nullptr): QWidget(parent)
    {
        layout = new QVBoxLayout();

        QPushButton *p;
        for (int i =0 ; i < 20; i++) {
            p = new QPushButton(QString::number(i), this);
            layout->addWidget(p);
        }

        setLayout(layout);
    }

signals:

public slots:

private:

    QVBoxLayout *layout;

};

#endif // INVENTORYWIDGET_H
