#include "mainwindow.h"
#include "bst_inorder_window.h"
#include "bst_about_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStringListIterator>
#include <QIcon>
#include <QMessageBox>
#include <QMenu>
#include <QMovie>
#include <QtCore>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setStyleSheet("MainWindow {background-image:url(:/new/prefix1/Background/background.png)}");
    // Create default save directory
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);

    this->bst = this->getBST();

    this->createMenu();
//    this->createToolbar();

    inorder = new Bst_inorder_window(this->bst);
    postorder = new Bst_postorder_window(this->bst);
    preorder = new Bst_preorder_window(this->bst);


    // Build buttons and layout for buttons on the left of the window
    propertyButton = new QPushButton("", this);
    propertyButton->setToolTip("More information about Binary Search Tree");
    propertyButton->setCursor(Qt::PointingHandCursor);

    deleteButton = new QPushButton("", this);
    deleteButton->setToolTip("Delete a Node or more Nodes of Binary Search Tree");
    deleteButton->setCursor(Qt::PointingHandCursor);

    insertButton = new QPushButton("", this);
    insertButton->setToolTip("Insert a Node or more Nodes of Binary Search Tree");
    insertButton->setCursor(Qt::PointingHandCursor);

    NLRButton = new QPushButton("",this);
    NLRButton->setToolTip("Pre-order (NLR) traversal");
    NLRButton->setCursor(Qt::PointingHandCursor);

    LNRButton = new QPushButton("",this);
    LNRButton->setToolTip("In-order (LNR) traversal");
    LNRButton->setCursor(Qt::PointingHandCursor);

    LRNButton = new QPushButton("",this);
    LRNButton->setToolTip("Post-order (LNR) traversal");
    LRNButton->setCursor(Qt::PointingHandCursor);

    searchButton = new QPushButton("", this);
    searchButton->setToolTip("Search a Node by Value");
    searchButton->setCursor(Qt::PointingHandCursor);

    searchMinButton = new QPushButton("", this);
    searchMinButton->setToolTip("Search Minimize Node of Binary Search Tree");
    searchMinButton->setCursor(Qt::PointingHandCursor);

    searchMaxButton = new QPushButton("", this);
    searchMaxButton->setToolTip("Search Maximize Node of Binary Search Tree");
    searchMaxButton->setCursor(Qt::PointingHandCursor);

    leftRorateButton = new QPushButton("", this);
    leftRorateButton->setToolTip("Rotate the Binary Search Tree to Left");
    leftRorateButton->setCursor(Qt::PointingHandCursor);

    rightRorateButton = new QPushButton("", this);
    rightRorateButton->setToolTip("Rootate the Binary Search Tree to Right");
    rightRorateButton->setCursor(Qt::PointingHandCursor);


