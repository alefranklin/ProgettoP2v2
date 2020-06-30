#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QGridLayout>

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget() = default;

signals:

public slots:
    void setMap(char **mappa, int w, int h);

private:
    QGridLayout *layout;

};
#endif // MAPWIDGET_H
