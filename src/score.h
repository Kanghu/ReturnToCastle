#ifndef SCORE_H
#define SCORE_H

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QDebug>

class Score
{
public:
    Score(int level, float time, QString name);
    Score();
    void initialize(int level, float time, QString name);
    void write_highscore();

private:
    int level;
    float time;
    QString name;
};

#endif // SCORE_H
