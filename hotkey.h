#ifndef HOTKEY_H
#define HOTKEY_H

#include <QPushButton>
#include <QtWidgets>


class Hotkey : public QPushButton
{
    Q_OBJECT
public:
    explicit Hotkey(int id, QString productname, double price, QWidget *parent = 0);
    int getCount();
    void incCount();
    void setCount(int c);
    int getId();
    QString getProductname();
    double getPrice();
private:
    int count;
    int id;
    QString productname;
    double price;

signals:

public slots:


};
#endif // HOTKEY_H
