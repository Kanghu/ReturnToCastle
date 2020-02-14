#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QPoint>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>
#include <vector>
#include <QSound>

#include "monster.h"
#include "definitions.h"

class MainWindow;

class Level
{

public:
    Level(QString path);

    void initialize(QString path);
    void clearMap();

    void implantLifePack();
    void removeLifePack();

    void movePlayer(int pos);
    void resetPlayer();

    bool check_if_move_able(int pos);
    bool check_if_next_level();
    bool check_if_life_pack();
    bool check_if_portal();

    void nextLevel();

    friend class MainWindow;
    friend class Monster;
    friend class Player;

private:
    int map[15][15];

    int mobs;
    int gates;
    int portals;

    int level;

    int lifeType;

    QPoint playerPos;
    QPoint startPos;
    QPoint lifePos;

    std::vector<QPoint*> mobs_Pos;
    std::vector<QPoint*> gates_Pos;
    std::vector<QPoint*> portals_Pos;

};

#endif // LEVEL_H
