//include guards

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMediaPlayer> //for the music that starts playing when game is running
#include <QMainWindow>
#include "gameboard.h"

namespace Ui {
class MainWindow;
}


/**
    @class MainWindow
    @brief Class that creates the MainWindow or essentially the startup screen of the game as well as additional windows
    @details
    Each MainWindow object has a private variable Gameboard associated with it.
    There are public slots to indicate the game level as well as instructions, game story, game over, and level completion.
    @code
        MainWindow w; //default constructor
    @endcode
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void easy_game_begin();
    void medium_game_begin();
    void hard_game_begin();

    void instructions();
    void story();

    void new_game();
    void game_over();
    void complete_level();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameBoard* board;

};

#endif // MAINWINDOW_H
