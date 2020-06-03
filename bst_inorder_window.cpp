#include "bst_inorder_window.h"
#include <iostream>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

Bst_inorder_window :: Bst_inorder_window(BinarySearchTree<int> *bst,QWidget *parent) : QMainWindow(parent)
{
    //Stack
    this->setWindowTitle("Pre Order");
    this->setFixedSize(QSize(300,300));
    stackLabel = new QLabel("Stack");
    stackLineEdit = new QLineEdit("");
    stackLineEdit->setStyleSheet("color: black; width: 100px;"
                                 "padding-left: 10px; font-size: 14px;");
    //Renderarea

    renderarea = new RenderArea(bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderarea);
    treeScrollArea->installEventFilter(renderarea);
    //Demo code
    QVBoxLayout *textAreaLayout = new QVBoxLayout();
    QTextEdit *txtEdit = new QTextEdit("");
    txtEdit->setStyleSheet("background-color: white; color: black;");
    txtEdit->setFixedWidth(100);
    txtEdit->setReadOnly(true);
    textAreaLayout->addWidget(txtEdit);

    QHBoxLayout *contain = new QHBoxLayout();
    contain->addWidget(treeScrollArea);
    contain->addLayout(textAreaLayout);

    QVBoxLayout *central = new QVBoxLayout();
    central->addWidget(stackLabel);
    central->addWidget(stackLineEdit);
    central->addLayout(contain);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(central);

    this->setCentralWidget(centralWidget);
}

Bst_inorder_window::~Bst_inorder_window()
{
    delete stackLabel;
    delete stackLineEdit;
    delete renderarea;
    delete treeScrollArea;
}

void Bst_inorder_window::recursive_bst(BinarySearchTree<int> *bst)
{
}
void Bst_inorder_window::show()
{
    this->setVisible(true);
    this->setWindowIcon(QIcon(":/new/prefix1/Icon/important_property.png"));
    this->activateWindow();
    return;
}

void Bst_inorder_window::close()
{
    this->close();
    return;
}


