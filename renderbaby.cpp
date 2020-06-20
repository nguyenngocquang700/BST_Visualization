#include "renderbaby.h"


Renderbaby::Renderbaby(RenderArea *rd,QScrollArea *parent) : QScrollArea(parent)
{
    this->render = rd;
    setWidget(render);
    setStyleSheet("background-color: #cde5f9");
    // Pass any events that happen on the scroll area to the
    // render area (specifically clicking, so that renderArea
    // can zoom in/out when clicks happen
//    installEventFilter(render);

}

void Renderbaby::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint p;
    p.setX(172);
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
