#ifndef CHOICEBUTTON_H
#define CHOICEBUTTON_H

#include <game.h>
#include <QPushButton>

class ChoiceButton : public QPushButton
{
    Q_OBJECT

public:
    ChoiceButton(QWidget *parent = nullptr);

    void setChoice(Game::Choice c) {
        choice = c;
        setText(c.getLabel());
    }

signals:
    void buttonClicked(Game::Choice);

private slots:
    void handleClick();

private:
    Game::Choice choice;
};

#endif // CHOICEBUTTON_H
