
#include "bst_about_window.h"
#include <QTextEdit>

BST_About_Window::BST_About_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("About BST Visualization");
    window->setFixedSize(QSize(370, 300));

    QVBoxLayout *specifierLayout = new QVBoxLayout();
    specifierLayout->addWidget(new QLabel("Date:"));
    specifierLayout->addWidget(new QLabel("Funding:"));
    specifierLayout->addWidget(new QLabel("Programmer:"
                                          "\n"
                                          "\n"
                                          "\n"));

    labelLayout = new QVBoxLayout;
    labelLayout->addWidget(new QLabel("June 2020"));
    labelLayout->addWidget(new QLabel("Posts and Telecommunications Institute of Technology"));
    labelLayout->addWidget(new QLabel("Le Thi My Phung "
                                      "\nTran Thi Thanh Tam "
                                      "\nNguyen Ngoc Quang "
                                      "\nHuynh My Dung"));

    QVBoxLayout *textAreaLayout = new QVBoxLayout();
    QTextEdit *txtEdit = new QTextEdit("");
    txtEdit->setStyleSheet("background-color: white; color: black;");
    txtEdit->setReadOnly(true);
    textAreaLayout->addWidget(txtEdit);

    containerLayout = new QHBoxLayout;
    containerLayout->addLayout(specifierLayout);
    containerLayout->addLayout(labelLayout);

    QVBoxLayout *vContainerLayout = new QVBoxLayout();
    vContainerLayout->addLayout(containerLayout);
    vContainerLayout->addLayout(textAreaLayout);

    container = new QWidget;
    container->setLayout(vContainerLayout);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(container);
    // mainLayout->addLayout(buttonLayout); // layout for ok/close button

    centralWidget = new QWidget(window);
    centralWidget->setLayout(mainLayout);

    window->setCentralWidget(centralWidget);
}

BST_About_Window::~BST_About_Window()
{
    delete labelLayout;
    delete containerLayout;
    delete container;
    delete mainLayout;
    delete centralWidget;
    delete window;
}

void BST_About_Window::show()
{
    window->setVisible(true);
    window->setWindowIcon(QIcon(":/new/prefix1/Icon/about.png"));
    window->activateWindow();
    return;
}

void BST_About_Window::close()
{
    window->close();
    return;
}
