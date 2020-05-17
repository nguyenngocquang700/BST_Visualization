#include "insert.h"
#include <QTextEdit>
#include "mainwindow.h"
#include <QLineEdit>
insert::insert()
{
    window = new QMainWindow();
    window->setWindowTitle("Input:");
    window->setFixedSize(QSize(370, 300));

    QVBoxLayout *Layout = new QVBoxLayout();
    Layout->addWidget(new QLabel("Add value:"));
    Layout->addWidget(insertValueLineEdit);

    insertValueLineEdit = new QLineEdit;
    insertValueLineEdit->setFixedWidth(200);
    insertValueLineEdit->setToolTip("Enter single value or multiple values separated by space");
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(returnValue()));

    centralWidget = new QWidget(window);
    centralWidget->setLayout(Layout);
    window->setCentralWidget(centralWidget);
}

insert::~insert()
{
    delete labelLayout;
    delete containerLayout;
    delete container;
    delete mainLayout;
    delete centralWidget;
    delete window;
}

void insert::show()
{
    window->setVisible(true);
    window->setWindowIcon(QIcon(":/new/prefix1/Icon/about.png"));
    window->activateWindow();
    return;
}

void insert::close()
{
    window->close();
    return;
}
QString insert::returnValue()
{
    return insertValueLineEdit->text();
}
