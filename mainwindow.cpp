#include "mainwindow.h"
#include "gameboard.h"
#include "ui_mainwindow.h"


/**
    @brief constructor that takes in a QWidget param
    @code
        MainWindow w;
    @endcode
    @param parent is set as the parent/"owner" of the MainWindow
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Sounds/Imperial March.mp3"));
    music->play();

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    this->setFixedSize(1075,500);

    ui->setupUi(this);  //displays the UI

}


/**
    @brief sets the game to the easiest level
    @details
    the board is 7x7
    @code
        MainWindow w;
        w.easy_game_begin();
    @endcode
*/
void MainWindow::easy_game_begin()
{
    board = new GameBoard(this,7);
    this->setCentralWidget(board);

    this->setFixedSize(515,555);
}


/**
    @brief sets the game to the medium level
    @details
    the board is 9x9
    @code
        MainWindow w;
        w.medium_game_begin();
    @endcode
*/
void MainWindow::medium_game_begin()
{
    board = new GameBoard(this,9);
    this->setCentralWidget(board);

    this->setFixedSize(600,665);
}

/**
    @brief sets the game to the hardest level
    @details
    the board is 11x11
    @code
        MainWindow w;
        w.hard_game_begin();
    @endcode
*/
void MainWindow::hard_game_begin()
{
    board = new GameBoard(this,11);
    this->setCentralWidget(board);

    this->setFixedSize(675,745);
}


/**
    @brief displays a separate window with instructions for the game
    @details
    accessed by clicking on a pushbutton on the startup screen
    @code
        MainWindow w;
        w.instructions();
    @endcode
*/
void MainWindow::instructions()
{
    QWidget* Top = new QWidget;
    Top->setWindowTitle("Instructions");

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    Top->setAutoFillBackground(true);
    Top->setPalette(Pal);

    QVBoxLayout *vert = new QVBoxLayout(Top);

    QLabel* gameplay = new QLabel("Press the left or right arrow keys to move the Millennium Falcon.\n"
                                  "The goal is to shoot (by pressing the space bar) and destroy all\n"
                                  "the TIE fighters and avoid shooting the X-Wings.\n"
                                  "If an X-Wing were to be hit, you will automatically lose the level.\n\n"
                                  "Both TIE fighters and X-Wings will be moving randomly on the board\n"
                                  "at a certain speed.\n"
                                  "VERY IMPORTANT: TIE FIGHTERS AND X-WINGS CAN MOVE OUT OF THE BOARD\n"
                                  "AND COME BACK ON.\n\n"
                                  "Additionally, for every level, you will be given two ultra-ray blasts.\n"
                                  "They can be used by pressing the up key.\n"
                                  "The blast will destroy everything in its column. This means\n"
                                  "potentially one or more objects can be shot down.\n"
                                  "\n"
                                  "There are three levels of difficulty for this game.\n"
                                  "The higher the level, the more X-Wings and TIE fighters\n"
                                  "there will be and the slower your attacks will be.\n"
                                  "\n"
                                  "WARNING: THERE MIGHT BE A CHANCE THAT AN X-WING IS HIDING UNDER A TIE\n"
                                  "FIGHTER!!!\n"
                                  "PRO-TIP: ATTACK TIE FIGHTERS WHEN X-WINGS ARE NOT AROUND.\n"
                                  "PRO-TIP: ATTACK TIE FIGHTERS WHEN THEY'RE IN CLOSE RANGE.\n"
                                  "\n"
                                  "May the force be with you!");
    gameplay->setStyleSheet("QLabel {color : white; }");
    gameplay->setAlignment(Qt::AlignCenter);

    vert->addWidget(gameplay,Qt::AlignCenter);


    QString yoda_filename(":/Images/Yoda.jpg");
    QPixmap* yoda_image = new QPixmap(yoda_filename);

    QLabel* yoda = new QLabel;

    yoda->setPixmap(*yoda_image);
    vert->addWidget(yoda,0,Qt::AlignCenter);

    Top->setFixedSize(600,800);
    Top->show();
}


