#include "mainview.h"
#include "ui_mainview.h"
#include "movebutton.h"

#include <QObject>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>

MainView::MainView(Game *g, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainView)
    , model(g)
{
    ui->setupUi(this);

    // nascondo il pulsante
    ui->choiceButton->setHidden(true);

    //connetto il segnale del pulsante allo slot per gestirlo
    //ChoiceButton* cbt = ui->choiceButton;
    //connect(cbt, &ChoiceButton::buttonClicked, this, &MainView::choicePressed);

    //solo per il dialogo
    QPushButton* bt = ui->dialogo;
    connect(bt, &QPushButton::clicked, this, &MainView::onDialogPressed);


    // controllo il volume
    volumeSlider = ui->volumeSlider; // TODO sostitutire con (riga sotto)
    //volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainView::onVolumeChanged);

    // bottone per il muto
    muteButton = ui->muteButton;
    //muteButton = new QPushButton("mute");
    connect(muteButton, &QPushButton::clicked, this, &MainView::onMute);

    moveWidget = new MoveWidget(this);

    connect(moveWidget, &MoveWidget::emitDir, this, &MainView::movePressed);

    choiceWidget = new ChoiceWidget(this);
    choiceWidget->move(0,100);
    connect(choiceWidget, &ChoiceWidget::sendChoice, this, &MainView::choicePressed);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::printString(QString s)
{
    ui->textEdit->append(s);
}

void MainView::showChoice(QVector<Game::Choice> c)
{
    //mostriamo le scelte
    choiceWidget->setChoices(c);

    //ui->choiceButton->setEnabled(true);
   //ui->choiceButton->setHidden(false);
   // ui->choiceButton->setChoice(c);
}

void MainView::choicePressed(Game::Choice c)
{
    choiceWidget->cleanGrid();
    emit emitChoice(c);
}

void MainView::onDialogPressed()
{
    emit emitDialog();
}

void MainView::onVolumeChanged(int volume) {
    // se il volume è a zero mute è disabilitato
    if(volume == 0) muteButton->setDisabled(true);
    else muteButton->setDisabled(false);
    // emetto il segnale verso il controller
    emit volumeChanged(volume);
}

void MainView::onMute() {
    volumeSlider->setValue(0);
}

void MainView::movePressed(char dir){
    //codice per muovere
    ui->textEdit->append(QString(dir)); //placeholder per test
}