//    searchButton = new QPushButton("Search", this);

    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;

    // Set properties of buttons
    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    propertyButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/propertiesButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/deleteButton.png)0 0 0 0 stretch stretch;"
                                   "width: 173px;"
                                   "height: 50px;"
                                  "}");
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/insertButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    NLRButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    NLRButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/preorderButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    LRNButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    LRNButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/postorderButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    LNRButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    LNRButton->setStyleSheet("QPushButton {border-style: none; "
                                  "font-family: Consolas; "
                                  "background-image: url(:/new/prefix1/Icon/inorderButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    leftRorateButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    leftRorateButton->setStyleSheet("QPushButton {border-style: none; "
                                    "background-image: url(:/new/prefix1/Icon/leftRotateButton.png)0 0 0 0 stretch stretch;"
                                    "width: 173px;"
                                    "height: 50px;"
                                    "}");
    rightRorateButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    rightRorateButton->setStyleSheet("QPushButton {border-style: none; "
                                     "background-image: url(:/new/prefix1/Icon/rightRotateButton.png)0 0 0 0 stretch stretch;"
                                     "width: 173px;"
                                     "height: 50px;"
                                     "}");
    searchButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    searchButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/searchButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    searchMinButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    searchMinButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/sMinButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    searchMaxButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    searchMaxButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/sMaxButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");

    insertValueLineEdit->setFixedWidth(100);
    insertValueLineEdit->setToolTip("Enter single value or multiple values separated by space");

    deleteValueLineEdit->setFixedWidth(100);
    deleteValueLineEdit->setToolTip("Enter value to delete");

    searchValueLineEdit= new QLineEdit;
    searchValueLineEdit->setFixedWidth(100);
    searchValueLineEdit->setToolTip("Enter value to search");

    // Connect the slots to the button signals

    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));
    connect(searchValueLineEdit,SIGNAL(returnPressed()), this, SLOT(searchClicked()));
    connect(NLRButton,SIGNAL(clicked()),this,SLOT(bst_preorder()));
    connect(LNRButton,SIGNAL(clicked()),this,SLOT(bst_inorder()));
    connect(LRNButton,SIGNAL(clicked()),this,SLOT(bst_postorder()));
    connect(leftRorateButton, SIGNAL(clicked()), this, SLOT(leftRorateClicked()));
    connect(rightRorateButton, SIGNAL(clicked()), this, SLOT(rightRorateClicked()));
    connect(searchButton,SIGNAL(clicked()), this, SLOT(searchClicked()));
    connect(searchMinButton,SIGNAL(clicked()), this, SLOT(searchMinClicked()));
    connect(searchMaxButton,SIGNAL(clicked()), this, SLOT(searchMaxClicked()));

    // Create the toolbar

    QToolBar *toolbar = addToolBar("Main Toolbar");
    QPixmap loadpix(":/new/prefix1/Icon/add.png");
    QPixmap delpix(":/new/prefix1/Icon/delete.png");
    QPixmap zoominpix(":/new/prefix1/Icon/zoom-in.png");
    QPixmap zoomoutpix(":/new/prefix1/Icon/zoom-out.png");
    insertAction = new QAction(loadpix,tr("&Insert"), this);
    connect(insertAction,&QAction::triggered, this, &MainWindow::insertClicked);
    deleteAction = new QAction(delpix,tr("&Delete"), this);
    connect(deleteAction,&QAction::triggered, this, &MainWindow::deleteClicked);
    zoominAction = new QAction(zoominpix,tr("Zoom &In"), this);
    connect(zoominAction,&QAction::triggered, this, &MainWindow::zoomInClicked);
    zoomoutAction = new QAction(zoomoutpix,tr("Zoom &Out"), this);
    connect(zoomoutAction,&QAction::triggered, this, &MainWindow::zoomOutClicked);
    aboutAction->setIcon(QIcon(":/new/prefix1/Icon/about.png"));

    toolbar->addAction(insertAction);
    toolbar->addAction(deleteAction);
    toolbar->addAction(zoominAction);
    toolbar->addAction(zoomoutAction);
    toolbar->addAction(aboutAction);
    toolbar->addAction(exitAction);
    toolbar->setIconSize(QSize(50,70));
    toolbar->setFixedHeight(550);
    addToolBar(Qt::LeftToolBarArea,toolbar);

    // Create button layout and add buttons

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(deleteButton);
//    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
//    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addSpacing(40);
    buttonLayout->addWidget(NLRButton);
    buttonLayout->addWidget(LRNButton);
    buttonLayout->addWidget(LNRButton);
    buttonLayout->addSpacing(40);
//    buttonLayout->addWidget(statusLabel);
    buttonLayout->addWidget(leftRorateButton);
    buttonLayout->addWidget(rightRorateButton);
    buttonLayout->addSpacing(40);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(searchMinButton);
    buttonLayout->addWidget(searchMaxButton);
    QMovie *movie=new QMovie(":/new/prefix1/Background/gif_cat.gif");
    // Play GIF
    label=new QLabel(this);
    label->setGeometry(20,650,500,492);
    label->resize(200,192);
    label->setMovie(movie);
    movie->start();
//    QPixmap movie = QPixmap::grabWidget()

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);
//    renderArea->setMinimumSize(500, 550);
//    treeScrollArea->setMinimumSize(20,20);
//    treeScrollArea->setGeometry(200,200,200,200);
//    treeScrollArea->setFixedWidth(900);
    treeScrollArea->setFixedSize(950, 700);
    renderArea->setContentsMargins(10,10,10,10);
    treeScrollArea->setAlignment(Qt::AlignTop);
    treeScrollArea->setAlignment(Qt::AlignHCenter);

    // Pass any events that happen on the scroll area to the
    // render area (specifically clicking, so that renderArea
    // can zoom in/out when clicks happen
    treeScrollArea->installEventFilter(renderArea);
    treeScrollArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(treeScrollArea, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    // Create the main layout and add all the widgets to it

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);


    // Build the main window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setFixedSize(QSize(1300,800));
    this->setWindowTitle("Binary Search Tree Visualization");
    this->setWindowIcon(QIcon(":/new/prefix1/Icon/logo.png"));
    //this->showMaximized();

    // Create secondary windows (but do not display them)
    prop = new BST_Properties_Window();
    about = new BST_About_Window();

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   this->renderArea->callRepaint();
}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete propertyButton;
    delete deleteButton;
    delete insertButton;
    delete zoomInButton;
    delete zoomOutButton;
    delete treeScrollArea;
    delete prop;
    delete about;
    delete bst;
    delete centralWidget;
    delete inorder;
    delete searchButton;
    delete searchMaxButton;
    delete searchMinButton;
    delete leftRorateButton;
    delete rightRorateButton;
}

