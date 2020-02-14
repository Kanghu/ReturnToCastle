#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QDebug>
#include <iostream>
#include <vector>

#include "player.h"
#include "level.h"
#include "monster.h"
#include "menulabel.h"
#include "score.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *e);

    void initializeMobs();

    void clearLevel();
    void drawLevel(Level level);

    void movePlayer(int pos);
    bool check_if_dead();

    void drawText();
    void TextGameOver();
    void TextGameFinish();

    void inGameMenu();
    void saveHighScore();

    void resetMobsPos();

    friend class Level;

private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    QGraphicsTextItem *levels;
    QGraphicsTextItem *lives;
    QGraphicsTextItem *timeText;
    QGraphicsPixmapItem *lifeItem;

    MenuLabel *startGame;
    MenuLabel *options;
    MenuLabel *credits;
    MenuLabel *hallOfFame;
    MenuLabel *exitGame;
    QLabel *menuCastle;

    QVBoxLayout *menuButtons;

    Level *level;
    Score *score;

    float time;
    bool gameStarted;

    QTimer *timer;
    QTimer *playing_time;

    QLabel *rtcTitle;

    QLineEdit *name;
    QString playerName;

    Player *player;
    std::vector<Monster*> monsters;

private slots:
    void moveMobs();
    void addTime();

    void StartGame();
    void GameOptions();
    void GameCredits();
    void GameHallOfFame();
    void ExitGame();

    void writeHighScore();
    void turnSounds(int a);

};

#endif // MAINWINDOW_H
