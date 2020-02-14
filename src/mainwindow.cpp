#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    /* Game objects initialization (Graphic Scene, Graphic View, Timers, etc) */

    time = 0;
    soundOn = true;

    setMouseTracking(true);

    gameStarted = false;

    qsrand(QTime::currentTime().msec());

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(this);

    levels = new QGraphicsTextItem();
    lives = new QGraphicsTextItem();
    timeText = new QGraphicsTextItem();
    rtcTitle = new QLabel(this);

    level = new Level("Data/Levels/level_1.dat");
    score = new Score();

    timer = new QTimer(this);
    playing_time = new QTimer(this);

    /* Creating menu */

    menuButtons = new QVBoxLayout();

    startGame = new MenuLabel(this);
    options = new MenuLabel(this);
    credits = new MenuLabel(this);
    hallOfFame = new MenuLabel(this);
    exitGame = new MenuLabel(this);
    menuCastle = new QLabel(this);

    startGame->setText("<h3>Start Game</h3>");
    options->setText("<h3>Options</h3>");
    credits->setText("<h3>Credits</h3>");
    hallOfFame->setText("<h3>Hall of Fame</h3>");
    exitGame->setText("<h3>Exit</h3>");
    rtcTitle->setText("<h1>RETURN TO CASTLE</h1>");
    menuCastle->setPixmap(QPixmap("Data/Misc/castle.png"));

    startGame->setStyleSheet("color: white");
    options->setStyleSheet("color: white");
    credits->setStyleSheet("color: white");
    hallOfFame->setStyleSheet("color: white");
    exitGame->setStyleSheet("color: white");
    rtcTitle->setStyleSheet("color: blue");

    startGame->setFont(QFont("Verdana"));
    startGame->setFont(QFont("Verdana"));
    options->setFont(QFont("Verdana"));
    credits->setFont(QFont("Verdana"));
    hallOfFame->setFont(QFont("Verdana"));
    exitGame->setFont(QFont("Verdana"));
    rtcTitle->setFont(QFont("System"));

    menuButtons->addWidget(rtcTitle);
    menuButtons->addSpacing(15);
    menuButtons->addWidget(menuCastle);
    menuButtons->addSpacing(15);
    menuButtons->addWidget(startGame);
    menuButtons->addWidget(options);
    menuButtons->addWidget(credits);
    menuButtons->addWidget(hallOfFame);
    menuButtons->addWidget(exitGame);
    menuButtons->setAlignment(Qt::AlignCenter);
    menuButtons->addStretch(1);

    QWidget *widget = new QWidget(this);
    widget->setLayout(menuButtons);
    this->setCentralWidget(widget);

    this->setStyleSheet("background-color: black");

    connect(startGame, SIGNAL(pressed()), this, SLOT(StartGame()));
    connect(options, SIGNAL(pressed()), this, SLOT(GameOptions()));
    connect(credits, SIGNAL(pressed()), this, SLOT(GameCredits()));
    connect(hallOfFame, SIGNAL(pressed()), this, SLOT(GameHallOfFame()));
    connect(exitGame, SIGNAL(pressed()), this, SLOT(ExitGame()));

}

