#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include "entity.h"

/* questa classe serve per definire il widget per visualizzare
 * gli item di gioco nell'interfaccia grafica
 */
class ItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ItemWidget(QWidget *parent = nullptr);

signals:
    void selectedItem(int id);
    void deleteItem(int id);

public slots:
    void setItem(vector<Entity::Attribute> attributes);

    void clear();

private slots:
    void onClickSelect(int id);
    void onClickDelete(int id);

private:

    class IDButton: public QPushButton {
        Q_OBJECT
    public:
        explicit IDButton(QWidget *parent = nullptr);
        void setID(int id);

     signals:
        void buttonClicked(int id);

     private slots:
        void handleClick();

     private:
        int _id;
    };

    QGridLayout *layout;
    QLabel *lbl_name;       // nome oggetto
    QLabel *lbl_img;        // label che mostra l'immagine
    QTextEdit *lbl_info;    // info dell'item
    IDButton *btn_sel;      // pulsante per selezionare
    IDButton *btn_del;      // pulsante per eliminare
    QPixmap pix;            // immagine


};

#endif // ITEMWIDGET_H
