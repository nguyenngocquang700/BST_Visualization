#ifndef INSERT_H
#define INSERT_H

#include "binarysearchtree.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class insert : public QMainWindow
{
public:
    insert();
    ~insert();
    void show();
    void close();
//    QString returnValue();
private:
    QMainWindow *window;
    QVBoxLayout *labelLayout;
    QHBoxLayout *containerLayout;
    QWidget *container;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;
    QLineEdit *insertValueLineEdit;
private slots:
    void exitSlot();
};

#endif // INSERT_H
