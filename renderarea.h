
#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include "binarysearchtree.h"
#include <QColor>
#include <QScrollBar>
#include <QMenu>
#include <QGraphicsView>
#include <QtWidgets>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(BinarySearchTree<int> *bst, QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void zoomIn();
    void zoomOut();
    bool eventFilter(QObject *, QEvent *event);
    void autoSize();
    void callRepaint();
    void changeNodeColor(QColor c);
    void changeBackgroundColor(QColor c);
    void changeTextColor(QColor c);
    QColor getNodeColor() const;
    QColor getBackgroundColor() const;
    QColor getTextColor() const;
    void ShowContextMenuNode(const QPoint&);
    void InitColor();


signals:

public slots:
    void paintEvent(QPaintEvent *event) override;
private:
    BinarySearchTree<int> *bst;
    BinarySearchTree<int> *root;
    double scale;
    QPen pen;
    QBrush brush;
    QColor backgroundColor;
    QColor nodeColor;
    QColor textColor;
    QMenu *RightClickedMenu;
};

#endif // RENDERAREA_H
