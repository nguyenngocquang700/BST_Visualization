#include "renderbaby.h"


Renderbaby::Renderbaby(RenderArea *rd,QScrollArea *parent) : QScrollArea(parent)
{
    this->render = rd;
    setWidget(render);
    setStyleSheet("background-color: #cde5f9");
}

void Renderbaby::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint p;
    p.setX(75);
    p.setY(45);
    switch(event->button()){
        case Qt::LeftButton:
            this->render->move(event->pos()- p);
            break;
        default:
        break;
    }
    return;
}
