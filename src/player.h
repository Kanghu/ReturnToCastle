#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QSound>

#include "definitions.h"
#include "level.h"

class Level;

class Player : public QGraphicsItem
{

private:

    int x, y;
    int lives;
    int position;

    QPoint defPos;

    QPixmap *pixmap;

public:

    Player(int x, int y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int rx();
    int ry();
    int rLives();

    void setDefaultPos(int x, int y);

    void move(int position);
    void pickLife();
    void pickExtraLife();
    void die();

    void goToRandomPos(Level *level);

    void changeSideLeft();
    void changeSideRight();


};

#endif // PLAYER_H
