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

private slots:
    void onChoicePressed(Game::Choice c);

private:

    void clearWidgets(QLayout *layout);

    QGridLayout *grid;
    QVector<ChoiceButton*> buttons;
};

#endif // CHOICEWIDGET_H
