#ifndef BST_INORDER_WINDOW_H
#define BST_INORDER_WINDOW_H

#include "binarysearchtree.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include "renderarea.h"

class Bst_inorder_window:public QMainWindow
{
    QWidget *centralWiget;
public:
    explicit Bst_inorder_window(BinarySearchTree<int> *bst,QWidget *parent=0);
    ~Bst_inorder_window();
    void recursive_bst(BinarySearchTree<int> *bst);
    void show();
    void close();
//    void getbst(BinarySearchTree<int> *bst);
private:
    QLabel *stackLabel;
    QLineEdit *stackLineEdit;
    RenderArea *renderarea;
    QScrollArea *treeScrollArea;
    BinarySearchTree<int> *bst1;

private slots:
    void recursive_bst_clicked();
    void exitSlot();
};

#endif // BST_INORDER_WINDOW_H