/**
    @brief displays a separate window with story for the game
    @details
    accessed by clicking on a pushbutton on the startup screen
    @code
        MainWindow w;
        w.story();
    @endcode
*/
void MainWindow::story()
{
    QWidget* Top = new QWidget;
    Top->setWindowTitle("Story");

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    Top->setAutoFillBackground(true);
    Top->setPalette(Pal);

    QVBoxLayout *vert = new QVBoxLayout(Top);

    QLabel* intro = new QLabel("\nA long time ago in a galaxy far, far away...\n\n\n");
    intro->setStyleSheet("QLabel {color : teal; }");
    intro->setAlignment(Qt::AlignLeft);

    vert->addWidget(intro,Qt::AlignCenter);


    QLabel* details = new QLabel("It is a period of great urgency. The Rebels have landed devasting attacks on the Empire. After the\n"
                                 "destruction of the Death Star, the Empire has ordered immediate construction of a second Death Star\n"
                                 "in order to obliterate planets with Rebel strongholds.\n\n"
                                 "On a daring mission, Chewbecca and his friends have infiltrated an imperial base and stolen the plans\n"
                                 "for the second Death Star. However, they did not leave unnoticed.\n\n"
                                 "With TIE fighters on hot pursuit, the Millennium Falcon and the Rebel X-Wings attempt to escape from\n"
                                 "and destroy the enemy starships. They must hurry. Imperial Star Destroyers have been called and Lord\n"
                                 "Vader is not happy...\n\n"
                                 );
    details->setStyleSheet("QLabel {color : yellow; }");
    details->setAlignment(Qt::AlignLeft);

    vert->addWidget(details,Qt::AlignCenter);


    QString crew_filename(":/Images/aboard_falcon.jpg");
    QPixmap* crew_image = new QPixmap(crew_filename);

    QLabel* crew = new QLabel;

    crew->setPixmap(*crew_image);
    vert->addWidget(crew,0,Qt::AlignCenter);

    Top->setFixedSize(615,660);
    Top->show();
}


/**
    @brief displays a separate window saying you completed the level
    @details
    this function will be called when all the TIE fighters are destroyed
    @code
        MainWindow w;
        w.complete_level();
    @endcode
*/
void MainWindow::complete_level()
{
    QWidget* Top = new QWidget;
    Top->setWindowTitle("LEVEL COMPLETED");

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    Top->setAutoFillBackground(true);
    Top->setPalette(Pal);

    QVBoxLayout *vert = new QVBoxLayout(Top);

    QLabel* message = new QLabel("\nYou have escaped from Vader and the imperial forces. The force is strong in you.\n\n"
                                 "Exit this window and click 'New Game' to play again."
                                 );
    message->setStyleSheet("QLabel {color : green; }");
    message->setAlignment(Qt::AlignCenter);

    vert->addWidget(message,Qt::AlignCenter);


    QString no_filename(":/Images/nooooooooo.jpg");
    QPixmap* no_image = new QPixmap(no_filename);

    QLabel* no = new QLabel;

    no->setPixmap(*no_image);
    vert->addWidget(no,0,Qt::AlignCenter);

    Top->setFixedSize(750,475);
    Top->show();
}


/**
    @brief sets the game back to the start-up screen
    @details
    this will get called when we press the 'New Game' button
    @code
        MainWindow w;
        w.new_game();
    @endcode
*/
void MainWindow::new_game() {

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    // Line above will delete the widget gracefully (no memory errors)

    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);
}


/**
    @brief displays a separate window saying game over/you did not pass the level
    @details
    this function will be called when an X-Wing is hit
    @code
        MainWindow w;
        w.game_over();
    @endcode
*/
void MainWindow::game_over() {

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    // Line above will delete the widget gracefully (no memory errors)


    QWidget* Top = new QWidget;
    Top->setWindowTitle("GAME OVER");

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    Top->setAutoFillBackground(true);
    Top->setPalette(Pal);

    QVBoxLayout *vert = new QVBoxLayout(Top);

    QLabel* message = new QLabel("\nYou have destroyed an ally X-Wing. Vader and his fleet has captured the Millennium Falcon.\n\n"
                                 "Exit this window and try again if you wish."
                                 );
    message->setStyleSheet("QLabel {color : red; }");
    message->setAlignment(Qt::AlignCenter);

    vert->addWidget(message,Qt::AlignCenter);


    QString captured_name(":/Images/captured.jpg");
    QPixmap* cap_image = new QPixmap(captured_name);

    QLabel* captured = new QLabel;

    captured->setPixmap(*cap_image);
    vert->addWidget(captured,0,Qt::AlignCenter);

    Top->setFixedSize(750,475);
    Top->show();

    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);
}


/**
    @brief destructor for the MainWindow class
    @details
    deletes all the widgets that we created on the UI
*/
MainWindow::~MainWindow()
{
    delete ui;
}


