
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
//    QTabWidget* tw = new QTabWidget();

    // Set background to white so that when the RenderArea is
    // saved as an image (or the RenderArea is grabbed) the
    // the background will be white
    //this->setStyleSheet("background-color: white;");

//    this->nodeColor = Qt::red;
//    this->backgroundColor = Qt::black;
//    this->textColor = Qt::black;
//    QMovie *movie = new QMovie(":/new/prefix1/Background/76252.jpg");
//    QLabel *processLabel = new QLabel(this);
//    processLabel->setMovie(movie);
//    movie->start();

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
void RenderArea::paintEvent(QPaintEvent *  event )
{
    // Only repaint the tree if it's not empty
    if (this->bst->isEmpty())
        return;
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

//    QBrush brush;
//    brush.setColor(this->nodeColor);
//    brush.setStyle(Qt::SolidPattern);
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
//    this->backgroundColor = c;
//    QString style("background-color: ");
//    style.append(c.name());
//    style.append(";");
//    this->setStyleSheet(style);
//    QPainter* pPainter = new QPainter();
//    pPainter->drawPixmap(rect(), QPixmap(":/new/prefix1/Background/76252.jpg"));
//    delete pPainter;
//    QWidget::paintEvent(pe);
//    setStyleSheet("background-image: url(:/images/bg.png)");
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

//void MyWidget::wheelEvent(QWheelEvent *event)
//{
//    QPoint numPixels = event->pixelDelta();
//    QPoint numDegrees = event->angleDelta() / 8;

//    if (!numPixels.isNull()) {
//        scrollWithPixels(numPixels);
//    } else if (!numDegrees.isNull()) {
//        QPoint numSteps = numDegrees / 15;
//        scrollWithDegrees(numSteps);
//    }

//    event->accept();
//}
// Handle mouse clicking that is done on the QScrollArea that should
// be handled by the RenderArea (for zooming)

//void RenderArea::ShowContextMenuNode(QContextMenuEvent *event){
//    QMenu *menu = new QMenu(this);
//    QAction *DeleteNodeAction = new QAction(tr("Delete this node"));
//    connect(DeleteNodeAction, SIGNAL(triggered()), this, SLOT(this->bst->deleteAtLocation(QMouseEvent::x(), QMouseEvent::y())));
//    menu->addAction(DeleteNodeAction);
//    menu->exec(event->globalPos());
//    this->repaint();
//}

bool RenderArea::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mb = static_cast<QMouseEvent *>(event);
        if(mb->button() == Qt::RightButton){
            QMenu *menu = new QMenu(this);
//            QAction *DeleteNodeActon = new QAction(tr("Delete this Node"));
//            connect(DeleteNodeActon, SIGNAL(triggered()), this, SLOT(&BinarySearchTree::deleteAtLocation(mb->x(), mb->y())));
//            menu->addAction(insertAction);
//            menu->addAction(insertActions());
//            this->repaint();

        }
        if(mb->modifiers() == Qt::ControlModifier && mb->button() == Qt::BackButton){
            this->zoomIn();
        }
        else if(mb->modifiers() == Qt::ControlModifier && mb->button() == Qt::RightButton){
            this->zoomOut();
        }
        else return true;
//        switch(mb->button()){
//        case Qt::LeftButton:
//            this->zoomIn();
//            break;
//        case Qt::RightButton:
//            this->zoomOut();
//            break;
//        default:
//            return true;
//        }
    }

    return true;
}

// Auto size the render area based on the required size by the tree
void RenderArea::autoSize() {
    QSize size(bst->getTotalX(), bst->getTotalY());
    this->setMinimumSize(size);
    this->resize(size);
}

// Detect mouse release on render area
//void RenderArea::mouseReleaseEvent(QMouseEvent *event)
//{
//    if(event->modifiers() == Qt::ControlModifier && event->button() == Qt::LeftButton){
//        this->zoomOut();
//    }
//    else if(event->modifiers() == Qt::ControlModifier && event->button() == Qt::RightButton){
//        this->zoomIn();
//    }
//    else return;
//    switch(event->button()){
//    case Qt::LeftButton:
//        if ( event->modifiers() & Qt::ControlModifier )
//        {
//            // search for a node at the provided location and delete it. Returns false if no node was found.
//            this->zoomIn();
//            break;
//        }
//        break;
//    case Qt::RightButton:
//       if( event->modifiers() & Qt::ControlModifier)
//        this->zoomOut();
//        break;
//    default:
//        return;
//    }

//    this->bst->deleteAtLocation(event->x(), event->y());
//    this->repaint();
//    if(event->button() == Qt::ControlModifier && event->button() == Qt::LeftButton)
//}


void RenderArea::InitColor()
{
    this->bst->getInOrderTraversal();
    return;
}
