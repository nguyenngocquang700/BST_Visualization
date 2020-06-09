

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
//    QMovie *movie = new QMovie(":/new/prefix1/Background/gif.gif");
//    QLabel *processLabel = new QLabel(this);
//    processLabel->setMovie(movie);
//    movie->start();
    // Create default save directory
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/BSTVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);

    this->bst = this->getBST();

    this->createMenu();
//    this->createToolbar();

    //NLR
//    inorder = new Bst_inorder_window(this->bst);
//    postorder = new Bst_postorder_window(this->bst);
//    preorder = new Bst_preorder_window(this->bst);
//    NLRButton = new QPushButton("NLR",this);
//    NLRButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    connect(NLRButton,SIGNAL(clicked()),this,SLOT(bst_preorder()));

    //LNR
//    LNRButton = new QPushButton("LNR",this);
//    LNRButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    connect(LNRButton,SIGNAL(clicked()),this,SLOT(bst_inorder()));

    //LRN

//    LRNButton = new QPushButton("LRN",this);
//    LRNButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    connect(LRNButton,SIGNAL(clicked()),this,SLOT(bst_postorder()));

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

    zoomInButton = new QPushButton("Zoom &In", this);
    zoomOutButton = new QPushButton("Zoom &Out", this);

//    searchButton = new QPushButton("Search", this);

    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;

    // Set properties of buttons
//    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    propertyButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/propertiesButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
//    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/deleteButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
//    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/insertButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    NLRButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/preorderButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    LNRButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/inorderButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    LRNButton->setStyleSheet("QPushButton {border-style: none; "
                                  "background-image: url(:/new/prefix1/Icon/postorderButton.png)0 0 0 0 stretch stretch;"
                                  "width: 173px;"
                                  "height: 50px;"
                                  "}");
    zoomInButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomOutButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertValueLineEdit->setFixedWidth(100);
    insertValueLineEdit->setToolTip("Enter single value or multiple values separated by space");

    deleteValueLineEdit->setFixedWidth(100);
    deleteValueLineEdit->setToolTip("Enter value to delete");

    //==============================================

    searchButton= new QPushButton("&Search",this);
    searchMinButton= new QPushButton("&SearchMin",this);
    searchMaxButton= new QPushButton("&SearchMax",this);
//    inorderButton= new QPushButton("&Inorder", this);
//    preorderButton= new QPushButton("&Preorder",this);
//    postorderButton= new QPushButton("&Postorder", this);
//    leftRorateButton= new QPushButton("&LeftRorate",this);
//    rightRorateButton= new QPushButton("&RightRorate",this);
    searchValueLineEdit= new QLineEdit;

    searchMinButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    searchMaxButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    searchButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    inorderButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    preorderButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    postorderButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    leftRorateButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    rightRorateButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    searchValueLineEdit->setFixedWidth(100);
    searchValueLineEdit->setToolTip("Enter value to search");



    //=========================================
    // Connect the slots to the button signals

    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(NLRButton, SIGNAL(clicked()), this, SLOT(bst_preorder()));
    connect(LNRButton, SIGNAL(clicked()), this, SLOT(bst_inorder()));
    connect(LRNButton, SIGNAL(clicked()), this, SLOT(bst_postorder()));

    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomInClicked()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOutClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

    connect(searchButton,SIGNAL(clicked()), this, SLOT(searchClicked()));
    connect(searchMinButton,SIGNAL(clicked()), this, SLOT(searchMinClicked()));
    connect(searchMaxButton,SIGNAL(clicked()), this, SLOT(searchMaxClicked()));