void MainWindow::keyPressEvent(QKeyEvent *e){

    if(!gameStarted){
        return;
    }

    if(e->key() == Qt::Key_W) {
        if(level->check_if_move_able(NORTH)){
            level->movePlayer(NORTH);
            player->move(NORTH);
        }

        if(level->check_if_next_level()){
            level->nextLevel();

            if(level->level > MAX_LEVEL){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                TextGameFinish();
                monsters.clear();

                return;
            }

            level->implantLifePack();
            player->setPos(level->playerPos.ry() * 30, level->playerPos.rx() * 30);
            player->setDefaultPos(level->playerPos.rx(), level->playerPos.ry());

            clearLevel();
            drawLevel(*level);
            drawText();
            initializeMobs();
        }

        if(this->check_if_dead()){
            player->die();
            level->resetPlayer();
            resetMobsPos();
            drawText();


            if(player->rLives() == 0){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                if(soundOn == true){
                QSound::play("Data/Sounds/game_over.wav");
                }

                TextGameOver();
                monsters.clear();
                saveHighScore();
            }
        }

        if(level->check_if_life_pack()){
            switch(level->lifeType){
            case 0: scene->removeItem(lifeItem);
                player->pickLife();
                level->removeLifePack();
                break;
            case 1: scene->removeItem(lifeItem);
                player->pickExtraLife();
                level->removeLifePack();
                break;
            }

            drawText();
        }

        if(level->check_if_portal()){
            player->goToRandomPos(level);
        }

        else {
            return;
        }

    }

    else if(e->key() == Qt::Key_S) {
        if(level->check_if_move_able(SOUTH)){
            level->movePlayer(SOUTH);
            player->move(SOUTH);
        }

        if(level->check_if_next_level()){
            level->nextLevel();

            if(level->level > MAX_LEVEL){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                TextGameFinish();
                monsters.clear();
            }

            level->implantLifePack();
            player->setPos(level->playerPos.ry() * 30, level->playerPos.rx() * 30);
            player->setDefaultPos(level->playerPos.rx(), level->playerPos.ry());

            clearLevel();
            drawLevel(*level);
            drawText();
            initializeMobs();
        }

        if(this->check_if_dead()){
            player->die();
            level->resetPlayer();
            resetMobsPos();
            drawText();


            if(player->rLives() == 0){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                if(soundOn == true){
                QSound::play("Data/Sounds/game_over.wav");
                }

                TextGameOver();
                monsters.clear();
                saveHighScore();
            }
        }

        if(level->check_if_life_pack()){
            switch(level->lifeType){
            case 0: scene->removeItem(lifeItem);
                player->pickLife();
                level->removeLifePack();
                break;
            case 1: scene->removeItem(lifeItem);
                player->pickExtraLife();
                level->removeLifePack();
                break;
            }

            drawText();
        }

        if(level->check_if_portal()){
            player->goToRandomPos(level);
        }

        else {
            return;
        }

    }

    else if(e->key() == Qt::Key_A) {
        if(level->check_if_move_able(WEST)){
            level->movePlayer(WEST);
            player->move(WEST);
            player->changeSideLeft();
        }

        if(level->check_if_next_level()){
            level->nextLevel();

            if(level->level > MAX_LEVEL){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                TextGameFinish();
                monsters.clear();
            }

            level->implantLifePack();
            player->setPos(level->playerPos.ry() * 30, level->playerPos.rx() * 30);
            player->setDefaultPos(level->playerPos.rx(), level->playerPos.ry());


            clearLevel();
            drawLevel(*level);
            drawText();
            initializeMobs();
        }

        if(this->check_if_dead()){
            player->die();
            level->resetPlayer();
            resetMobsPos();
            drawText();

            if(player->rLives() == 0){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);        
                scene->removeItem(timeText);
                scene->clear();

                if(soundOn == true){
                QSound::play("Data/Sounds/game_over.wav");
                }

                monsters.clear();
                TextGameOver();
                saveHighScore();
            }
        }

        if(level->check_if_life_pack()){
            switch(level->lifeType){
            case 0: scene->removeItem(lifeItem);
                player->pickLife();
                level->removeLifePack();
                break;
            case 1: scene->removeItem(lifeItem);
                player->pickExtraLife();
                level->removeLifePack();
                break;
            }

            drawText();
        }

        if(level->check_if_portal()){
            player->goToRandomPos(level);
        }

        else {
            return;
        }
    }

    else if(e->key() == Qt::Key_D) {
        if(level->check_if_move_able(EAST)){
            level->movePlayer(EAST);
            player->move(EAST);
            player->changeSideRight();
        }

        if(level->check_if_next_level()){
            level->nextLevel();

            if(level->level > MAX_LEVEL){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                TextGameFinish();
                monsters.clear();

                return;
            }

            level->implantLifePack();
            player->setPos(level->playerPos.ry() * 30, level->playerPos.rx() * 30);
            player->setDefaultPos(level->playerPos.rx(), level->playerPos.ry());

            clearLevel();
            drawLevel(*level);
            drawText();
            initializeMobs();
        }

        if(this->check_if_dead()){
            player->die();
            level->resetPlayer();
            resetMobsPos();
            drawText();


            if(player->rLives() == 0){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                if(soundOn == true){
                QSound::play("Data/Sounds/game_over.wav");
                }

                monsters.clear();
                TextGameOver();
                saveHighScore();
            }
        }

        if(level->check_if_life_pack()){
            switch(level->lifeType){
            case 0: scene->removeItem(lifeItem);
                player->pickLife();
                level->removeLifePack();
                break;
            case 1: scene->removeItem(lifeItem);
                player->pickExtraLife();
                level->removeLifePack();
                break;
            }

            drawText();
        }

        if(level->check_if_portal()){
            player->goToRandomPos(level);
        }

        else {
            return;
        }
    } //meatspin.com  meatspin.com  meatspin.com

}