void MainWindow::createMenu()
{
    this->createActions();

    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    editMenu = this->menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(resetAction);

    aboutmenu = this->menuBar()->addMenu(tr("&About"));
    aboutmenu->addAction(aboutAction);
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
        /* Create an object context menu */
        QMenu * menu = new QMenu(this);
        /* Set the actions to the menu */
        menu->addAction(insertAction);
        menu->addAction(deleteAction);
        /* Call the context menu */
        menu->popup(this->renderArea->mapToGlobal(pos));
}

void MainWindow::createActions()
{
    QPixmap aboutpix(":/new/prefix1/Icon/about.png");
    QPixmap loadpix(":/new/prefix1/Icon/open.png");
    QPixmap savepix(":/new/prefix1/Icon/save.png");
    QPixmap exitpix(":/new/prefix1/Icon/exit.png");
    QPixmap resetpix(":/new/prefix1/Icon/reset.png");
    aboutAction = new QAction(aboutpix,tr("About"), this);
    aboutAction->setStatusTip("About Binary Search Tree Visualization");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutMenu);

    loadAction = new QAction(loadpix,tr("&Open"), this);
    loadAction->setShortcut(tr("CTRL+O"));
    loadAction->setStatusTip("Load a BST from a file");
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadFileMenu);

    saveAction = new QAction(savepix,tr("&Save"), this);
    saveAction->setShortcut(tr("CTRL+S"));
    saveAction->setStatusTip("Save a BST to a file");
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveMenu);

    exitAction = new QAction(exitpix,tr("&Exit"), this);
    exitAction->setShortcut(tr("CTRL+Q"));
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitMenu);

    resetAction = new QAction(resetpix,tr("&Reset"), this);
    resetAction->setStatusTip("Reset the BST to be empty");
    connect(resetAction, &QAction::triggered, this, &MainWindow::resetMenu);

    changeNodeColorAction = new QAction(tr("&Node color"), this);
    changeNodeColorAction->setStatusTip("Change Node Color");
    connect(changeNodeColorAction, &QAction::triggered, this, &MainWindow::changeNodeColorMenu);

    changeBackgroundColorAction = new QAction(tr("&Background color"), this);
    changeBackgroundColorAction->setStatusTip("Change Background Color");
    connect(changeBackgroundColorAction, &QAction::triggered, this, &MainWindow::changeBackgroundColorMenu);

    changeTextColorAction = new QAction(tr("Node &text color"), this);
    changeTextColorAction->setStatusTip("Change Node Text Color");
    connect(changeTextColorAction, &QAction::triggered, this, &MainWindow::changeTextColorMenu);

}

void MainWindow::closeEvent(QCloseEvent *event)
{

    // Save BST before closing
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer/last_bst.txt";

    QString text = bst->getPreOrderTraversal();
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
    }
    this->saveSettings();

    prop->closePropertyWindow(); // close property window
    about->close(); // close about window
    event->setAccepted(true); // set whether to close application or not
    return;
}

// Slot for property button


void MainWindow::bst_inorder()
{
    inorder->show();
    return;
}

void MainWindow::bst_preorder()
{
    preorder->show();
    return;
}

void MainWindow::bst_postorder()
{
    postorder->show();
    return;
}
void MainWindow::propertyClicked() const
{
    // show and update the properties gui
    prop->show();
    prop->update(this->bst);
    return;
}

