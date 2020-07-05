#include "musicwidget.h"

#include <QHBoxLayout>

MusicWidget::MusicWidget(QWidget *parent) : QWidget(parent)
{
    musicSlider = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // controllo il volume
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);
    // bottone per il muto
    muteButton = new QPushButton("Mute", this);

    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    musicSlider->setLayout(layout);
    musicSlider->setFixedSize(200, 65);

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/track1"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(volumeSlider->value());
    music->play();
}

void MusicWidget::sliderChanged(){
    music->setVolume(volumeSlider->value());
    if(volumeSlider->value() == 0) muteButton->setDisabled(true);
    else muteButton->setEnabled(true);
}

void MusicWidget::onMutePressed(){
    muteButton->setDisabled(true);
    volumeSlider->setValue(0);
    music->setVolume(0);
}

