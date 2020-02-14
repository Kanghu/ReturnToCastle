#ifndef MENULABEL_H
#define MENULABEL_H

#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <QSound>

class MenuLabel : public QLabel
{
    Q_OBJECT
public:
    MenuLabel(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    virtual void enterEvent(QEvent *ev);
    virtual void leaveEvent(QEvent *ev);
    
signals:
    void pressed();
    
public slots:
    
};

#endif // MENULABEL_H
