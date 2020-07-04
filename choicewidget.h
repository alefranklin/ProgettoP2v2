#ifndef CHOICEWIDGET_H
#define CHOICEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <choicebutton.h>
#include "game.h"

class ChoiceWidget : public QWidget
{
    Q_OBJECT
public:
    ChoiceWidget(QWidget *parent = nullptr);

    void cleanGrid();

    void setChoices(QVector<Game::Choice> choices);

signals:
    void sendChoice(Game::Choice c);

public slots:
    void choicePressed(Game::Choice c);

private:
    QGridLayout *grid;
    QVector<ChoiceButton*> buttons;
};

#endif // CHOICEWIDGET_H
