#include "gameboard.h"
#include "ui_gameboard.h"
#include "gameoverwindow.h"
#include "alltreasurecollected.h"
#include <QtWidgets>
#include <QEvent>
#include <QTimer>

//player score
int treasure = 0;
//count of all treasures on the map
int total_treasure = 0;
//test

//This will be used to populate the screen with game pieces

GameBoard::GameBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameBoard)
{
    ui->setupUi(this);

    QGraphicsView * view = ui->graphicsView;

    scene = new QGraphicsScene;

    view->setScene(scene);
    //gray is more aestically pleasing in my opinion
    scene->setBackgroundBrush(Qt::gray);




    //these are coordinates to the players current location. At game start, the player will spawn top left
    x_ = 0;
    y_ = 0;

    //loops through the game board to populate with game pieces
    for(int x = 0; x < 20; x++){
        for(int y = 0; y < 20; y++){
            int random = rand() % 30;
            //randomly generates locations on the board that will house either enemies, trees, or treasure
            if(random == 0 && enemycount < 10){
                board_[x][y] = new QGraphicsTextItem{QStringLiteral("😈")};
                enemyPos[enemycount][0] = x;
                enemyPos[enemycount][1] = y;
                enemycount ++;
                //I chose to make the game not exceed ten enemies
            } else if(random < 5 && treecount < 50){
                board_[x][y] = new QGraphicsTextItem{QStringLiteral("🌲")};
                treepos[treecount][0] = x;
                treepos[treecount][1] = y;
                treecount ++;
                //game will not exceed 50 trees
            } else {
                board_[x][y] = new QGraphicsTextItem{QStringLiteral("🌞")};
                total_treasure++;

            }
        }
    }
    //always set player location and graphic to top left at game start!
    board_[0][0] = new QGraphicsTextItem{QStringLiteral("👾")};
}

void GameBoard::updateGame(){
    //sets the previous player location to a blank if and only if the player moved onto a treasure two turns ago
    board_[prevx_][prevy_]->setHtml(" ");
    //increments the player score
    treasure++;
    //updates the board to match the player location
    board_[x_][y_]->setHtml("👾");

    std::string score = "Score: " + std::to_string(treasure);
    ui->label1_2->setText(QString(score.c_str()));
    //pastes the player score after each turn
    scene->update();
    update();
}



GameBoard::~GameBoard()
{
    delete ui;
}
//loops through the array and displays the string emojis associated with each gamepiece
void GameBoard::display(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            //sets the position and scale of each board item to best fit the UI
            board_[i][j]->setPos(40*i,27*j);
            board_[i][j]->setScale(1.5);
            scene->addItem(board_[i][j]);
        }
    }
}
//used to get the player movement. W,A,S and D keys are how the player moves around the board
void GameBoard::keyPressEvent(QKeyEvent * k){

    //if the player collected all the treasure on the board, then the game will end
    if(treasure == total_treasure){
        success();

    }
    //the variables will update the board after the player moves. Essentially trakcs the players last coordinates
    prevx_ = x_;
    prevy_ = y_;
    //If player presses the S key, they wish to move down
    if(k->key() == Qt::Key_S && y_ < 19){
        //If the player moves onto an enemy, end the game and quit the application
        if(checkifEnemy(x_,y_+1) == false){
            //Engame opens a new dialoque UI which gives the player an option to restart or exit the program
            endgame();

            QApplication::quit();
        //if the player attempts to move into a tree, display in the UI the player cannot move
        // up,down, left or right depending on the key input
        }else if(checkiftree(x_, y_+1) == false){

            ui->label1->setText("Cant Move Down!");
        }
        //if the player wishes to move onto a treasure, update their location
        else {
            y_+=1;
        }
    }
    //Same functionality as above, except the player coordinates are incremented/decremented
    //according to the key they pressed
    else if(k->key() == Qt::Key_W && y_ > 0){

        if(checkifEnemy(x_,y_-1) == false){
                    endgame();
                    QApplication::quit();
        }else if(checkiftree(x_, y_-1) == false){
            ui->label1->setText("Cant Move Up!");
        } else {
            y_-=1;
        }
    }
    else if(k->key() == Qt::Key_D && x_ < 19){
        if(checkifEnemy(x_+1,y_) == false){
                    endgame();
                    QApplication::quit();
        }else if(checkiftree(x_+1, y_) == false){
            ui->label1->setText("Cant Move Up!");
        } else {
            x_+=1;
        }
    }
    else if(k->key() == Qt::Key_A && x_ > 0){
        if(checkifEnemy(x_-1,y_) == false){
                    endgame();
                    QApplication::quit();
        }else if(checkiftree(x_-1, y_) == false){
            ui->label1->setText("Cant Move Up!");
        } else {
            x_-=1;
        }
    }
    //once the if/else cases are through, the game will update accordingly, and the scene willl also update
    updateGame();
    scene->update();


}


