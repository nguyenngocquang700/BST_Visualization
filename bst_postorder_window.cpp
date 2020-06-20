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
    code1 = new QLineEdit("If this is null" );
//    code1->setStyleSheet("background-color: white; color: black;");
    code1->setFixedWidth(150);
    code1->setReadOnly(true);
    code2 = new QLineEdit("return");
//    code2->setStyleSheet("background-color: white; color: black;");
    code2->setFixedWidth(150);
    code2->setReadOnly(true);
    code3 = new QLineEdit("postOrder (left)");
//    code2->setStyleSheet("background-color: white; color: black;");
    code3->setFixedWidth(150);
    code3->setReadOnly(true);
    code4 = new QLineEdit("visit this, then postOrder (right)");
//    code3->setStyleSheet("background-color: white; color: black;");
    code4->setFixedWidth(220);
    code4->setReadOnly(true);

    textAreaLayout->addWidget(code1);
    textAreaLayout->addWidget(code2);
    textAreaLayout->addWidget(code3);
    textAreaLayout->addWidget(code4);
    textAreaLayout->setAlignment(Qt::AlignTop);

//    QHBoxLayout *buttonLayout = new QHBoxLayout;
//    buttonLayout->addStretch(0);
//    buttonLayout->addWidget(exitButton);


    QHBoxLayout *contain = new QHBoxLayout();
    contain->addWidget(treeScrollArea);
    contain->addLayout(textAreaLayout);

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
    QString traversal = bst->getPostOrderTraversal();
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
                 this->stackLineEdit->setText(ss1);
             }
        }
        this->renderarea->repaint();
        QThread::sleep(2);

    }
    QMessageBox::information(NULL,"Note","Post-order traversal is complete!");
    this->renderarea->InitColor();
    this->renderarea->repaint();
    this->stackLineEdit->setText("");
}

void Bst_postorder_window::show()
{
    this->setVisible(true);
    this->setWindowIcon(QIcon(":/new/prefix1/Icon/important_property.png"));
    this->activateWindow();
    return;
}
