#include "level.h"

Level::Level(QString path)
{
   level = 1;

   initialize(path);
   implantLifePack();
}

void Level::initialize(QString path){
    QFile file(path);
    QTextStream stream(&file);

    QString word;
    int x, y;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

    clearMap();

    while (!stream.atEnd()) {
        stream >> word;

        if(word == "Startpos"){
            stream >> x >> y;

            playerPos.setX(x);
            playerPos.setY(y);

            startPos.setX(x);
            startPos.setY(y);

            map[x][y] = 2;
        }

        else if(word == "Mobs"){
            stream >> x;
            mobs = x;

            for(int a = 0; a < mobs; a++){
                stream >> x;
                stream >> y;

                QPoint *mobPos = new QPoint(x, y);
                mobs_Pos.push_back(mobPos);

                map[y][x] = 4;
            }
        }

        else if(word == "Portals"){
            stream >> x;
            portals = x;

            for(int a = 0; a < portals; a++){
                stream >> x;
                stream >> y;

                QPoint *portalPos = new QPoint(x, y);
                portals_Pos.push_back(portalPos);

                map[x][y] = 6;
            }

        }

        else if(word == "Gates"){
            stream >> x;
            gates = x;

            for(int a = 0; a < gates; a++){
                stream >> x;
                stream >> y;

                QPoint *gatePos = new QPoint(x, y);
                gates_Pos.push_back(gatePos);

                map[x][y] = 3;
            }

        }

        else if(word == "Walls"){
            while(!stream.atEnd()){
                stream >> x >> y;

                map[x][y] = 1;
            }
        }
    }
}



bool Level::check_if_move_able(int pos){
    if(pos == NORTH){
        switch(map[playerPos.rx() - 1][playerPos.ry()]){
        case 0:
            return true;
        break;

        case 1:
            return false;
        break;

        }
    }

   else if(pos == SOUTH){
        switch(map[playerPos.rx() + 1][playerPos.ry()]){
        case 0:
            return true;
        break;

        case 1:
            return false;
        break;
        }
    }

   else if(pos == WEST){
        switch(map[playerPos.rx()][playerPos.ry() - 1]){
        case 0:
            return true;
        break;

        case 1:
            return false;
        break;
        }
    }

   else if(pos == EAST){
        switch(map[playerPos.rx()][playerPos.ry() + 1]){
        case 0:
            return true;
        break;

        case 1:
            return false;
        break;
        }
    }
}

void Level::movePlayer(int pos){
    switch(pos){
    case NORTH:
        map[playerPos.rx()][playerPos.ry()] = 0;
        map[playerPos.rx() - 1][playerPos.ry()] = 2;

        playerPos.setX(playerPos.rx() - 1);
        break;

    case SOUTH:
        map[playerPos.rx()][playerPos.ry()] = 0;
        map[playerPos.rx() + 1][playerPos.ry()] = 2;

        playerPos.setX(playerPos.rx() + 1);
        break;

    case EAST:
        map[playerPos.rx()][playerPos.ry()] = 0;
        map[playerPos.rx()][playerPos.ry() + 1] = 2;

        playerPos.setY(playerPos.ry() + 1);
        break;

    case WEST:
        map[playerPos.rx()][playerPos.ry()] = 0;
        map[playerPos.rx()][playerPos.ry() - 1] = 2;

        playerPos.setY(playerPos.ry() - 1);
        break;
    }
}

void Level::clearMap(){
    for(int a = 0; a < 15; a++){
        for(int b = 0; b < 15; b++){
            map[a][b] = 0;
        }
    }
}

bool Level::check_if_next_level(){
    for(int a = 0; a < gates; a++){
        if(playerPos.rx() == gates_Pos[a]->rx() && playerPos.ry() == gates_Pos[a]->ry()){
            return true;
        }

        else {
            // Don't forget to check meatspin.com
        }

    }

    return false;
}

void Level::nextLevel(){
    level += 1;

    mobs_Pos.clear();
    gates_Pos.clear();
    portals_Pos.clear();

    if(level > MAX_LEVEL){
        return;
    }

    QString levelPath = "Data/Levels/level_.dat";
    levelPath.insert(18, QString::number(level));

    if(soundOn == true){
    QSound::play("Data/Sounds/door.wav");
    }

    initialize(levelPath);
}

void Level::resetPlayer(){
    map[playerPos.rx()][playerPos.ry()] = 0;

    playerPos.setX(this->startPos.rx());
    playerPos.setY(this->startPos.ry());

    map[playerPos.rx()][playerPos.ry()] = 3;


}

void Level::implantLifePack(){
    int chance = qrand() % 7;
    int chance2 = qrand() % 20;

    if(chance == 1){
        for(;;){
            int x = qrand() % 15;
            int y = qrand() % 15;

            lifePos.setX(x);
            lifePos.setY(y);

            if(map[x][y] == 0){
                map[x][y] = 5;
                lifeType = 0;
                return;
            }
        }
    }

    if(chance2 == 1){
        for(;;){
            int x = qrand() % 15;
            int y = qrand() % 15;

            lifePos.setX(x);
            lifePos.setY(y);

            if(map[x][y] == 0){
                map[x][y] = 7;
                lifeType = 1;
                return;
            }
        }
    }
}

bool Level::check_if_life_pack(){

    if(playerPos.x() == lifePos.x() && playerPos.y() == lifePos.y()){
        return true;
    }

    else {
        return false;
    }
}

bool Level::check_if_portal(){
    for(int a = 0; a < portals; a++){
        if(playerPos.rx() == portals_Pos[a]->rx() && playerPos.ry() == portals_Pos[a]->ry()){
            return true;
        }

        else {
            // Don't forget to check meatspin.com
        }

    }

    return false;
}

void Level::removeLifePack(){
    lifePos.setX(-1);
    lifePos.setY(-1);
}