void MainWindow::drawLevel(Level level){

    for(int a = 0; a < 15; a++){
        for(int b = 0; b < 15; b++){

            if(level.map[a][b] == 1){
                int wallPos = b * 30;
                int wallPos2 = a * 30;
                QPixmap *wall = new QPixmap("Data/Sprites/wall.bmp");
                QGraphicsPixmapItem *wallItem = scene->addPixmap(*wall);
                wallItem->setPos(wallPos, wallPos2);
             }

            else if(level.map[a][b] == 3){
                int gatePos = b * 30;
                int gatePos2 = a * 30;
                QPixmap *gate = new QPixmap();
                if(this->level->level == MAX_LEVEL)
                {
                    gate->load("Data/Sprites/castle.bmp");
                }

                else
                {
                    gate->load("Data/Sprites/gate.bmp");
                }
                QGraphicsPixmapItem *gateItem = scene->addPixmap(*gate);
                gateItem->setPos(gatePos, gatePos2);
             }

            else if(level.map[a][b] == 5){
                int lifePos = b * 30;
                int lifePos2 = a * 30;
                QPixmap *life = new QPixmap("Data/Sprites/up.bmp");
                lifeItem = scene->addPixmap(*life);
                lifeItem->setPos(lifePos, lifePos2);
            }

            else if(level.map[a][b] == 6){
                int portalPos = b * 30;
                int portalPos2 = a * 30;
                QPixmap *portal = new QPixmap("Data/Sprites/teleport.bmp");
                QGraphicsPixmapItem *portalItem = scene->addPixmap(*portal);
                portalItem->setPos(portalPos, portalPos2);
            }

            else if(level.map[a][b] == 7){
                int bonusLifePos = b * 30;
                int bonusLifePos2 = a * 30;
                QPixmap *bonusLife = new QPixmap("Data/Sprites/extra.bmp");
                lifeItem = scene->addPixmap(*bonusLife);
                lifeItem->setPos(bonusLifePos, bonusLifePos2);
            }
         }
     }
 }

void MainWindow::clearLevel(){
    scene->removeItem(player);
    scene->removeItem(levels);
    scene->removeItem(lives);
    scene->removeItem(timeText);
    scene->clear();
    scene->addItem(player);
    scene->addItem(levels);
    scene->addItem(lives);
    scene->addItem(timeText);

    monsters.clear();
}

void MainWindow::initializeMobs(){
    for(int a = 0; a < level->mobs; a++){
        QPoint *newMobPos = level->mobs_Pos[a];

        Monster *newMob = new Monster(newMobPos->rx() * 30, newMobPos->ry() * 30);
        monsters.push_back(newMob);
        scene->addItem(newMob);

    }
}

