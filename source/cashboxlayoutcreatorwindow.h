#ifndef CASHBOXLAYOUTCREATORWINDOW_H
#define CASHBOXLAYOUTCREATORWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include "hotkey.h"

#include <QDialog>
#include <QtWidgets>
#include "hotkey.h"

class CashboxLayoutCreatorWindow : public QDialog
{
    Q_OBJECT
public:
    explicit CashboxLayoutCreatorWindow(QWidget *parent = 0);
    ~CashboxLayoutCreatorWindow();
    void create_awesome_ui();

private:
    QVBoxLayout *Hotkey_Conf_Layout;
    QLabel *Output_HotkeyConfiguration;
    QListWidget *List_Hotkeys;
    QHBoxLayout *Hotkey_Name_Layout;
    QLabel *Output_Hotkeyname;
    QLineEdit *Input_Hotkeyname;
    QHBoxLayout *Hotkey_Price_Layout;
    QLabel *Output_HotkeyPrice;
    QLineEdit *Input_HotkeyPrice;
    QHBoxLayout *Buttons_Layout;
    QPushButton *btOk;
    QPushButton *btDelete;
    QVBoxLayout *List_Layout;
    QLabel *Output_Layout_Overview;
    QListWidget *List_Layouts;
    QPushButton *btDeleteLayout;
    QHBoxLayout *saveLayout;
    QLabel *Output_Save_Layout;
    QLineEdit *Input_Layoutname;
    QPushButton *btSaveLayout;
    QVBoxLayout *totalLayout;
    //Variables
    QList<Hotkey*> MyHotkeys;
    QList<QString> Layouts;
    int id;
    int numHotkeys;
signals:

public slots:
    //After click on btOk, add to QList<Hotkey>MyHotkeys;
    void add_ToMyHotkeys_And_ListHotkeys();
    void delete_Hotkey();
    void save_Layout();
    void delete_Layout();

};
#endif // CASHBOXLAYOUTCREATORWINDOW_H
