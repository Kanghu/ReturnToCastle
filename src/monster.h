#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtCore>

#include "definitions.h"
#include "level.h"

class Level;

class Monster : public QGraphicsItem
{

private:
    int x, y;
    int mpX, mpY;

    QPixmap *pixmap;
public:
    Monster(int x, int y);
    Monster();

    QPoint defPos;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int rx();
    int ry();

    int rmX();
    int rmY();

    void move(int position);
    void random_move(Level *level, int a);

    void setMapPos(int x, int y);
};

#endif // MONSTER_H