void MainWindow::moveMobs(){
    for(int a = 0; a < level->mobs; a++){
        monsters[a]->random_move(level, a);

        if(check_if_dead()){
            player->die();
            level->resetPlayer();
            drawText();
            resetMobsPos();

            if(player->rLives() == 0){
                delete timer;
                scene->removeItem(player);
                scene->removeItem(levels);
                scene->removeItem(lives);
                scene->removeItem(timeText);
                scene->clear();

                monsters.clear();
                TextGameOver();

                return;
            }
        }
    }
}

bool MainWindow::check_if_dead(){
    for(int a = 0; a < level->mobs; a++){
        if(level->playerPos.rx() == monsters[a]->rmX() && level->playerPos.ry() == monsters[a]->rmY()){
            return true;
        }

        else {
            // meatspin.com meatspin.com meatspin.com
        }
    }

    return false;
}

void MainWindow::drawText(){
    QString a = "Level ";

    a.insert(6, QString::number(level->level));
    a.insert(0, "<h2>");
    a.insert(a.size(), "</h2>");

    levels->setHtml(a);

    a = "Lives ";

    a.insert(6, QString::number(player->rLives()));
    a.insert(0, "<h2>");
    a.insert(a.size(), "</h2>");

    lives->setHtml(a);

}

void MainWindow::resetMobsPos(){
    for(int a = 0; a < level->mobs; a++){
        for(int a = 0; a < 15; a++){
            for(int b = 0; b < 15; b++){
                if(level->map[a][b] == 4){
                    level->map[a][b] = 0;
                }
            }
        }
        monsters[a]->setMapPos(monsters[a]->defPos.x(), monsters[a]->defPos.y());
        monsters[a]->setPos(monsters[a]->defPos.y() * 30, monsters[a]->defPos.x() * 30);

        level->map[monsters[a]->defPos.x()][monsters[a]->defPos.y()] = 4;
    }
}

void MainWindow::TextGameFinish(){
    QPixmap *gamefinish = new QPixmap("Data/Text/congratulations.bmp");
    QGraphicsPixmapItem *gfitem = scene->addPixmap(*gamefinish);

    gfitem->setPos(75, 210);
}

void MainWindow::TextGameOver(){
    QPixmap *gameover = new QPixmap("Data/Text/game_over.bmp");
    QGraphicsPixmapItem *goitem = scene->addPixmap(*gameover);

    goitem->setPos(75, 210);
}

void MainWindow::addTime(){
    time = time + 0.1;

    QString sTime = "Time: ";
    sTime.insert(6, QString::number(time));
    sTime.insert(0, "<h2>");
    sTime.insert(sTime.size(), "</h2>");

    timeText->setHtml(sTime);
}

void MainWindow::GameOptions(){
    QWidget *optionsWindow = new QWidget();
    optionsWindow->setFixedSize(250, 150);
    optionsWindow->setWindowTitle("Options");

    QCheckBox *soundBox = new QCheckBox("Sounds", optionsWindow);
    soundBox->setGeometry(10, 10, 100, 50);

    if(soundOn == true){
        soundBox->setCheckState(Qt::Checked);
    }

    optionsWindow->show();

    connect(soundBox, SIGNAL(stateChanged(int)), this, SLOT(turnSounds(int)));
}

void MainWindow::turnSounds(int a){
    if(a == Qt::Checked){
        soundOn = true;
    }

    else {
        soundOn = false;
    }
}

