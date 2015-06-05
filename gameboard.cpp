#include "gameboard.h"
#include "ui_gameboard.h"
#include "mainwindow.h"

//need this for random number generator
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);


/**
    @brief constructor with parameters that sets the board size and other properties
    @details
    creates the board with the appropriate number of X-Wings and TIE fighters as well
    @code
        GameBoard g(this,7);
    @endcode
    @param parent takes ownership of the GameBoard
    @param board_sz is the board size
*/
GameBoard::GameBoard(QWidget *parent, size_t board_sz) :
    QWidget(parent),
    ui(new Ui::GameBoard),
    board_size(board_sz)
{
    ui->setupUi(this);

    Top = new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");
    QHBoxLayout *top_bar = new QHBoxLayout(Top);

    QLabel* rays_text = new QLabel("Blasts: ");
    top_bar->addWidget(rays_text,0,Qt::AlignLeft);

    QString ray_fileName(":/Images/laser_ray.jpg");
    rays_image = new QPixmap(ray_fileName);

    rays_remaining = 2;
    rays = new QLabel*[rays_remaining];

    for(size_t i=0;i<rays_remaining;++i)
    {
            rays[i] = new QLabel;
            rays[i]->setPixmap(*rays_image);
            rays[i]->setMinimumSize(40,40);
            rays[i]->setMaximumSize(40,40);
            rays[i]->setScaledContents(true);
            top_bar->addWidget(rays[i],0,Qt::AlignLeft); //adds in the labels
    };

    QPushButton* button = new QPushButton("New Game");
    QObject::connect(button, SIGNAL(clicked()), parent, SLOT(new_game()));
    top_bar->addWidget(button);


    QString tie_filename(":/Images/tie_fighter.jpg");
    tie_image = new QPixmap(tie_filename);


    Middle = new QWidget;
    Middle->setStyleSheet("QLabel { background-color : black; color : white; border: black; }");
    QHBoxLayout *middle_bar = new QHBoxLayout(Middle);

    QLabel* tie_text = new QLabel("TIEs: ");
    middle_bar->addWidget(tie_text,0,Qt::AlignLeft);


    ties_remaining = ((int)board_size)-3;
    ties = new QLabel*[ties_remaining];

    for(size_t i=0;i<ties_remaining;++i)
    {
            ties[i] = new QLabel;
            ties[i]->setPixmap(*tie_image);
            ties[i]->setMinimumSize(40,40);
            ties[i]->setMaximumSize(40,40);
            ties[i]->setScaledContents(true);
            middle_bar->addWidget(ties[i],0,Qt::AlignLeft);
    };

    //This code creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    //Random number generator for C++11
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(0,board_size-1);

       // Create each label for the board,
       for(size_t i=0;i<board_size;++i)
       {
          for(size_t j=0;j<board_size;++j)
          {

                // Create label and set properties.
                labels[i*board_size+j] = new QLabel;
                labels[i*board_size+j]->setMinimumSize(50,50);
                labels[i*board_size+j]->setMaximumSize(50,50);
                labels[i*board_size+j]->setStyleSheet("QLabel { background-color : black; color : white; border : black; }");
                labels[i*board_size+j]->setFrameStyle(3);
                labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

                // Add label to the layout
                SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

            }
        }

        if(board_size == 7)
        {
            falcon_position = new QPoint(4,6);  //e.g. 4th column, 6th row
            Board->setFixedSize(400,400);
        }
        if(board_size == 9)
        {
            falcon_position = new QPoint(6,8);
            Board->setFixedSize(500,500);
        }
        if(board_size == 11)
        {
            falcon_position = new QPoint(8,10);
            Board->setFixedSize(600,600);
        }


        //Creating the falcon
        QString falcon_filename(":/Images/m_falcon.jpg");
        falcon_image = new QPixmap(falcon_filename);
        labels[(board_size * board_size)-3]->setPixmap(*falcon_image);
        labels[(board_size * board_size)-3]->setScaledContents(true);



        QVBoxLayout *piece_together = new QVBoxLayout;

        piece_together->addWidget(Top,0,Qt::AlignCenter);
        piece_together->addWidget(Middle,0,Qt::AlignCenter);
        piece_together->addWidget(Board,0,Qt::AlignCenter);
        this->setLayout(piece_together);
        this->setStyleSheet("QLabel { background-color : black; color : white; }");


        QString xwing_filename(":/Images/x_wing.bmp");
        xwing_image = new QPixmap(xwing_filename);


        //some of the X-Wings and TIE fighters are outside the board
        if(board_size == 7)
        {
            number_xwings = 4;
            xwing_positions = new QPoint[number_xwings];

            xwing_positions[0].setX(-1);
            xwing_positions[0].setY(distribution(generator)-1);

            xwing_positions[1].setX(board_size);
            xwing_positions[1].setY(distribution(generator)-1);

            xwing_positions[2].setY(-1);
            xwing_positions[2].setX(distribution(generator));

            xwing_positions[3].setY(3);
            xwing_positions[3].setX(distribution(generator));


            number_ties = 4;
            tie_positions = new QPoint[number_ties];

            tie_positions[0].setX(-1);
            tie_positions[0].setY(distribution(generator)-1);

            tie_positions[1].setX(board_size);
            tie_positions[1].setY(distribution(generator)-1);

            tie_positions[2].setY(-1);
            tie_positions[2].setX(distribution(generator));

            tie_positions[3].setY(4);
            tie_positions[3].setX(distribution(generator));
        }

        if(board_size == 9)
        {

            number_xwings = 6;
            xwing_positions = new QPoint[number_xwings];

            xwing_positions[0].setX(-1);
            xwing_positions[0].setY(distribution(generator)-1);

            xwing_positions[1].setX(board_size);
            xwing_positions[1].setY(distribution(generator)-1);

            xwing_positions[2].setY(-1);
            xwing_positions[2].setX(distribution(generator));

            xwing_positions[3].setY(4);
            xwing_positions[3].setX(distribution(generator));

            xwing_positions[4].setX(-1);
            xwing_positions[4].setY(distribution(generator)-1);

            xwing_positions[5].setX(board_size);
            xwing_positions[5].setY(distribution(generator)-1);


            number_ties = 6;
            tie_positions = new QPoint[number_ties];

            tie_positions[0].setX(-1);
            tie_positions[0].setY(distribution(generator)-1);

            tie_positions[1].setX(board_size);
            tie_positions[1].setY(distribution(generator)-1);

            tie_positions[2].setY(-1);
            tie_positions[2].setX(distribution(generator));

            tie_positions[3].setY(5);
            tie_positions[3].setX(distribution(generator));

            tie_positions[4].setX(-1);
            tie_positions[4].setY(distribution(generator)-1);

            tie_positions[5].setX(board_size);
            tie_positions[5].setY(distribution(generator)-1);

        }

        if(board_size == 11)
        {

            number_xwings = 8;
            xwing_positions = new QPoint[number_xwings];

            xwing_positions[0].setX(-1);
            xwing_positions[0].setY(distribution(generator)-1);

            xwing_positions[1].setX(board_size);
            xwing_positions[1].setY(distribution(generator)-1);

            xwing_positions[2].setY(-1);
            xwing_positions[2].setX(distribution(generator));

            xwing_positions[3].setY(4);
            xwing_positions[3].setX(distribution(generator));

            xwing_positions[4].setX(-1);
            xwing_positions[4].setY(distribution(generator)-1);

            xwing_positions[5].setX(board_size);
            xwing_positions[5].setY(distribution(generator)-1);

            xwing_positions[6].setY(-1);
            xwing_positions[6].setX(distribution(generator));

            xwing_positions[7].setY(6);
            xwing_positions[7].setX(distribution(generator));


            number_ties = 8;
            tie_positions = new QPoint[number_ties];

            tie_positions[0].setX(-1);
            tie_positions[0].setY(distribution(generator)-1);

            tie_positions[1].setX(board_size);
            tie_positions[1].setY(distribution(generator)-1);

            tie_positions[2].setY(-1);
            tie_positions[2].setX(distribution(generator));

            tie_positions[3].setY(5);
            tie_positions[3].setX(distribution(generator));

            tie_positions[4].setX(-1);
            tie_positions[4].setY(distribution(generator)-1);

            tie_positions[5].setX(board_size);
            tie_positions[5].setY(distribution(generator)-1);

            tie_positions[6].setY(-1);
            tie_positions[6].setX(distribution(generator));

            tie_positions[7].setY(7);
            tie_positions[7].setX(distribution(generator));

        }

        //Separate timers for the updates
        QTimer *timer = new QTimer(this);
        QTimer *timer2 = new QTimer(this);

        connect(timer2, SIGNAL(timeout()), this, SLOT(updateAttacks()));
        connect(timer, SIGNAL(timeout()), this, SLOT(updateObjects()));
        timer->start(125);
        timer2->start(50);  //shots are faster than the objects moving

        QString attack_filename(":/Images/attack_ray.jpg");
        attack_image = new QPixmap(attack_filename);


        //creating the signals and slots
        //will call the game_over/complete_level of mainwindow
        connect(this, SIGNAL(game_over()), parent, SLOT(game_over()));
        connect(this, SIGNAL(complete_level()), parent, SLOT(complete_level()));


        attack_positions.reserve(300);

}

