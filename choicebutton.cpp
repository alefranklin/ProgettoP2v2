#include "choicebutton.h"

ChoiceButton::ChoiceButton(QWidget *parent): QPushButton(parent) {
    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void ChoiceButton::handleClick()
{
    emit buttonClicked(choice);
}
