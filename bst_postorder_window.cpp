#include "bst_postorder_window.h"
#include <iostream>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QAction>
#include <sstream>

Bst_postorder_window::Bst_postorder_window(BinarySearchTree<int> *bst,QWidget *parent) : QMainWindow(parent)
{
    //Stack
    this->setWindowTitle("Post-order Traversal");
    this->setFixedSize(QSize(600,750));
    stackLabel = new QLabel("Stack");
    stackLineEdit = new QLineEdit("");
    stackLineEdit->setReadOnly(true);

    stackLineEdit->setStyleSheet("color: black; width: 100px;"
                                 "padding-left: 10px; font-size: 14px;");

//    exitButton = new QPushButton("E&xit", this);
//    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));

    //Renderarea
    this->bst1 = bst;

    renderarea = new RenderArea(bst1);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderarea);
    treeScrollArea->installEventFilter(renderarea);
    //Create toolbar
    QToolBar *toolbar1 = addToolBar("Main Toolbar");
    QPixmap playpix(":/new/prefix1/Icon/play.png");
    QAction *playAction = new QAction(playpix, tr(""), this);
    connect(playAction,&QAction::triggered, this, &Bst_postorder_window::recursive_bst_clicked);
    toolbar1->addAction(playAction);
    toolbar1->setIconSize(QSize(40,40));
    addToolBar(Qt::LeftToolBarArea,toolbar1);


    //Demo code
    QVBoxLayout *textAreaLayout = new QVBoxLayout();
    QTextEdit *txtEdit = new QTextEdit("");
    txtEdit->setStyleSheet("background-color: white; color: black;");
    txtEdit->setFixedWidth(100);
    txtEdit->setReadOnly(true);
    textAreaLayout->addWidget(txtEdit);

//    QHBoxLayout *buttonLayout = new QHBoxLayout;
//    buttonLayout->addStretch(0);
//    buttonLayout->addWidget(exitButton);


    QHBoxLayout *contain = new QHBoxLayout();
    contain->addWidget(treeScrollArea);
//    contain->addLayout(textAreaLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackLabel);
    mainLayout->addWidget(stackLineEdit);
    mainLayout->addLayout(contain);
//    central->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
}

Bst_postorder_window::~Bst_postorder_window()
{
    delete stackLabel;
    delete stackLineEdit;
    delete renderarea;
    delete treeScrollArea;
}

void Bst_postorder_window::recursive_bst_clicked()
{
    this->recursive_bst(bst1);
}
void Bst_postorder_window::recursive_bst(BinarySearchTree<int> *bst)
{
//    bst->rightRorate();
    QString traversal = bst->getPostOrderTraversal();
    std::stringstream ss(traversal.toStdString());
 //   ss.str(traversal.toStdString());
    std::string token=" ",token1=" ";
    while (ss >> token)
    {
        bool t = bst->findandchange((QString::fromStdString(token).toInt()));
        if ( t == true)
        {
            token1.append(token + " ");
            QString ss1 = QString::fromStdString(token1);
            this->stackLineEdit->setText(ss1);
        }
        this->renderarea->repaint();
        QThread::sleep(2);

    }
    QThread::sleep(2);
    this->renderarea->InitColor();
    this->stackLineEdit->setText("");
}
void Bst_postorder_window::show()
{
    this->setVisible(true);
    this->setWindowIcon(QIcon(":/new/prefix1/Icon/important_property.png"));
    this->activateWindow();
    return;
}
