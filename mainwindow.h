
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include "renderarea.h"
#include <QInputDialog>
#include <QToolBar>
/*
 * bst_properties_window.h includes:
 * QMainWindow, QVBoxLayout, QHBoxLayout, QScrollArea, QWidget, QLabel, QLineEdit
 */
#include "bst_inorder_window.h"
#include "bst_postorder_window.h"
#include "bst_preorder_window.h"
#include "bst_properties_window.h"
#include "bst_about_window.h"
#include "binarysearchtree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    RenderArea *renderArea;
    QPushButton *propertyButton;
    QPushButton *deleteButton;
    QPushButton *insertButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *NLRButton;
    QPushButton *LNRButton;
    QPushButton *LRNButton;

    QLineEdit *insertValueLineEdit;
    QLineEdit *deleteValueLineEdit;
    QScrollArea *treeScrollArea;
    QVBoxLayout *mainLayout;
    QLabel *statusLabel;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *aboutmenu;
    QMenu *runMenu;
    QAction *aboutAction;
    QAction *loadAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *resetAction;
    QAction *insertAction;
    QAction *deleteAction;
    QAction *zoominAction;
    QAction *zoomoutAction;
    QAction *changeNodeColorAction;
    QAction *changeBackgroundColorAction;
    QAction *changeTextColorAction;
    BST_Properties_Window *prop;
    BST_About_Window *about;
    Bst_inorder_window *inorder;
    Bst_preorder_window *preorder;
    Bst_postorder_window *postorder;
    BinarySearchTree<int> *bst;
    BinarySearchTree<int> *getBST();
    void loadSettings();
    void saveSettings();
    void createMenu();
    void createToolbar();
    void createActions();
    QPushButton *searchButton;
    QPushButton *searchMinButton;
    QPushButton *searchMaxButton;
    QPushButton *inorderButton;
    QPushButton *preorderButton;
    QPushButton *postorderButton;
    QPushButton *leftRorateButton;
    QPushButton *rightRorateButton;
    QLineEdit *searchValueLineEdit;
    QLineEdit *searchMinLineEdit;
    QLineEdit *searchMaxLineEdit;

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void propertyClicked() const;
    void insertClicked() const;
    void deleteClicked() const;
    void zoomInClicked() const;
    void zoomOutClicked() const;
    void loadFileMenu();
    void saveMenu();
    void exitMenu();
    void resetMenu() const;
    void aboutMenu() const;
    void changeNodeColorMenu();
    void changeBackgroundColorMenu();
    void changeTextColorMenu();
    void bst_inorder();
    void bst_preorder();
    void bst_postorder();
    void searchClicked() const;
    void searchMinClicked() const;
    void searchMaxClicked() const;
    void leftRorateClicked() const;
    void rightRorateClicked() const;
    void slotCustomMenuRequested(QPoint pos);

};

#endif // MAINWINDOW_H
