#include "mainview.h"
#include "ui_mainview.h"

#include <QObject>
#include <QTextEdit>
#include <QPushButton>

MainView::MainView(Game *g, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainView)
    , model(g)
{
    ui->setupUi(this);

    // nascondo il pulsante
    ui->choiceButton->setHidden(true);

    //connetto il segnale del pulsante allo slot per gestirlo
    ChoiceButton* cbt = ui->choiceButton;
    connect(cbt, &ChoiceButton::buttonClicked, this, &MainView::choicePressed);

    //solo per il dialogo
    QPushButton* bt = ui->dialogo;
    connect(bt, &QPushButton::clicked, this, &MainView::onDialogPressed);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::printString(QString s)
{
    ui->textEdit->append(s);
}

void MainView::showChoice(Choice c)
{
    ui->choiceButton->setEnabled(true);
    ui->choiceButton->setHidden(false);
    ui->choiceButton->setChoice(c);
}

void MainView::choicePressed(Choice c, ChoiceButton *cbt)
{
    cbt->setEnabled(false);
    cbt->setHidden(true);
    emit emitChoice(c);
}

void MainView::onDialogPressed()
{
    emit emitDialog();
}

