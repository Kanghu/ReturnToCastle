#include "score.h"

Score::Score(int level, float time, QString name)
{
    initialize(level, time, name);
}

Score::Score()
{

}

void Score::write_highscore()
{
    QFile file("Data/hof.dat");
    QTextStream stream(&file);
    QStringList list;
    QString line;
    QString stats = this->name;
    QString replacing_score;
    int x;
    float y;

    stats.append(" ");
    stats.append(QString::number(level));
    stats.append(" ");
    stats.append(QString::number(time));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "SOMETHING TERRIBLE IS HAPPENING";

    for(int a = 1; a <= 10; a++){
        list.append(stream.readLine());
    }

    stream.seek(0);

    for(int count = 0; count < 10; count++){
        stream >> line >> x >> y;

        replacing_score = line;
        replacing_score.insert(replacing_score.size(), line);
        replacing_score.insert(replacing_score.size(), " ");
        replacing_score.insert(replacing_score.size(), QString::number(x));
        replacing_score.insert(replacing_score.size(), " ");
        replacing_score.insert(replacing_score.size(), QString::number(y));

        if(this->level > x){
            for(int replaced = 9; replaced > count; replaced--){
                list.replace(replaced, list.at(replaced-1));
            }

            list.replace(count, stats);
            break;
        }

        else if(this->level == x && this->time < y){
            for(int replaced = 9; replaced > count; replaced--){
                list.replace(replaced, list.at(replaced-1));
            }

            list.replace(count, stats);
            break;
        }
    }

    file.close();

    QFile ndfile("Data/hof.dat");
    QTextStream ndstr(&ndfile);

    if (!ndfile.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

    for(int a = 0; a < 10; a++){
        ndstr << list.at(a) << endl;
    }

    ndfile.close();
}

void Score::initialize(int level, float time, QString name)
{
    this->level = level;
    this->time = time;
    this->name = name;
}