// Slot for delete button
void MainWindow::deleteClicked() const {

    QString value;
    do
    {
        deleteButton->setWindowIcon(QIcon(":/new/prefix1/Icon/delete.png"));
        value = QInputDialog::getText(deleteButton, tr("Delete"),tr("Remove Value:"),QLineEdit::Normal,0);
        if(value.toInt()<-2147483647||value.toInt()>2147483646)
        {
             QMessageBox::information(NULL,"Remove","gia tri nam ngoai vung qui dinh");
        }
    }
    while(value.toInt()<-2147483647||value.toInt()>2147483646);

    QString traversal = this->bst->getNode(value.toInt());
    std::stringstream ss(traversal.toStdString());
    std::string token=" ";
    QWidget *win = new QMessageBox();
    int reply = QMessageBox::warning(win,"Remove","Are you sure to delete this Node?",QMessageBox::Yes,QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        // traversal
        if(!bst->isEmpty())
        {
            QString traversal = this->bst->getNode(value.toInt());;
            std::stringstream ss(traversal.toStdString());
            std::string token=" ";
            while (ss >> token)
            {
                bst->searchNotValue(QString::fromStdString(token).toInt());
                this->renderArea->repaint();
                QThread::sleep(2);
            }
        }
        //delete
        if(!this->bst->deleteItem(value.toInt()))
        {
            QMessageBox::information(win,"Remove","Value is not in tree...",QMessageBox::Yes);
            this->renderArea->InitColor();
            this->renderArea->repaint();

        }
        else
        {
            this->renderArea->InitColor();
            this->renderArea->repaint(); // repaint to show changes to tree

        }
        this->deleteValueLineEdit->setText(""); // clear text box

    }

    return;
}


// Slot for insert button

void MainWindow::insertClicked() const
{

    QString values;
    do{
        insertButton->setWindowIcon(QIcon(":/new/prefix1/Icon/add.png"));
        values = QInputDialog::getText(insertButton, tr("Insert Node"),tr("Add Value:"),QLineEdit::Normal,0);
        if(values.toInt()<-2147483647||values.toInt()>2147483646){
             QMessageBox::information(NULL,"insert","gia tri nam ngoai vung qui dinh");
        }
    }
    while(values.toInt()<-2147483647||values.toInt()>2147483646);

    QWidget *win = new QMessageBox();
    int reply = QMessageBox::warning(win,"Insert","Are you sure????",QMessageBox::Ok,QMessageBox::No);
    if (reply == QMessageBox::Ok){
        //traversal
        if(!bst->isEmpty()){
            QString traversal = this->bst->getNode(values.toInt());;
            std::stringstream ss(traversal.toStdString());
            std::string token=" ";
            while (ss >> token)
            {
                bst->searchNotValue(QString::fromStdString(token).toInt());
                this->renderArea->repaint();
                QThread::sleep(2);
            }
        }
        //insert
        QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        QStringListIterator iterator(valueList);
        while (iterator.hasNext())
        {
            if(!this->bst->insert(iterator.next().toInt())) // inserts 0 if text isn't an int
            {
                QMessageBox::information(win,"Confirm Value","Duplicate value...",QMessageBox::Ok);
                this->renderArea->InitColor();
                this->renderArea->repaint();
            }
            else
            {
                this->renderArea->InitColor();
                this->renderArea->repaint();
                this->statusLabel->setText("Value inserted...");
                QMessageBox::information(win,"Confirm Value","Value inserted...",QMessageBox::Ok);

            }
        }
        insertValueLineEdit->setText(""); // clear text box
        return;
    }

}

