#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <Qcolor>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QMainWindow>




QT_BEGIN_NAMESPACE
namespace Ui { class GameBoard; }
QT_END_NAMESPACE

class GameBoard : public QMainWindow
{
    Q_OBJECT

public:
    //constructor and destructor
    GameBoard(QWidget *parent = nullptr);
    ~GameBoard();
    //used to print out the board initially
    void display();
    //moves the player piece to the new location
    void updateGame();
    //makes sure the place the player wishes to move is not a tree
    bool checkiftree(int x, int y);
    //displays the endgame dialoque then closes the application
    void endgame();
    //assures the player will not move onto an enemy
    bool checkifEnemy(int x, int y);
    //If player collects all treasure without dying, successfull game Dialogue is called
    void success();



private slots:
    //will be used to start the movement of the game
   void on_pushButton_clicked();

    //randomly moves enemy pieces one space
    void moveEnemys();



protected:
    //used to gett the players movement
    void keyPressEvent(QKeyEvent * k) override;
signals:
   void keyPressed();


private:
    Ui::GameBoard *ui;
    //sets up the board comprised of gamepiece objects;
    QGraphicsTextItem * board_[20][20];

    //Sets up the scene to add to
    QGraphicsScene * scene;

    int enemycount = 0;
    //used to update locations of enemies throughout map
    QTimer* timer;

    //User location on board
    int x_; int y_;

    int treecount = 0;
    //tracks location of all enemies on map
    int enemyPos[9][2];
    //tracks all trees on the map
    int treepos[49][2];
    //these are used to set the players previous spot to a blank space
    int prevx_; int prevy_;

};
#endif // GAMEBOARD_H
