#include "mapwidget.h"
#include <QPushButton>

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    /* setto il backgroud */
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(86,86,86)); //#565656
    setAutoFillBackground(true);
    setPalette(pal);

    /* creo il layout e aggiungo gli elementi*/
    layout = new QGridLayout(this);
    layout->setSpacing(1);

    /* setto il layout appena creata al
     * Widget in modo da avere una diposizione degli oggetti
     */
    setLayout(layout);
}

void MapWidget::setMap(char **mappa, int w, int h)
{
    QPalette pal;

    /*fare una funzione per raggruppare le istruzioni dei case*/

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            QPushButton *b = new QPushButton(this);
            b->setFlat(true);
            switch (mappa[i][j]) {
                case '$':
                    b->setToolTip("tesoro");
                    // setto background
                    pal = b->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::yellow));
                    b->setAutoFillBackground(true);
                    b->setPalette(pal);
                    break;
                case '@':
                    b->setToolTip("mostro");
                    // setto background
                    pal = b->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::darkGreen));
                    b->setAutoFillBackground(true);
                    b->setPalette(pal);
                    break;
                case 'P':
                    b->setToolTip("Tu");
                    // setto background
                    pal = b->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::red));
                    b->setAutoFillBackground(true);
                    b->setPalette(pal);
                    break;
                default:
                    b->setDisabled(true);
                    // setto background
                    pal = b->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::darkGray));
                    b->setAutoFillBackground(true);
                    b->setPalette(pal);
                    break;
            }
            layout->addWidget(b, i, j);
        }
    }


}
