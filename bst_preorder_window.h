#ifndef BST_PREORDER_WINDOW_H
#define BST_PREORDER_WINDOW_H
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
#include <QToolBar>


class Bst_preorder_window : public QMainWindow
{

    QWidget *centralWiget;
public:
    explicit Bst_preorder_window(BinarySearchTree<int> *bst,QWidget *parent=0);
    ~Bst_preorder_window();
    void show();
    void close();
    void recursive_bst(BinarySearchTree<int> *bst);
    QLineEdit *code1;
    QLineEdit *code2;
    QLineEdit *code3;
    QLineEdit *code4;
    QLineEdit *code5;

private:
    QLabel *stackLabel;
    QLineEdit *stackLineEdit;
    RenderArea *renderarea;
    QScrollArea *treeScrollArea;
    QPushButton *exitButton;
    BinarySearchTree<int> *bst1;

private slots:
    void recursive_bst_clicked();
    void exitSlot();
};

#endif // BST_PREORDER_WINDOW_H