//    connect(inorderButton,SIGNAL(clicked()), this, SLOT(inorderClicked()));
//    connect(preorderButton,SIGNAL(clicked()), this, SLOT(preorderClicked()));
//    connect(postorderButton,SIGNAL(clicked()), this, SLOT(postorderClicked()));
//    connect(leftRorateButton, SIGNAL(clicked()), this, SLOT(leftRorateClicked()));
//    connect(rightRorateButton, SIGNAL(clicked()), this, SLOT(rightRorateClicked()));
    connect(searchValueLineEdit,SIGNAL(returnPressed()), this, SLOT(searchClicked()));
    // Create the toolbar

    QToolBar *toolbar = addToolBar("Main Toolbar");
    QPixmap loadpix(":/new/prefix1/Icon/add.png");
    QPixmap delpix(":/new/prefix1/Icon/delete.png");
    QPixmap zoominpix(":/new/prefix1/Icon/zoom-in.png");
    QPixmap zoomoutpix(":/new/prefix1/Icon/zoom-out.png");
    QAction *insertAction = new QAction(loadpix,tr("&Insert"), this);
    connect(insertAction,&QAction::triggered, this, &MainWindow::insertClicked);
    QAction *deleteAction = new QAction(delpix,tr("&Delete"), this);
    connect(deleteAction,&QAction::triggered, this, &MainWindow::deleteClicked);
    QAction *zoominAction = new QAction(zoominpix,tr("Zoom &In"), this);
    connect(zoominAction,&QAction::triggered, this, &MainWindow::zoomInClicked);
    QAction *zoomoutAction = new QAction(zoomoutpix,tr("Zoom &Out"), this);
    connect(zoomoutAction,&QAction::triggered, this, &MainWindow::zoomOutClicked);
    aboutAction->setIcon(QIcon(":/new/prefix1/Icon/about.png"));

    toolbar->addAction(insertAction);
    toolbar->addAction(deleteAction);
    toolbar->addAction(zoominAction);
    toolbar->addAction(zoomoutAction);
    toolbar->addAction(aboutAction);
    toolbar->addAction(exitAction);
    toolbar->setIconSize(QSize(50,50));
    toolbar->setFixedHeight(450);
    toolbar->addSeparator();
    addToolBar(Qt::LeftToolBarArea,toolbar);

    // Create button layout and add buttons

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(deleteButton);
//    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
//    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addWidget(NLRButton);
    buttonLayout->addWidget(LRNButton);
    buttonLayout->addWidget(LNRButton);

    buttonLayout->addSpacing(25);
    buttonLayout->addWidget(statusLabel);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(searchMinButton);
    buttonLayout->addWidget(searchMaxButton);
//    buttonLayout->addWidget(inorderButton);
//    buttonLayout->addWidget(preorderButton);
//    buttonLayout->addWidget(postorderButton);
//    buttonLayout->addWidget(leftRorateButton);
//    buttonLayout->addWidget(rightRorateButton);

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);
//    renderArea->setMinimumSize(500, 550);
    treeScrollArea->setMinimumSize(20,20);
//    treeScrollArea->setMaximumSize(550, 600);
//    renderArea->setSizeConstraint(QLayout::SetFixedSize);


    // Pass any events that happen on the scroll area to the
    // render area (specifically clicking, so that renderArea
    // can zoom in/out when clicks happen
    treeScrollArea->installEventFilter(renderArea);

    // Create the main layout and add all the widgets to it

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);

