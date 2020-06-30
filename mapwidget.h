#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QVector>

#include <entity.h>
#include "map.h"
#include "tilebutton.h"


class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr, int min = 10, int max = 30, int val = 15);
    ~MapWidget() = default;

signals:
    // invio il segnale per cambiare grandezza della minimappa
    void setMiniMapSize(int dim);

    // invio il segnale per avere info sull'Entity presente nel Tile cliccato
    void showDetailsOf(QVector<Entity*> e);


public slots:
    void refresh(const QVector<QVector<Tile>> &miniMap, Coordinate pos);

    // gestisco il segnale proveniente dallo slider per selezionare la dimensione
    void onDimensionChanged(int dim);

    void onTileButtonPressd(QVector<Entity*> e);

private:

    // elimino tutti i widget nel layout
    void clearWidgets(QLayout * layout);


    QGridLayout *layout;
    QGridLayout *tile_layout;
    QGridLayout *slider_layout;

    QSlider *dimensionSlider;
    QLabel *dimensionLabel;

};
#endif // MAPWIDGET_H
