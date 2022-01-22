#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QDialog>

namespace Ui {
class GameOverWindow;
}

class GameOverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverWindow(QWidget *parent = nullptr);
    ~GameOverWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GameOverWindow *ui;
};

#endif // GAMEOVERWINDOW_H
