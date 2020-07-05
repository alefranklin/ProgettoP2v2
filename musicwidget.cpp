#include "musicwidget.h"

#include <QHBoxLayout>

MusicWidget::MusicWidget(QWidget *parent) : QWidget(parent)
{

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


    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/track1"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(volumeSlider->value());
    music->play();

    connect(volumeSlider, &QSlider::valueChanged, this, &MusicWidget::sliderChanged);
    connect(muteButton, &QPushButton::clicked, this, &MusicWidget::onMutePressed);

    setLayout(layout);
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