// Slot for search
void MainWindow::searchClicked() const{

    QString value = QInputDialog::getText(searchButton, tr("Search"),tr("Search Value:"),QLineEdit::Normal,0);
    QWidget *win = new QMessageBox();
    int reply = QMessageBox::warning(win,"Search","Are you sure????",QMessageBox::Ok,QMessageBox::No);
    if (reply == QMessageBox::Ok)
    {

        if(bst->find(value.toInt())){
            QString traversal = this->bst->getNode(value.toInt());
//            QMessageBox::information(NULL,"Inorder",QString("inorder: "+traversal));
            std::stringstream ss(traversal.toStdString());
            std::string token=" ",token1=" ";
            while (ss >> token)
            {
                bst->searchValue(value.toInt(),QString::fromStdString(token).toInt());
                this->renderArea->repaint();
                QThread::sleep(2);
            }
            QMessageBox::information(win,"Search","Found.",QMessageBox::Ok);
              this->searchValueLineEdit->setText(""); // clear text box
}
        else{
            QString traversal = this->bst->getNode(value.toInt());
//            QMessageBox::information(NULL,"Inorder",QString("traversal: "+traversal));
            std::stringstream ss(traversal.toStdString());
            std::string token=" ",token1=" ";
            while (ss >> token)
            {
                bst->searchNotValue(QString::fromStdString(token).toInt());
                this->renderArea->repaint();
                QThread::sleep(2);
            }
              this->searchValueLineEdit->setText(""); // clear text box
            QMessageBox::information(win,"Search","Not Found.",QMessageBox::Ok);
        }
    }
    QThread::sleep(2);
    this->renderArea->InitColor();
}
//Slot for searchMin
void MainWindow::searchMinClicked() const{
    QWidget *win = new QMessageBox();
    int reply = QMessageBox::warning(win,"Search","Are you sure????",QMessageBox::Ok,QMessageBox::No);
    if (reply == QMessageBox::Ok)
    {
        QString traversal = this->bst->getLeftMostNode();
        std::stringstream ss(traversal.toStdString());
        std::string token=" ",token1=" ";
        while (ss >> token)
        {
            bst->searchMin((QString::fromStdString(token).toInt()));
            this->renderArea->repaint();
            QThread::sleep(2);
        }
        QMessageBox::information(NULL,"Search", QString("min: "+QString::number(this->bst->min())));
    }
    QThread::sleep(2);
    this->renderArea->InitColor();
}
//Slot for searchMax
void MainWindow::searchMaxClicked() const{
    QWidget *win = new QMessageBox();
    int reply = QMessageBox::warning(win,"Search","Are you sure????",QMessageBox::Ok,QMessageBox::No);
    if (reply == QMessageBox::Ok)
    {
        QString traversal = this->bst->getRightMostNode();
        std::stringstream ss(traversal.toStdString());

        std::string token=" ",token1=" ";
        while (ss >> token)
        {
            bst->searchMax((QString::fromStdString(token).toInt()));
            this->renderArea->repaint();
            QThread::sleep(2);
        }
              QMessageBox::information(NULL,"Search", QString("max: "+QString::number(this->bst->max())));
    }
    QThread::sleep(2);
    this->renderArea->InitColor();
}

// SLot for left rorate()
void MainWindow::leftRorateClicked() const{
    this->bst->leftRorate();
    QString traversal =this->bst->getPreOrderTraversal();
    this->bst->resetTree();
    this->renderArea->repaint();
    std::stringstream ss(traversal.toStdString());
    std::stringstream ss1(traversal.toStdString());
    std::string token=" ",token1=" ";

    while (ss1 >> token1)
    {
        if(!bst->isEmpty()){
            std::stringstream ss(traversal.toStdString());
            while (ss >> token)
            {
                bst->searchNotValue(QString::fromStdString(token).toInt());
                this->renderArea->repaint();
                QThread::msleep(300);
            }
        }
        bst->insert((QString::fromStdString(token1).toInt()));
        this->renderArea->repaint();
    }
    this->renderArea->InitColor();
    this->renderArea->repaint();

}

//Slot for right roarte()

void MainWindow::rightRorateClicked() const{


    this->bst->rightRorate();
    QString traversal =this->bst->getPreOrderTraversal();
    this->bst->resetTree();
    this->renderArea->repaint();
    std::stringstream ss(traversal.toStdString());
    std::stringstream ss1(traversal.toStdString());
    std::string token=" ",token1=" ";

    while (ss1 >> token1)
    {
        if(!bst->isEmpty()){
            std::stringstream ss(traversal.toStdString());
            while (ss >> token)
            {
                bst->searchNotValue(QString::fromStdString(token).toInt());
                this->renderArea->repaint();
                QThread::msleep(300);
            }
        }
        bst->insert((QString::fromStdString(token1).toInt()));
        this->renderArea->repaint();
    }
    this->renderArea->InitColor();
    this->renderArea->repaint();

}

// Slot for zoom in button
void MainWindow::zoomInClicked() const {
    this->statusLabel->setText("");
    renderArea->zoomIn();
    return;
}

// Slot for zoom out button
void MainWindow::zoomOutClicked() const {
    this->statusLabel->setText("");
    renderArea->zoomOut();
    return;
}

// Slot for load in the file menu
void MainWindow::loadFileMenu()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                 QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer",
                                 tr("Text files (*.txt)"));
    QMessageBox *win = new QMessageBox();
    QString text;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
//        this->statusLabel->setText("Could not open file!");
        QMessageBox::information(win,"Confirm Open File","Could not open file!",QMessageBox::Ok);
        return;
    }

    this->bst->resetTree();

    QTextStream reader(&file);

    while (!reader.atEnd())
    {
        reader >> text;
        if(text != " " && text != "")
            this->bst->insert(text.toInt());
    }
    file.close();

    this->renderArea->repaint();

