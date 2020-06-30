#ifndef CHOICEBUTTON_H
#define CHOICEBUTTON_H

#include <game.h>
#include <QPushButton>

class ChoiceButton : public QPushButton
{
    Q_OBJECT

public:
    ChoiceButton(QWidget *parent = nullptr);

    void setChoice(Choice c) {
        choice = c;
        setText(c.getLabel());
    }

signals:
    void buttonClicked(Choice, ChoiceButton*);

private slots:
    void handleClick()
    {
        emit buttonClicked(choice, this);
    }

private:
    Choice choice;
};

#endif // CHOICEBUTTON_H
