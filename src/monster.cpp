#include "monster.h"

Monster::Monster(int x, int y)
{
    Monster::x = x;
    Monster::y = y;

    setPos(x, y);

    Monster::mpY = x / 30;
    Monster::mpX = y / 30;

    defPos.setX(mpX);
    defPos.setY(mpY);

    pixmap = new QPixmap("Data/Sprites/mob.bmp");
}

Monster::Monster(){
    pixmap = new QPixmap("Data/Sprites/mob.bmp");
}

QRectF Monster::boundingRect() const{
    return QRectF(0, 0, 30, 30);
}

void Monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(QRect(0, 0, 30, 30), *pixmap, QRect(0, 0, 30, 30));
}

int Monster::rx(){
    return x;
}

int Monster::ry(){
    return y;
}

void Monster::move(int position){
    switch(position){

    case NORTH: moveBy(0, -30);
        x -= 30;
        mpX -= 1;
        break;
    case SOUTH: moveBy(0, 30);
        x += 30;
        mpX += 1;
        break;
    case WEST: moveBy(-30, 0);
        y -= 30;
        mpY -= 1;
        break;
    case EAST: moveBy(30, 0);
        y += 30;
        mpY += 1;
        break;

    }
}

void Monster::random_move(Level *level, int a){
        int random;
        random = qrand() % 4;

        switch(random){
        case NORTH:
            if(level->map[mpX - 1][mpY] == 0 || level->map[mpX - 1][mpY] == 2){
                level->map[mpX][mpY] = 0;
                level->map[mpX - 1][mpY] = 4;

                level->mobs_Pos[a]->setX(x - 1);
                move(NORTH);

                //qDebug() << "moved north";
            }

            break;

        case SOUTH:
            if(level->map[mpX + 1][mpY] == 0 || level->map[mpX + 1][mpY] == 2){
                level->map[mpX][mpY] = 0;
                level->map[mpX + 1][mpY] = 4;

                level->mobs_Pos[a]->setX(x + 1);
                move(SOUTH);

                //qDebug() << "moved south";
            }

            break;

        case WEST:
            if(level->map[mpX][mpY - 1] == 0 || level->map[mpX][mpY - 1] == 2){
                level->map[mpX][mpY] = 0;
                level->map[mpX][mpY - 1] = 4;

                level->mobs_Pos[a]->setY(y - 1);
                move(WEST);

                //qDebug() << "moved west";
            }

            break;

        case EAST:
            if(level->map[mpX][mpY + 1] == 0 || level->map[mpX][mpY + 1] == 2){
                level->map[mpX][mpY] = 0;
                level->map[mpX][mpY + 1] = 4;

                level->mobs_Pos[a]->setY(y + 1);
                move(EAST);

                //qDebug() << "moved east";
            }

            break;
        }

    }

int Monster::rmX(){
    return mpX;
}

int Monster::rmY(){
    return mpY;
}

void Monster::setMapPos(int x, int y){
    Monster::mpX = x;
    Monster::mpY = y;
}