//    QPixmap loadpix(":/new/prefix1/Icon/add.png");
//    QPixmap delpix(":/new/prefix1/Icon/delete.png");
//    QPixmap zoominpix(":/new/prefix1/Icon/zoom-in.png");
//    QPixmap zoomoutpix(":/new/prefix1/Icon/zoom-out.png");
//    QToolBar *toolbar = addToolBar("Main Toolbar");
//    QAction *insertAction = new QAction(loadpix,tr("&Insert"), this);
//    connect(insertAction,&QAction::triggered, this, &MainWindow::insertClicked);
//    QAction *deleteAction = new QAction(delpix,tr("&Delete"), this);
//    connect(deleteAction,&QAction::triggered, this, &MainWindow::deleteClicked);
//    QAction *zoominAction = new QAction(zoominpix,tr("Zoom &In"), this);
//    connect(zoominAction,&QAction::triggered, this, &MainWindow::zoomInClicked);
//    QAction *zoomoutAction = new QAction(zoomoutpix,tr("Zoom &Out"), this);
//    connect(zoomoutAction,&QAction::triggered, this, &MainWindow::zoomOutClicked);
//    aboutAction->setIcon(QIcon(":/new/prefix1/Icon/about.png"));
//    toolbar->addAction(insertAction);
//    toolbar->addAction(deleteAction);
//    toolbar->addAction(zoominAction);
//    toolbar->addAction(zoomoutAction);
//    toolbar->addAction(aboutAction);
//    toolbar->addAction(exitAction);
//    toolbar->setIconSize(QSize(50,70));
//    toolbar->setFixedHeight(475);
//    toolbar->setOrientation(l)
    toolbar->addSeparator();
    addToolBar(Qt::LeftToolBarArea, toolbar);

    // Build the main window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumHeight(800);
    this->setMinimumWidth(1300);
    this->setWindowTitle("Binary Search Tree Visualization");
    this->setWindowIcon(QIcon(":/new/prefix1/Icon/title.png"));
    //this->showMaximized();

    // Create secondary windows (but do not display them)
    prop = new BST_Properties_Window();
    about = new BST_About_Window();
    //inser = new insert();
    // must show window before loading settings
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
//    delete inorderButton;
//    delete preorderButton;
//    delete postorderButton;
//    delete leftRorateButton;
//    delete rightRorateButton;
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
    editMenu->addAction(changeNodeColorAction);
    editMenu->addAction(changeBackgroundColorAction);
    editMenu->addAction(changeTextColorAction);

    aboutmenu = this->menuBar()->addMenu(tr("&About"));
    aboutmenu->addAction(aboutAction);
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
//    QString value = deleteValueLineEdit->text();
    QWidget *win = new QMessageBox();
    deleteButton->setWindowIcon(QIcon(":/new/prefix1/Icon/delete.png"));
    QString value = QInputDialog::getText(deleteButton, tr("Delete"),tr("Remove Value:"),QLineEdit::Normal,0);
    int reply = QMessageBox::warning(win,"Remove","Are you sure to delete this Node?",QMessageBox::Yes,QMessageBox::No);
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
    if (reply == QMessageBox::Yes)
    {
        if(!this->bst->deleteItem(value.toInt()))
    //        this->statusLabel->setText("Value is not in tree...");
        {
            QMessageBox::information(win,"Remove","Value is not in tree...",QMessageBox::Yes);
            this->renderArea->InitColor();
        }
        else
    //        this->statusLabel->setText("Value deleted.");
              QMessageBox::information(win,"Remove","Value deleted.",QMessageBox::Yes);
        this->renderArea->repaint(); // repaint to show changes to tree
        this->deleteValueLineEdit->setText(""); // clear text box
    }
    this->renderArea->InitColor();
    return;
}

// Slot for insert button

void MainWindow::insertClicked() const
{
    // Get entire line of text and iterate through the list of
    // values separated by whitespace - inserting all the values
//    QString values = insertValueLineEdit->text();
//    setStyleSheet("MainWindow {background-image:url(:/new/prefix1/Background/background.png)}");
    insertButton->setWindowIcon(QIcon(":/new/prefix1/Icon/add.png"));
    QString values = QInputDialog::getText(insertButton, tr("Insert Node"),tr("Add Value:"),QLineEdit::Normal,0);
    QWidget *win = new QMessageBox();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);
    //=========================
    QString traversal = this->bst->getNode(values.toInt());;
    std::stringstream ss(traversal.toStdString());
    std::string token=" ",token1=" ";
    while (ss >> token)
    {
        bst->searchNotValue(QString::fromStdString(token).toInt());
        this->renderArea->repaint();
        QThread::sleep(2);
    }
    //=========================

    while (iterator.hasNext())
    {
        if(!this->bst->insert(iterator.next().toInt())) // inserts 0 if text isn't an int
//            this->statusLabel->setText("Duplicate valaue...");
           {
            QMessageBox::information(win,"Confirm Value","Duplicate value...",QMessageBox::Ok);
        this->renderArea->InitColor();
        }

//        else
//            this->statusLabel->setText("Value inserted...");
//            QMessageBox::information(win,"Confirm Value","Value inserted...",QMessageBox::Ok);
    }
    this->renderArea->repaint(); // repaint to show changes to tree
    insertValueLineEdit->setText(""); // clear text box
    this->renderArea->InitColor();
    return;
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