/**
    @brief destructor for GameBoard
    @details
    calls delete on all the heap memory that we have not passed ownership too to widgets
*/
GameBoard::~GameBoard()
{
    delete [] xwing_positions;
    delete [] tie_positions;
    delete falcon_position;

    //ranged based for loop
    for(auto x: attack_positions)
    {
        delete x;
    }

    delete ui;
}

/**
    @brief this function gets called everytime we press either the up, left, right, or space keys
    @details
    moves the Falcon on the board, unleashes an ultra-ray blast, or shoots out a projectile
    @param event is essentially the instance of a key press
*/
void GameBoard::keyPressEvent(QKeyEvent *event)
{
    int x = falcon_position->rx();
    int y = falcon_position->ry();

    switch (event->key())
    {
    case Qt::Key_Left:
        if(falcon_position->rx() != 0)
            updateFalcon(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(falcon_position->rx() != ((int)board_size)-1)
            updateFalcon(x,y,x+1,y);

        break;

    case Qt::Key_Up:
        if(rays_remaining > 0)
        {
            rays[rays_remaining - 1]->clear();
            rays_remaining--;
            unleash(x,y);
        }

        break;

    case Qt::Key_Space:
        //everytime we press space bar, new memory is getting allocated
        attack_positions.push_back(new QPoint(x,y-1));


        break;

    default:
        QWidget::keyPressEvent(event);
    }

    return;
}


/**
    @brief paints on the objects on the gameboard based on their QPoint property
    @details
    this function is called repeatedly by our timer within the updateObject function
    @param e is not used in the function at all
*/
void GameBoard::paintEvent(QPaintEvent *e)
{
    for(size_t i=0;i<number_xwings;++i)
    {
        int px1 = xwing_positions[i].rx();
        int py1 = xwing_positions[i].ry();

        //if on the board
        if(px1 >= 0 && py1 >= 0 && px1 < (int)board_size && py1 < (int)board_size)
        {
            labels[py1*board_size+px1]->setPixmap(*xwing_image);
            labels[py1*board_size+px1]->setScaledContents(true);
        }
    }

    for(size_t i=0;i<number_ties;++i)
    {
        int px2 = tie_positions[i].rx();
        int py2 = tie_positions[i].ry();

        if(px2 >= 0 && py2 >= 0 && px2 < (int)board_size && py2 < (int)board_size)
        {
            labels[py2*board_size+px2]->setPixmap(*tie_image);
            labels[py2*board_size+px2]->setScaledContents(true);
        }
    }


    for(int i=0;i<attack_positions.size();++i)
    {
        int px3 = attack_positions[i]->rx();
        int py3 = attack_positions[i]->ry();

        //if on the board
        if(py3 >= 0 && py3 < (int)board_size)
        {
            labels[py3*board_size+px3]->setPixmap(*attack_image);
            labels[py3*board_size+px3]->setScaledContents(true);
        }
    }
}

/**
    @brief makes sure the objects on the gameboard are moving
    @details
    needed so our game runs smoothly
    @param e is the event
*/
void GameBoard::showEvent(QShowEvent *e) {

    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}


/**
    @brief this is the void function that occurs when we press the up key to use the ultra-ray blast
    @details
    we are essentially destroying every spaceship in the same column as the Falcon is in
    @code
        GameBoard g(this, 10);
        g.unleash(6,5) //7th row and 6th column
    @endcode
    @param x is the x location (the column -1) that we are destroying objects in
    @param y is the y location (the row -1) that we are destroying objects in (not used/necessary in the function definition)
*/
void GameBoard::unleash(int x, int y)
{
    for(int m=0, n=number_xwings; m<n; ++m)
    {
        if(xwing_positions[m].rx() == x && xwing_positions[m].ry() > -1 )
        {
            this->game_over();

            return;
        }
    }

    for(int m=0, n=number_ties; m<n; ++m)
    {
        if(tie_positions[m].rx() == x && tie_positions[m].ry() > -1  )
        {
                    labels[tie_positions[m].ry()*board_size+x]->clear();

                    //out of the board forever
                    tie_positions[m].setY(-10);
                    tie_positions[m].setX(-10);

                    //clears one of the ties_remaining labels
                    if(ties_remaining >= 1)
                    {
                        ties_remaining--;
                        ties[ties_remaining]->clear();
                    }

                    if(ties_remaining == 0)
                    {

                        this->complete_level();
                    }
        }
    }

}


/**
    @brief updates the Falcon location everytime we press the left or right key
    @details
    clears the old location the falcon was at and changed the location of the Falcon
    @code
        GameBoard g(this, 10);
        //moves the falcon to the left by one
        g.updateFalcon(7,6,6,6);
    @endcode
    @param px is the old x location
    @param py is the old y location
    @param nx is the new x location
    @param ny is the new y location
*/
void GameBoard::updateFalcon(int px, int py, int nx, int ny)
{
    labels[py*board_size+px]->clear();

    falcon_position->setX(nx);
    falcon_position->setY(ny);

    labels[ny*board_size+nx]->setPixmap(*falcon_image);
    labels[ny*board_size+nx]->setScaledContents(true);

}


/**
    @brief updates the locations of the objects (X-Wings and TIE fighters) in a random fashion
    @details
    uses different distributions to determine whether to go left,right,up,down and forces a repaint at the end of the function
    @code
        GameBoard g(this,10);
        g.updateObjects();
    @endcode
    @param px is the old x location
    @param py is the old y location
    @param nx is the new x location
    @param ny is the new y location
*/
void GameBoard::updateObjects()
{
    //different type of distributions for random movement
    std::uniform_real_distribution<double> p(0,1);
    std::uniform_int_distribution<int> x_or_y(0,1);
    std::uniform_int_distribution<int> increment(0,1);

    for(size_t i=0;i<number_xwings;++i)
    {

        int px1 = xwing_positions[i].rx();
        int py1 = xwing_positions[i].ry();


        if(px1>=0 && py1 >= 0 && px1<(int)board_size && py1<(int)board_size)  //if on the board
        {
            labels[py1*board_size+px1]->clear();  //then clear
        }

        int nx1 = px1;
        int ny1 = py1;

        if(px1 >= -1 && px1 <= (int)board_size && py1 >= -1 && py1 <= ((int)board_size)-2)
        {
            if(p(generator) < 0.18) //decides whether to even move or not
            {
                if(x_or_y(generator) == 0)  //move x-value
                {
                    int tempx1 = px1 + (2*increment(generator)-1);  //decides whether to move left or right
                    if(tempx1 >= -1 && tempx1 <= (int)board_size)
                    {
                        nx1 = tempx1;
                        xwing_positions[i].setX(nx1);
                    }
                }
                else  //move y-value
                {
                    int tempy1 = py1 + (2*increment(generator)-1);  //decides whether to move up or down
                    if(tempy1 >= -1 && tempy1 <= ((int)board_size)-2)
                    {
                        ny1 = tempy1;
                        xwing_positions[i].setY(ny1);
                    }
                }

            }
        }

        int px2 = tie_positions[i].rx();
        int py2 = tie_positions[i].ry();


        if(px2>=0 && py2 >= 0 && px2<(int)board_size && py2<(int)board_size)
        {
            labels[py2*board_size+px2]->clear();
        }

        int nx2 = px2;
        int ny2 = py2;

        if(px2 >= -1 && px2 <= (int)board_size && py2 >= -1 && py2 <= ((int)board_size)-2)
        {
            if(p(generator) < 0.25)  //moves faster than the X-Wings
            {
                if(x_or_y(generator) == 0)  //move x-value
                {
                    int tempx2 = px2 + (2*increment(generator)-1);
                    if(tempx2 >= -1 && tempx2 <= (int)board_size)
                    {
                        nx2 = tempx2;
                        tie_positions[i].setX(nx2);
                    }
                }
                else  //move y-value
                {
                    int tempy2 = py2 + (2*increment(generator)-1);
                    if(tempy2 >= -1 && tempy2 <= ((int)board_size)-2)
                    {
                        ny2 = tempy2;
                        tie_positions[i].setY(ny2);
                    }
                }

            }
        }
    }

    repaint();
    QCoreApplication::processEvents();
}


/**
    @brief checks if an X-Wing has been hit and if yes, calls game_over()
    @details
    traverses through the vector of xwing_positions to check if any of the x and y coordinates match up
    @code
        GameBoard g(this,10);
        QPoint* location = new QPoint(5,5);
        g.xwing_hit(location);
    @endcode
    @param location is the QPoint that the function will check if any of the X-Wings' positions match up
*/
void GameBoard::xwing_hit(QPoint* location)
{
    for(int m=0, n=number_xwings; m<n; ++m)
    {
        if(xwing_positions[m].rx() == location->rx() && xwing_positions[m].ry() == location->ry() && xwing_positions[m].ry() > -1 && ties_remaining != 0 )
        {
            this->game_over();

            return;
        }
    }
}


/**
    @brief checks if a TIE fighter has been hit and if yes, decrements ties_remaining and removes the TIE fighter from the gameboard
    @details
    traverses through the vector of tie_positions to check if any of the x and y coordinates match up; if no more TIEs, then level is completed
    @code
        GameBoard g(this,10);
        QPoint* location = new QPoint(5,5);
        g.tie_hit(location);
    @endcode
    @param location is the QPoint that the function will check if any of the TIE fighters' positions match up
*/
void GameBoard::tie_hit(QPoint* location)
{
    for(int m=0, n=number_ties; m<n; ++m)
    {
        if(tie_positions[m].rx() == location->rx() && tie_positions[m].ry() == location->ry() && tie_positions[m].ry() > -1  )
        {
                    location->setX(-10);  //out of the board forever
                    location->setY(-10);

                    tie_positions[m].setY(-10);
                    tie_positions[m].setX(-10);

                    if(ties_remaining >= 1)
                    {
                        ties_remaining--;
                        ties[ties_remaining]->clear();
                    }

                    if(ties_remaining == 0)
                    {
                        this->complete_level();
                    }
        }
    }
}


/**
    @brief updates the locations of the vector of attack QPoints by moving each one up 1; called repeately by our timer
    @details
    checks if any of attacks match up with any objects through the tie_hit and xwing_hit functions;\n
    once out of the board, the attack is set to somewhere way outside and cannot appear back on the board
    @code
        GameBoard g(this,10);
        g.updateAttacks();
    @endcode
*/
void GameBoard::updateAttacks()
{
    for(int i=0;i<attack_positions.size();++i)
    {

        int px3 = attack_positions[i]->rx();
        int py3 = attack_positions[i]->ry();

        int nx3 = px3;
        int ny3 = py3;

        if(px3>=0 && py3 >= 0 && px3<(int)board_size && py3<(int)board_size)  //if on the board
        {
            labels[py3*board_size+px3]->clear();
            tie_hit(attack_positions[i]);
            xwing_hit(attack_positions[i]);
        }

        if(attack_positions[i]->ry() >= 0)  //moves the attack up
        {
            ny3 = py3 -1;
            attack_positions[i]->setX(nx3);
            attack_positions[i]->setY(ny3);
        }
        else  //if out of the board, gone forever
        {
            attack_positions[i]->setX(-10);
            attack_positions[i]->setY(-10);
        }
    }

    return;
}
