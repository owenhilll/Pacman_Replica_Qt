#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"
#include <QProcess>

GameOverWindow::GameOverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);
}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}
//this is the restart button that the user may click, it will simply load a new window for the player to start a new game
void GameOverWindow::on_pushButton_clicked()
{
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

//this is the exit button, will quit the application when clicked
void GameOverWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

