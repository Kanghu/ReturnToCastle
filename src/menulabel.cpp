#include "menulabel.h"

MenuLabel::MenuLabel(QWidget *parent) :
    QLabel(parent)
{

}

void MenuLabel::mousePressEvent(QMouseEvent *ev){

}

void MenuLabel::mouseMoveEvent(QMouseEvent *ev){
    \
}

void MenuLabel::mouseReleaseEvent(QMouseEvent *ev){
    emit pressed();
}

void MenuLabel::enterEvent(QEvent *ev){
    this->setStyleSheet("color: blue");
}

void MenuLabel::leaveEvent(QEvent *ev){
    this->setStyleSheet("color: white");
}
