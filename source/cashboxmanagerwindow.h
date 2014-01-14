#ifndef CASHBOXMANAGERWINDOW_H
#define CASHBOXMANAGERWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include "cashboxwindow.h"

/*
 * Creates Cashboxes with Layouts
 */

class CashBoxManagerWindow : public QDialog
{
    Q_OBJECT
public:
    explicit CashBoxManagerWindow(QWidget *parent = 0);
    ~CashBoxManagerWindow();
private:
    //Leftside
    QVBoxLayout *leftLayout;
    QLabel *outputCREATECASHBOX;
    QLabel *outputCASHBOXNAME;
    QLineEdit *inputCashboxName;
    QLabel *outputWhatLayout;
    QListWidget *listCashboxLayouts;
    QPushButton *btCreateCashbox;
    //Rightside
    QVBoxLayout *rightLayout;
    QLabel *outputLOADCASHBOX;
    QLabel *freeSpace;
    QListWidget *listCashboxs;
    QHBoxLayout *rightControlLayout;
    QPushButton *btLoadCashbox;
    QPushButton *btDeleteCashbox;
    //TotalLayout
    QHBoxLayout *totalLayout;
    //Methods
    void create_ui();

private slots:
    void create_cashbox();
    void load_cashbox();
    void delete_cashbox();
};

#endif // CASHBOXMANAGERWINDOW_H
