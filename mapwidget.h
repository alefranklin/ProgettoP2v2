#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <vector>

#include <entity.h>
#include "map.h"
#include "tilebutton.h"


class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr, int val = 19);
    ~MapWidget() = default;

signals:
    // invio il segnale per cambiare grandezza della minimappa
    void setMiniMapSize(int dim);

    // invio il segnale per avere info sull'Entity presente nel Tile cliccato
    void showDetailsOf(std::vector<Entity*> e);


public slots:
    void refresh(const std::vector<std::vector<Tile>> &miniMap, Coordinate pos);

    // gestisco il segnale proveniente dallo slider per selezionare la dimensione
    //void onDimensionChanged(int dim);
    void onTileButtonPressed(std::vector<Entity *> e);

    void syncDimension();


private:
    int dimension;
    QVector<TileButton*> tiles;
    QGridLayout *layout;
};
#endif // MAPWIDGET_H
