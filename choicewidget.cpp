#include "choicewidget.h"

#include "choicebutton.h"
#include "game.h"

ChoiceWidget::ChoiceWidget(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    grid->setSpacing(15);
    setLayout(grid);

    for(int i = 0; i < 6; i++){
        buttons.append(new ChoiceButton());
        connect(buttons[i], &ChoiceButton::buttonClicked, this, &ChoiceWidget::choicePressed);
        buttons[i]->setFixedSize(70,30);
        buttons[i]->setEnabled(false);
        grid->addWidget(buttons[i],i/3,i%3);
    }

}

void ChoiceWidget::cleanGrid()
{
    for(int i = 0; i < 6; i++){
        buttons[i]->setText(QString(""));
        buttons[i]->setEnabled(false);
    }

}

void ChoiceWidget::setChoices(QVector<Game::Choice> choices){
    for(int i = 0; i < choices.size(); ++i){
        buttons[i]->setChoice(choices[i]);
        buttons[i]->setEnabled(true);
    }
}

void ChoiceWidget::choicePressed(Game::Choice c){
    emit sendChoice(c);
}



