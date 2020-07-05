#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QGroupBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MusicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicWidget(QWidget *parent = nullptr);


public slots:
    void sliderChanged();
    void onMutePressed();
private:
    QSlider *volumeSlider;

    //widget move
    QPushButton *muteButton;
    QGroupBox *musicSlider;

    QMediaPlaylist *playlist;
    QMediaPlayer *music;

};

#endif // MUSICWIDGET_H