void MainWindow::GameHallOfFame(){
    QWidget *highScoreWindow = new QWidget();
    highScoreWindow->setFixedSize(250, 400);
    highScoreWindow->setWindowTitle("Highscores");

    QFile file("Data/hof.dat");
    QTextStream stream(&file);
    QStringList list;
    QVBoxLayout *ddlayout = new QVBoxLayout(highScoreWindow);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "SOMETHING TERRIBLE IS HAPPENING";

    for(int a = 0; a < 10; a++){
        list.append(stream.readLine());
        QString bxx = list.at(a);
        bxx.insert(0, QString(QString::number(a + 1) + ". "));
        QLabel *label = new QLabel(bxx, highScoreWindow);
        QLabel *hline = new QLabel("<hr />", highScoreWindow);
        label->setFont(QFont("Verdana"));
        ddlayout->addWidget(label);
        ddlayout->addWidget(hline);
    }

    highScoreWindow->setLayout(ddlayout);
    highScoreWindow->show();
}

void MainWindow::StartGame(){
    gameStarted = true;
    this->setStyleSheet("color: white");

    delete startGame;
    delete options;
    delete credits;
    delete exitGame;
    delete hallOfFame;
    delete rtcTitle;
    delete menuCastle;

    delete menuButtons;

    view->setScene(scene);
    view->setGeometry(0, 0, 452, 482);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSceneRect(0, 0, 450, 480);
    scene->setBackgroundBrush(QBrush(Qt::black));

    levels->setDefaultTextColor(QColor(Qt::white));
    lives->setDefaultTextColor(QColor(Qt::white));
    timeText->setDefaultTextColor(QColor(Qt::white));

    levels->setPos(15, 450);
    lives->setPos(170, 450);
    timeText->setPos(300, 450);

    player = new Player(level->playerPos.rx() * 30, level->playerPos.ry() * 30);

    scene->addItem(player);
    scene->addItem(levels);
    scene->addItem(lives);
    scene->addItem(timeText);

    drawLevel(*level);
    initializeMobs();

    drawText();

    connect(timer, SIGNAL(timeout()), this, SLOT(moveMobs()));
    connect(playing_time, SIGNAL(timeout()), this, SLOT(addTime()));

    timer->start(1000);
    playing_time->start(100);

}

void MainWindow::ExitGame(){
    exit(0);
}

void MainWindow::saveHighScore(){
    QString congratz("You reached level ");
    congratz.insert(congratz.size(), QString::number(level->level));
    congratz.insert(congratz.size(), " in ");
    congratz.insert(congratz.size(), QString::number(time));
    congratz.insert(congratz.size(), " seconds.");

    QWidget *highScoreW = new QWidget();
    highScoreW->resize(300, 150);
    highScoreW->setWindowTitle("Hall of Fame");

    QLabel *text = new QLabel(congratz, highScoreW);
    QPushButton *save = new QPushButton("Save", highScoreW);
    name = new QLineEdit(highScoreW);

    QHBoxLayout *highScoreLayout = new QHBoxLayout();
    highScoreLayout->addWidget(name);
    highScoreLayout->addWidget(save);

    QVBoxLayout *daLayout = new QVBoxLayout(highScoreW);
    daLayout->addWidget(text);
    daLayout->addLayout(highScoreLayout);

    name->setMaxLength(15);

    highScoreW->setLayout(daLayout);
    highScoreW->show();

    connect(save, SIGNAL(clicked()), this, SLOT(writeHighScore()));
}

void MainWindow::inGameMenu(){

}

void MainWindow::GameCredits(){
    QWidget *creditsWindow = new QWidget();
    creditsWindow->setFixedSize(250, 150);
    creditsWindow->setWindowTitle("Credits");

    QString credits = "\n\n\    Coding: Kanghu.\n    Sounds: Soundjay.com.\n\n\    Original RTC created by Andy.";
    QLabel *label = new QLabel(credits, creditsWindow);
    label->setFont(QFont("Verdana", 10));

    creditsWindow->show();
}

void MainWindow::writeHighScore(){
    playerName = name->text();
    playerName.remove(QChar(' '), Qt::CaseInsensitive);

    score->initialize(level->level, this->time, this->playerName);
    score->write_highscore();

    qApp->exit(0);
}
