#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "cashboxlayoutcreatorwindow.h"
#include "cashboxmanagerwindow.h"

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = 0);
    ~MainMenuWindow();

private:
    static const int MAX_WIDTH = 500;
    static const int MAX_HEIGHT = 500;
    QPushButton *btCashboxLayoutCreator;
    QPushButton *btCashboxManager;

    void create_Cashbox_Layout_Creator_Window_Button();
    void create_Cashbox_Manager_Window_Button();

private slots:
    void create_Cashbox_Layout_Creator_Window();
    void create_Cashbox_Manager_Window();
};

#endif // MAINMENUWINDOW_H