void GameBoard::moveEnemys(){
    //looping through enemy position array
    for(int x = 0; x < 9; x++){
        //first rand is for either up/down or left right
        int random = rand() % 2;
        //second random is for either left or right, or up or down depending on first random variable
        int random2 = rand() % 2;
        //randomly move to left/right or up/down
        if(random == 0){
            //makes sure the enenmy movement does not cause segementation fault
            if(random2 == 0 && enemyPos[x][0] > 0){
                if(!checkiftree(enemyPos[x][0],enemyPos[x][1])){
                    //if previous tile was tree, the update back to a tree. Remember enemys can move through walls
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌲");
                } else {
                    //if not tree, then set to treasure
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌞");
                }
                //updates that enemy location
                enemyPos[x][0]--;
                //updates the board to match enemy location
                board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("😈");
                //if the enemy moves onto the player, end the game
                if(enemyPos[x][0] == x_ && enemyPos[x][1] == y_){
                    endgame();
                }
 //the functionality is the same below as it is above, which is why i excluded redudant commenting

            } else if(enemyPos[x][0] < 19){
                if(!checkiftree(enemyPos[x][0],enemyPos[x][1])){
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌲");
                } else {
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌞");
                }
                enemyPos[x][0]++;
                board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("😈");
                if(enemyPos[x][0] == x_ && enemyPos[x][1] == y_){
                    endgame();
                }
            }
        }
        else{
            if(random2==0 && enemyPos[x][1] > 0){
                if(!checkiftree(enemyPos[x][0],enemyPos[x][1])){
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌲");
                } else {
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌞");
                }
                enemyPos[x][1]--;
                board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("😈");
                if(enemyPos[x][0] == x_ && enemyPos[x][1] == y_){
                    endgame();
                }
            } else if(enemyPos[x][1] < 19){
                if(!checkiftree(enemyPos[x][0],enemyPos[x][1])){
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌲");
                } else {
                    board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("🌞");
                }
                enemyPos[x][1]++;
                board_[enemyPos[x][0]][enemyPos[x][1]]->setHtml("😈");
                if(enemyPos[x][0] == x_ && enemyPos[x][1] == y_){
                    endgame();
                }
            }

        }
    }
}


//Creates the endgame UI wwhich gives the player two options
//Restart or exit.
void GameBoard::endgame(){
    GameOverWindow endGame;
    endGame.setModal(true);
    endGame.exec();
}
//displays the UI that awards the player on their successful completion of  the game
void GameBoard::success(){
    alltreasurecollected endgame;
    endgame.setModal(true);
    endgame.exec();
}
//calls the moveenemy function every second to randomly move the enemys one spot
//enemys can move through walls
void GameBoard::on_pushButton_clicked()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveEnemys()));
    timer->start(1000);
}

//loops through the tree position array and returns false if their is a tree present on the coordinates
//If false, that means the player cannot move there
bool GameBoard::checkiftree(int x, int y){
   for(int i = 0; i < 49;i++){
       if(treepos[i][0] == x && treepos[i][1] == y){
           return false;
       }
   }
   return true;
}
//loops through the enemy position array, and returns false if an enemy is present
//If this is false in the overrided key press event function, the game will end
bool GameBoard::checkifEnemy(int x, int y){
    for(int i = 0; i < 9;i++){
        if(enemyPos[i][0] == x && enemyPos[i][1] == y){
            qDebug() << "Test";
            return false;
        }
    }
    return true;
}




