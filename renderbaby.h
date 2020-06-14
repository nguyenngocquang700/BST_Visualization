#ifndef RENDERBABY_H
#define RENDERBABY_H
#include <QScrollArea>
#include <QMouseEvent>
#include <QWidget>
#include <renderarea.h>
class Renderbaby : public QScrollArea
{
public:
    explicit Renderbaby(RenderArea *rd,QScrollArea *parent = 0);
    RenderArea *render;

public slots:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif // RENDERBABY_H
