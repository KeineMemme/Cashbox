#ifndef CASHBOXWINDOW_H
#define CASHBOXWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include <QList>
#include "hotkey.h"

class CashboxWindow : public QDialog
{
    Q_OBJECT

public:
    CashboxWindow(QString path, QWidget *parent = 0);
    ~CashboxWindow();
private:
    void read_hotkeys(QString filename);
    void create_awesome_ui();
    void create_hotkey_buttons();
    void create_right_top();
    void create_calc_and_options();
    void find_last_calc_id();
    void print_table();

    //Attributes
    QString cashboxpath;
    QString layoutName;
    QList<Hotkey *> MyHotkeys;
    int last_calc_id;
    double totalPrice;
    //Total-Layouts
    QHBoxLayout *top_Layout;
    QVBoxLayout *total_Layout;
    //Hotkeys-Layout
    QVBoxLayout *hotkey_Layout;
    QList<QHBoxLayout *> HotkeyRows;
    //RightTopSide-Layout
    QVBoxLayout *right_Layout;
    QHBoxLayout *calc_id_Layout;
    QLabel *lbIdText;
    QLabel *lbId;
    QHBoxLayout *product_Layout;
    QTableWidget *product_table;
    QHBoxLayout *totalPrice_Layout;
    QLabel *lbTotalPriceText;
    QLabel *lbTotalPrice;
    QHBoxLayout *paidPrice_Layout;
    QLabel *lbPaidPriceText;
    QLabel *lbPaidPrice;
    QHBoxLayout *moneyBack_Layout;
    QLabel *lbMoneyBackText;
    QLabel *lbMoneyBack;
    //Calculator-Layout
    QHBoxLayout *outputRow;
    QHBoxLayout *numRows[3];
    QHBoxLayout *calcOptionRow;
    QHBoxLayout *zeroRow;
    QVBoxLayout *calcLayout;
    QLineEdit *outputNum;
    QPushButton *num9;
    QPushButton *num8;
    QPushButton *num7;
    QPushButton *num6;
    QPushButton *num5;
    QPushButton *num4;
    QPushButton *num3;
    QPushButton *num2;
    QPushButton *num1;
    QPushButton *num0;
    QPushButton *btPoint;
    QPushButton *btDeleteAll;
    QPushButton *btDeleteLast;
    QPushButton *btCalc;
    QHBoxLayout *total_calcLayout;
        //Payed
        double payed;
        double moneyback;
    //Option-Layout
    QVBoxLayout *option_Layout;
    QLabel *lbOptions;
    QLabel *lbFreeSpace1;
    QPushButton *btRemoveSelectedItem;
    QPushButton *btDone;
public slots:
        void addCountOfHotkey();
        void addToOutput();
        void deleLastFromOutput();
        void deleteOutput();
        void pay();
        void nextCustomer();
        void delete_selected_table_row();

};


#endif // CASHBOXWINDOW_H
