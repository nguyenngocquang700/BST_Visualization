
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinarySearchTree
TEMPLATE = app


SOURCES += main.cpp\
    bst_inorder_window.cpp \
    mainwindow.cpp \
    renderarea.cpp \
    bst_properties_window.cpp \
    bst_about_window.cpp

HEADERS  += mainwindow.h \
    binarysearchtree.h \
    bst_inorder_window.h \
    renderarea.h \
    bst_properties_window.h \
    bst_about_window.h

FORMS    +=

RESOURCES += \
    Image.qrc
