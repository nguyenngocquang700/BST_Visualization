#include "bst_preorder_window.h"
#include <iostream>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QAction>
#include <sstream>

Bst_preorder_window::Bst_preorder_window(BinarySearchTree<int> *bst,QWidget *parent) : QMainWindow(parent)
{
    //Stack TEXTBOX
    this->setWindowTitle("Pre-order Traversal");
    this->setFixedSize(QSize(600,750));
    stackLabel = new QLabel("Stack");
    stackLineEdit = new QLineEdit("");
    stackLineEdit->setReadOnly(true);

    stackLineEdit->setStyleSheet("color: black; width: 100px;"
                                 "padding-left: 10px; font-size: 14px;");
    //Renderarea
    this->bst1 = bst;

    renderarea = new RenderArea(bst1);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderarea);
    treeScrollArea->installEventFilter(renderarea);

    //===========================Create toolbar of play button=========================

    QToolBar *toolbar1 = addToolBar("Main Toolbar");
    QPixmap playpix(":/new/prefix1/Icon/play.png");
    QAction *playAction = new QAction(playpix, tr(""), this);
    connect(playAction,&QAction::triggered, this, &Bst_preorder_window::recursive_bst_clicked);
    toolbar1->addAction(playAction);
    toolbar1->setIconSize(QSize(40,40));
    addToolBar(Qt::LeftToolBarArea,toolbar1);

    //=============================Demo code======================================
    QVBoxLayout *textAreaLayout = new QVBoxLayout();
    code1 = new QLineEdit("If this is null" );
    code1->setFixedWidth(150);
    code1->setReadOnly(true);
    code2 = new QLineEdit("return");
    code2->setFixedWidth(150);
    code2->setReadOnly(true);
    code5 = new QLineEdit("visit this");
    code5->setFixedWidth(100);
    code5->setReadOnly(true);
    code3 = new QLineEdit("preOrder (left)");
    code3->setFixedWidth(220);
    code3->setReadOnly(true);
    code4 = new QLineEdit("preOrder (right)");
    code4->setFixedWidth(150);
    code4->setReadOnly(true);

    textAreaLayout->addWidget(code1);
    textAreaLayout->addWidget(code2);
    textAreaLayout->addWidget(code5);
    textAreaLayout->addWidget(code3);
    textAreaLayout->addWidget(code4);
    textAreaLayout->setAlignment(Qt::AlignTop);

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

Bst_preorder_window::~Bst_preorder_window()
{
    delete stackLabel;
    delete stackLineEdit;
    delete renderarea;
    delete treeScrollArea;
}

void Bst_preorder_window::recursive_bst_clicked()
{
    this->recursive_bst(bst1);
}

//=================CHANGE COLOR CODE TEXTBOX WHEN TRAVERSAL WAS COMPLETED========================
void Bst_preorder_window::recursive_bst(BinarySearchTree<int> *bst)
{

    QString traversal = bst->getPreOrderTraversal();
    std::stringstream ss(traversal.toStdString());
    std::string token=" ";
    QString ss1 = " ";
    while (!ss.eof())
    {
        ss >> token;
        QString test = QString::fromStdString(token);

        if (test == "a" || test == "b" || test == "c"||test == "d")
        {
            this->code1->setStyleSheet("background-color: white; color: black;");
            this->code2->setStyleSheet("background-color: white; color: black;");
            this->code3->setStyleSheet("background-color: white; color: black;");
            this->code4->setStyleSheet("background-color: white; color: black;");
            this->code5->setStyleSheet("background-color: white; color: black;");
            if (test == "a")
                this->code1->setStyleSheet("background-color: pink; color: black;");
            else
            if (test == "c")
                this->code3->setStyleSheet("background-color: pink; color: black;");
             else
            if (test == "d")
                this->code4->setStyleSheet("background-color: pink; color: black;");
             else
                this->code2->setStyleSheet("background-color: pink; color: black;");
        } else
        {
            bool t = bst->findandchange(test.toInt());
            if ( t == true)
             {
                 ss1.append(test + " ");
                 this->code5->setStyleSheet("background-color: pink; color: black;");
                 this->stackLineEdit->setText(ss1);
             }
        }
        this->renderarea->repaint();
        QThread::sleep(2);

    }
    QMessageBox::information(NULL,"Note","Pre-order traversal is complete!");
    this->renderarea->InitColor();
    this->code2->setStyleSheet("background-color: white; color: black;");
    this->renderarea->repaint();
    this->stackLineEdit->setText("");
}
void Bst_preorder_window::show()
{
    this->setVisible(true);
    this->setWindowIcon(QIcon(":/new/prefix1/Icon/important_property.png"));
    this->activateWindow();
    return;

}