//    this->statusLabel->setText("File successfully opened!");
    QMessageBox::information(win,"Confirm Open File","File successfully opened!",QMessageBox::Ok);
    return;
}

// Slot for save action in menu
void MainWindow::saveMenu()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                 QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer",
                                 tr("Text files (*.txt);;Images (*.png *.jpg)"));

    QMessageBox *win = new QMessageBox();

    if (QFileInfo(fileName).suffix() == "txt")
    {
        QString text = bst->getPreOrderTraversal();
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
//            this->statusLabel->setText("File was not saved!");
            QMessageBox::information(win,"Confirm Save File","File was not saved!",QMessageBox::Ok);
            return;
        }
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
//        this->statusLabel->setText("File successfully saved!");
        QMessageBox::information(win,"Confirm Save File","File successfully saved!",QMessageBox::Ok);
        return;
    }

    // if not txt, save as image
    if(!this->renderArea->grab().save(fileName))
    {
//        this->statusLabel->setText("Image was not saved...");
        QMessageBox::information(win,"Confirm Save File","Image was not saved...",QMessageBox::Ok);
        return;
    }
//    this->statusLabel->setText("Image saved...");
     QMessageBox::information(win,"Confirm Save File","Image saved...",QMessageBox::Ok);

    return;
}

// Slot for exit action in menu
void MainWindow::exitMenu()
{
    this->close();
    return;
}

// Slot for reset action in menu
void MainWindow::resetMenu() const
{
    QMessageBox *win = new QMessageBox();
    //this->statusLabel->setText("Reset tree...");
    QMessageBox::information(win,"Confirm Reset","Reset tree...");
    this->bst->resetTree();
    this->renderArea->repaint();
    return;
}

// Slot for about action in menu
void MainWindow::aboutMenu() const
{
    about->show();
    return;
}

// Slot for changing node color in menu
void MainWindow::changeNodeColorMenu()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        // change color
        this->renderArea->changeNodeColor(color);
        this->renderArea->repaint();
    }
    return;
}

// Slot for changing background color in menu
void MainWindow::changeBackgroundColorMenu()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        // change color
        QPalette pal(this->treeScrollArea->palette());
        pal.setColor(QPalette::Window, color);
        this->treeScrollArea->setPalette(pal);
        this->renderArea->changeBackgroundColor(color);
    }
    return;
}


// Slot for changing background color in menu
void MainWindow::changeTextColorMenu()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        // change color
        this->renderArea->changeTextColor(color);
        this->renderArea->repaint();
    }
    return;
}

BinarySearchTree<int>* MainWindow::getBST()
{

    BinarySearchTree<int> *bst = new BinarySearchTree<int>;

    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer/last_bst.txt";

    QString text;
    QFile file(fileName);

    // If the file doesn't exist or if it can't open, return an empty bst
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return bst;
    }

    QTextStream reader(&file);

    while (!reader.atEnd())
    {
        reader >> text;
        if (text != " " && text != "")
            bst->insert(text.toInt());
    }

    file.close();
    return bst;
}

void MainWindow::saveSettings()
{
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer/settings.txt";
    QString text;
    text = "text-color:" + this->renderArea->getTextColor().name() + "\n";
    text += "background-color:" + this->renderArea->getBackgroundColor().name() + "\n";
    text += "node-color:" + this->renderArea->getNodeColor().name() + "\n";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
    }
    return;
}

void MainWindow::loadSettings()
{
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer/settings.txt";
    QString text;
    QFile file(fileName);

    // If the file doesn't exist or if it can't open, return
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream reader(&file);

    while (!reader.atEnd())
    {
        reader >> text;
        QStringList list = text.split(":");
        QColor c(list.value(1));
        if (!c.isValid()){
            file.close();
            return;
        }
        if (list.value(0) == QString("background-color")){
            QPalette pal(this->treeScrollArea->palette());
            pal.setColor(QPalette::Window, c);
            this->treeScrollArea->setPalette(pal);
            this->renderArea->changeBackgroundColor(c);

        }else if (list.value(0) == QString("node-color")){
            this->renderArea->changeNodeColor(c);

        }else if (list.value(0) == QString("text-color")){
            this->renderArea->changeTextColor(c);
        }
    }
    file.close();
}
