//include guards

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <chrono>
#include <QTimer>
#include <QPushButton>
#include <QVector>

#include <iostream>


namespace Ui {
class GameBoard;
}


/**
    @class GameBoard
    @brief Class that creates essentially the board where everything will be moving and where the user with interact with the Falcon and spaceships.
    @details
    Contains a bunch of private variables that keep track of positions, fill up the board with labels and widgets, sets the board size by
    n x n, and keeps track of remaining enemies to be destroyed.
    @code
        GameBoard g(this,7) //constructor ; "this" is the parent of the GameBoard, which should be the MainWindow object
    @endcode
*/
class GameBoard : public QWidget
{
    Q_OBJECT


public slots:
    void updateObjects();
    void updateAttacks();


signals:
    void game_over();
    void complete_level();


public:
    explicit GameBoard(QWidget *parent = 0, size_t board_size = 10);
    ~GameBoard();


    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);

    void unleash(int x, int y);
    void xwing_hit(QPoint* location);
    void tie_hit(QPoint* location);

    void updateFalcon(int px, int py, int nx, int ny);


private:

    Ui::GameBoard *ui;

    const QPixmap* falcon_image;
    QPixmap* xwing_image;
    QPixmap* tie_image;
    QPixmap* rays_image;
    QPixmap* attack_image;

    QPoint *falcon_position;
    QPoint *xwing_positions;
    QPoint *tie_positions;
    QVector <QPoint *> attack_positions;
    size_t number_xwings;
    size_t number_ties;

    //Top bar variables
    QWidget* Top;
    unsigned int rays_remaining;
    QLabel** rays;

    QWidget* Middle;
    unsigned int ties_remaining;
    QLabel** ties;

    //Board Variables
    QWidget *Board;
    size_t board_size;
    QLabel** labels;


};

#endif // GAMEBOARD_H

