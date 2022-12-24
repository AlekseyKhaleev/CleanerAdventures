
#include "GameOverView.h"

#include <QMessageBox>


GameOverView::GameOverView(QMessageBox *parent): QMessageBox(parent)
{

    this->setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
    this->setDefaultButton(QMessageBox::Retry);

}

GameOverView::~GameOverView()=default;

void GameOverView::levelLost() {
    this->setText("<p align='center'>Ohh no! You lose! </p>");
    this->setInformativeText("<p align='center'>Wanna try again?</p>");
    int result = this->exec();
    if(result == QMessageBox::Retry){
        emit gameStarted();
    }
    else{
        emit gameEnded();
    }
}

void GameOverView::levelDone() {
    this->setText("<p align='center'>Level done, great! </p>");
    this->setInformativeText("<p align='center'>Wanna go next?</p>");
    int result = this->exec();
    if(result == QMessageBox::Retry){
        emit gameStarted();
    }
    else{
        emit gameEnded();
    }
}



