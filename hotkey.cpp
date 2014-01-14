#include "hotkey.h"

Hotkey::Hotkey(int id, QString productname, double price, QWidget *parent) :
    QPushButton(parent)
{
    this->count = 0;
    this->id = id;
    this->productname = productname;
    this->price = price;
}

int Hotkey::getCount()
{
    return this->count;
}

void Hotkey::incCount()
{
    this->count++;
}

void Hotkey::setCount(int c)
{
    this->count = c;
}

int Hotkey::getId()
{
    return this->id;
}

QString Hotkey::getProductname()
{
    return this->productname;
}

double Hotkey::getPrice()
{
    return this->price;
}


