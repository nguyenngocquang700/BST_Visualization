
#include "renderarea.h"
#include "binarysearchtree.h"
#include "mainwindow.h"
#include <QApplication>
#include <QPainter>
#include <qglobal.h>
#include <QTime>
#include <QPen>
#include <QScrollBar>
#include <QGraphicsView>
#include <QWidget>

RenderArea::RenderArea(BinarySearchTree<int> *bst, QWidget *parent) : QWidget(parent), bst(),
    scale(1.0)
{
    this->bst = bst;
    this->scale = 1.2;
}

QSize RenderArea::sizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

// What to do when the render area gets repaint() called
void RenderArea::paintEvent(QPaintEvent *  event)
{
    // Only repaint the tree if it's not empty
    if (this->bst->isEmpty())
        return;
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(this->textColor);

    painter.setBrush(brush);
    painter.setPen(pen);

    this->bst->draw(&painter, this->scale,brush);

    // Autosize the renderArea after the tree has been drawn.
    this->autoSize();
}

void RenderArea::changeNodeColor(QColor c)
{
    this->nodeColor = c;
}

void RenderArea::changeBackgroundColor(QColor c)
{

    // change color
    this->backgroundColor = c;
    QString style("background-color: ");
    style.append(c.name());
    style.append(";");
    this->setStyleSheet("background-color: #fdf9e0; color: black;");
}

void RenderArea::changeTextColor(QColor c)
{
    this->textColor = c;
}

QColor RenderArea::getNodeColor() const
{
    return this->nodeColor;
}

QColor RenderArea::getBackgroundColor() const
{
    return this->backgroundColor;
}

QColor RenderArea::getTextColor() const
{
    return this->textColor;
}

// For outside to call - makes sure that the size is set correctly for scroll areas.
void RenderArea::callRepaint()
{
    if (this->bst->isEmpty())
        return;

    this->scale += 0.1;
    this->repaint();
    this->scale -= 0.1;
    this->repaint();
}

// Increment the scale variable and redraw
void RenderArea::zoomIn() {
    if (this->bst->isEmpty())
        return;
    if(this->scale < 2.0){
        this->scale += 0.1;
        this->repaint();
    }
}

// Decrement the scale variable and redraw
void RenderArea::zoomOut() {
    if (this->bst->isEmpty())
        return;
    if(this->scale > 0.2) {
        this->scale -= 0.1;
        this->repaint();
    }
}


bool RenderArea::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mb = static_cast<QMouseEvent *>(event);
        switch(mb->button()){
        case Qt::LeftButton:
            this->zoomIn();
            break;
        case Qt::RightButton:
            this->zoomOut();
            break;
        default:
            return true;
        }
    }

    return true;
}

// Auto size the render area based on the required size by the tree
void RenderArea::autoSize() {
    QSize size(bst->getTotalX(), bst->getTotalY());
    this->setMinimumSize(size);
    this->resize(size);
}


void RenderArea::InitColor()
{
    this->bst->getInOrderTraversal();
    return;
}
