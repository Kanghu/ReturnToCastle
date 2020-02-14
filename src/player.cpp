#include "player.h"

Player::Player(int x, int y)
{
    Player::x = x;
    Player::y = y;

    Player::lives = 7;

    pixmap = new QPixmap("Data/Sprites/player1.bmp");

    setPos(y, x);
    setDefaultPos(x / 30, y / 30);
}

void Player::move(int position){
    switch(position){

    case NORTH: moveBy(0, -30);
        x -= 30;
        break;
    case SOUTH: moveBy(0, 30);
        x += 30;
        break;
    case WEST: moveBy(-30, 0);
        y -= 30;
        break;
    case EAST: moveBy(30, 0);
        y += 30;
        break;

    }

}

int Player::rx(){
    return this->x;
}

int Player::ry(){
    return this->y;
}

void Player::changeSideLeft(){
    pixmap->load("Data/Sprites/player2.bmp");
}

void Player::changeSideRight(){
    pixmap->load("Data/Sprites/player1.bmp");
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(QRect(0, 0, 30, 30), *pixmap, QRect(0, 0, 30, 30));
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 30, 30);
}

void Player::die(){
    lives -= 1;

    setPos(defPos.ry() * 30, defPos.rx() * 30);
}

int Player::rLives(){
    return lives;
}

void Player::setDefaultPos(int x, int y){
    defPos.setX(x);
    defPos.setY(y);
}

void Player::pickLife(){
    lives += 1;
}

void Player::pickExtraLife(){
    lives += 3;
}

void Player::goToRandomPos(Level *level){
    for(;;){
        int randX = qrand() % 15;
        int randY = qrand() % 15;

        if(level->map[randX][randY] == 0){
            setPos(randY * 30, randX * 30);

            level->map[level->playerPos.x()][level->playerPos.y()] = 0;

            level->playerPos.setX(randX);
            level->playerPos.setY(randY);

            level->map[level->playerPos.x()][level->playerPos.y()] = 2;

            if(soundOn == true){
                QSound::play("Data/Sounds/teleport.wav");
            }

            return;
        }

        else {
            // check meatspin.com
        }
    }
}
