#include "cashboxwindow.h"

CashboxWindow::CashboxWindow(QString path, QWidget *parent)
    : QDialog(parent)
{

    this->setWindowTitle("Cashbox Application - Your Cashbox");
    this->totalPrice = 0;
    this->cashboxpath = path;
    QDir DirLayout(this->cashboxpath);
    QStringList filesList = DirLayout.entryList(QDir::Files);
    for(int i = 0; i < filesList.count();i++) {
        if(filesList.at(i)!="."&&filesList.at(i)!=".."&&!filesList.at(i).contains(".csv")){
            //Save LayoutName
            //QMessageBox::information(this,"",filesList.at(i));
            this->layoutName = filesList.at(i);
        }
    }
    //Read Hotkeys-Methode and save them in MyHotkeys-Liste
    read_hotkeys(this->cashboxpath+""+this->layoutName);
    //Find last calc id
    find_last_calc_id();
    //Create UI
    create_awesome_ui();
        //Create Hotkey-Buttons
        //Create Rightside-Top
        //Create Rightside-Calc + Options

}

CashboxWindow::~CashboxWindow()
{

}

void CashboxWindow::read_hotkeys(QString filename)
{
    int pos =0;
    QFile f(filename);
    //Read Hotkeys and add them to your Hotkey-QList
    f.open(QIODevice::ReadOnly);
    QTextStream in(&f);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        QString fieldstr = fields.at(2);
        fieldstr.replace(QString(";"), QString(" "));
        fieldstr.trimmed();
        //QMessageBox::information(this,"",QString::number(pos)+":"+fields.at(1)+":"+fieldstr);
        MyHotkeys.append(new Hotkey(pos,fields.at(1),fieldstr.toDouble()));
        //QMessageBox::information(this,"",QString::number(pos)+":"+fields.at(1)+":"+QString::number(MyHotkeys.at(MyHotkeys.size()-1)->getPrice()));
    }

    f.close();
}

void CashboxWindow::create_awesome_ui()
{
    total_Layout = new QVBoxLayout();
    top_Layout = new QHBoxLayout();
    create_hotkey_buttons();
    create_right_top();
    create_calc_and_options();
    this->setLayout(total_Layout);
}

void CashboxWindow::create_hotkey_buttons()
{
    hotkey_Layout = new QVBoxLayout();
    HotkeyRows.append(new QHBoxLayout());
    for(int i = 0; i < MyHotkeys.count(); i++) {
        MyHotkeys.at(i)->setText(MyHotkeys.at(i)->getProductname()+"("+QString::number(MyHotkeys.at(i)->getPrice())+"€)");
        connect(MyHotkeys.at(i),SIGNAL(clicked()),SLOT(addCountOfHotkey()));
        HotkeyRows.at(HotkeyRows.count()-1)->addWidget(MyHotkeys.at(i));

        if(i % 3 == 0 && i != 0 || i+1 == MyHotkeys.count()) {
            hotkey_Layout->addLayout(HotkeyRows.at(HotkeyRows.count()-1));
            if(i+1 != MyHotkeys.count()) {
                HotkeyRows.append(new QHBoxLayout());
            }
        }
    }
    /*hotkey_Layout = new QVBoxLayout();
    HotkeyRows.append(new QHBoxLayout());
    for(int i = 0; i < MyHotkeys.count(); i++) {
        //Add new Hotkey
        MyHotkeys.at(i)->setText(MyHotkeys.at(i)->getProductname()+"("+QString::number(MyHotkeys.at(i)->getPrice())+"€)");
        HotkeyRows.at(HotkeyRows.count()-1)->addWidget(MyHotkeys.at(i));
        //If only 1
        if(MyHotkeys.count() == 1) {
            hotkey_Layout->addLayout(HotkeyRows.at(HotkeyRows.count()-1));
        }
        connect(MyHotkeys.at(i),SIGNAL(clicked()),SLOT(addCountOfHotkey()));
        //Check at last round
        if(i % 4 != 0 && i == MyHotkeys.count()-1) {
            //Fuck off.. add last layout
            hotkey_Layout->addLayout(HotkeyRows.at(HotkeyRows.count()-1));
        }
        if(i % 4) {
            //Save Row
            if(i > 0){
                //Add old Row to layout
                hotkey_Layout->addLayout(HotkeyRows.at(HotkeyRows.count()-1));
                //New Row
                HotkeyRows.append(new QHBoxLayout());
            }
            if(i != MyHotkeys.count()-1) {
                //New Row
                HotkeyRows.append(new QHBoxLayout());
            }
        }
    }*/

    top_Layout->addLayout(hotkey_Layout);


}

void CashboxWindow::create_right_top()
{
    right_Layout = new QVBoxLayout();
    //Calc Informationid
    calc_id_Layout = new QHBoxLayout();
    lbIdText = new QLabel("<b>Calculation ID:</b>");
    lbId = new QLabel(QString::number(last_calc_id));
    calc_id_Layout->addWidget(lbIdText);
    calc_id_Layout->addWidget(lbId);
    //Product-Table
    product_Layout = new QHBoxLayout();
    product_table = new QTableWidget(MyHotkeys.count(),4);
    product_table->setColumnCount(4);
    QTableWidgetItem *amountItem = new QTableWidgetItem("Amount");
    product_table->setHorizontalHeaderItem(0,amountItem);
    QTableWidgetItem *productnameItem = new QTableWidgetItem("Productname");
    product_table->setHorizontalHeaderItem(1,productnameItem);
    QTableWidgetItem *singlePriceItem = new QTableWidgetItem("Single Price");
    product_table->setHorizontalHeaderItem(2,singlePriceItem);
    QTableWidgetItem *totalPriceItem = new QTableWidgetItem("Total Price");
    product_table->setHorizontalHeaderItem(3,totalPriceItem);
    product_table->setFixedSize(441,10*32.5);
    product_Layout->addWidget(product_table);
    //Total Price
    totalPrice_Layout = new QHBoxLayout();
    lbTotalPriceText = new QLabel("<b>Total Price:</b>");
    lbTotalPrice = new QLabel("0€");
    totalPrice_Layout->addWidget(lbTotalPriceText);
    totalPrice_Layout->addWidget(lbTotalPrice);
    //Paid Sum
    paidPrice_Layout = new QHBoxLayout();
    lbPaidPriceText = new QLabel("<b>Paid:</b>");
    lbPaidPrice = new QLabel("0€");
    paidPrice_Layout->addWidget(lbPaidPriceText);
    paidPrice_Layout->addWidget(lbPaidPrice);
    //Money back
    moneyBack_Layout = new QHBoxLayout();
    lbMoneyBackText = new QLabel("<b>Money back:</b>");
    lbMoneyBack = new QLabel("0€");
    moneyBack_Layout->addWidget(lbMoneyBackText);
    moneyBack_Layout->addWidget(lbMoneyBack);
    //Add Layouts
    right_Layout->addLayout(calc_id_Layout);
    right_Layout->addLayout(product_Layout);
    right_Layout->addLayout(totalPrice_Layout);
    right_Layout->addLayout(paidPrice_Layout);
    right_Layout->addLayout(moneyBack_Layout);

    top_Layout->addLayout(right_Layout);
}

void CashboxWindow::create_calc_and_options()
{
    outputRow = new QHBoxLayout();
    calcOptionRow = new QHBoxLayout();
    zeroRow = new QHBoxLayout();
    calcLayout = new QVBoxLayout();
    outputNum = new QLineEdit("");
    outputNum->setEnabled(false);
    outputRow->addWidget(outputNum);
    numRows[2] = new QHBoxLayout();
    num7 = new QPushButton("7");
    numRows[2]->addWidget(num7);
    connect(num7,SIGNAL(clicked()),SLOT(addToOutput()));
    num8 = new QPushButton("8");
    numRows[2]->addWidget(num8);
    connect(num8,SIGNAL(clicked()),SLOT(addToOutput()));
    num9 = new QPushButton("9");
    numRows[2]->addWidget(num9);
    connect(num9,SIGNAL(clicked()),SLOT(addToOutput()));
    numRows[1] = new QHBoxLayout();
    num4 = new QPushButton("4");
    numRows[1]->addWidget(num4);
    connect(num4,SIGNAL(clicked()),SLOT(addToOutput()));
    num5 = new QPushButton("5");
    numRows[1]->addWidget(num5);
    connect(num5,SIGNAL(clicked()),SLOT(addToOutput()));
    num6 = new QPushButton("6");
    numRows[1]->addWidget(num6);
    connect(num6,SIGNAL(clicked()),SLOT(addToOutput()));
    numRows[0] = new QHBoxLayout();
    num1 = new QPushButton("1");
    numRows[0]->addWidget(num1);
    connect(num1,SIGNAL(clicked()),SLOT(addToOutput()));
    num2 = new QPushButton("2");
    numRows[0]->addWidget(num2);
    connect(num2,SIGNAL(clicked()),SLOT(addToOutput()));
    num3 = new QPushButton("3");
    numRows[0]->addWidget(num3);
    connect(num3,SIGNAL(clicked()),SLOT(addToOutput()));
    num0 = new QPushButton("0");
    zeroRow->addWidget(num0);
    connect(num0,SIGNAL(clicked()),SLOT(addToOutput()));
    btPoint = new QPushButton(".");
    calcOptionRow->addWidget(btPoint);
    connect(btPoint,SIGNAL(clicked()),SLOT(addToOutput()));
    btDeleteAll = new QPushButton("(X)");
    calcOptionRow->addWidget(btDeleteAll);
    connect(btDeleteAll,SIGNAL(clicked()),SLOT(deleteOutput()));
    btDeleteLast = new QPushButton("<-");
    calcOptionRow->addWidget(btDeleteLast);
    connect(btDeleteLast,SIGNAL(clicked()),SLOT(deleLastFromOutput()));
    btCalc = new QPushButton("CALC");
    calcOptionRow->addWidget(btCalc);
    connect(btCalc,SIGNAL(clicked()),SLOT(pay()));

    //Add all Layouts to one Calc-Layout
    calcLayout->addLayout(outputRow);
    calcLayout->addLayout(numRows[2]);
    calcLayout->addLayout(numRows[1]);
    calcLayout->addLayout(numRows[0]);
    calcLayout->addLayout(zeroRow);
    calcLayout->addLayout(calcOptionRow);
    option_Layout = new QVBoxLayout();
    lbOptions = new QLabel("<b>Options:</b>");
    lbFreeSpace1 = new QLabel("");
    btRemoveSelectedItem = new QPushButton("Remove Selected Item");
    connect(btRemoveSelectedItem, SIGNAL(clicked()),SLOT(delete_selected_table_row()));
    btDone = new QPushButton("NEXT CUSTOMER");
    connect(btDone,SIGNAL(clicked()),SLOT(nextCustomer()));
    option_Layout->addWidget(lbOptions);
    option_Layout->addWidget(btRemoveSelectedItem);
    option_Layout->addWidget(btDone);
    option_Layout->addWidget(lbFreeSpace1);
    option_Layout->addWidget(lbFreeSpace1);
    total_calcLayout = new QHBoxLayout();
    total_calcLayout->addLayout(calcLayout);
    total_calcLayout->addLayout(option_Layout);
    total_Layout->addLayout(top_Layout);
    total_Layout->addLayout(total_calcLayout);
}

void CashboxWindow::find_last_calc_id()
{
    QFile f(this->cashboxpath+"bilance.csv");
    //Read Hotkeys and add them to your Hotkey-QList
    f.open(QIODevice::ReadOnly);
    QTextStream in(&f);
    if(in.atEnd()) {
        this->last_calc_id = 1;
    }

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        QString fieldstr = fields.at(2);
        fieldstr.replace(QString(";"), QString(" "));
        fieldstr.trimmed();
        this->last_calc_id = fields.at(0).toInt()+1;
        //QMessageBox::information(this,"",fields.at(0));
    }


    f.close();

}

void CashboxWindow::print_table()
{
    //Clear Table
    this->product_table->clear();
    //Old Structur pls
    QTableWidgetItem *amountItem = new QTableWidgetItem("Amount");
    product_table->setHorizontalHeaderItem(0,amountItem);
    QTableWidgetItem *productnameItem = new QTableWidgetItem("Productname");
    product_table->setHorizontalHeaderItem(1,productnameItem);
    QTableWidgetItem *singlePriceItem = new QTableWidgetItem("Single Price");
    product_table->setHorizontalHeaderItem(2,singlePriceItem);
    QTableWidgetItem *totalPriceItem = new QTableWidgetItem("Total Price");
    product_table->setHorizontalHeaderItem(3,totalPriceItem);

    this->totalPrice = 0;
    for(int i = 0, pos = 0; i < MyHotkeys.count(); i++) {
        if(MyHotkeys.at(i)->getCount()>0) {
            //Write this Hotkey in Table..
            product_table->setItem(pos,0, new QTableWidgetItem(QString::number(MyHotkeys.at(i)->getCount())));
            product_table->setItem(pos,1,new QTableWidgetItem(MyHotkeys.at(i)->getProductname()));
            product_table->setItem(pos,2,new QTableWidgetItem(QString::number(MyHotkeys.at(i)->getPrice())));
            product_table->setItem(pos,3,new QTableWidgetItem(QString::number(MyHotkeys.at(i)->getPrice()*MyHotkeys.at(i)->getCount())));
            totalPrice+=MyHotkeys.at(i)->getPrice()*MyHotkeys.at(i)->getCount();
            this->lbTotalPrice->setText(QString::number(totalPrice)+"€");
            pos++;
        }
    }

}

void CashboxWindow::addCountOfHotkey()
{
    Hotkey *clickedButton = qobject_cast<Hotkey*>(sender());
    clickedButton->incCount();
    print_table();
}

void CashboxWindow::addToOutput()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    outputNum->setText(outputNum->text()+clickedButton->text());
}

void CashboxWindow::deleLastFromOutput()
{
    //Remove last Value from Output
    QString output = outputNum->text();
    output.remove(output.length()-1,1);
    outputNum->setText(output);
}

void CashboxWindow::deleteOutput()
{
    //Clear Output
    outputNum->setText("");
}

void CashboxWindow::pay()
{
    this->payed = outputNum->text().toDouble();
    this->lbPaidPrice->setText(QString::number(this->payed)+"€");
    this->moneyback = this->payed - this->totalPrice;
    this->lbMoneyBack->setText(QString::number(moneyback)+"€");
}

void CashboxWindow::nextCustomer()
{
    //Save Calculation in bilance.csv
    QFile billFile(this->cashboxpath+"bilance.csv");
    billFile.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out(&billFile);
    for(int i = 0; i < MyHotkeys.count(); i++) {
        if(MyHotkeys.at(i)->getCount()>0) {
        //Gehe die einzelnen Hotkeys durch(so wie table-Darstellung und schreibe es anstatt in eine Table in eine Zeile
        out << QString::number(this->last_calc_id) << "," << MyHotkeys.at(i)->getProductname()<< "," << QString::number(MyHotkeys.at(i)->getCount()) << ","<< MyHotkeys.at(i)->getPrice()<<","<<QString::number(MyHotkeys.at(i)->getPrice()*MyHotkeys.at(i)->getCount())<<";\n";
        //Setze Hotkeys-Counts auf 0
        MyHotkeys.at(i)->setCount(0);
        }
    }
    billFile.close();
    //Clear Table
    this->product_table->clear();
    //Old Structur pls
    QTableWidgetItem *amountItem = new QTableWidgetItem("Amount");
    product_table->setHorizontalHeaderItem(0,amountItem);
    QTableWidgetItem *productnameItem = new QTableWidgetItem("Productname");
    product_table->setHorizontalHeaderItem(1,productnameItem);
    QTableWidgetItem *singlePriceItem = new QTableWidgetItem("Single Price");
    product_table->setHorizontalHeaderItem(2,singlePriceItem);
    QTableWidgetItem *totalPriceItem = new QTableWidgetItem("Total Price");
    product_table->setHorizontalHeaderItem(3,totalPriceItem);
    //Delete Calculator
    this->outputNum->setText("");
    //Delete Outputs
    this->totalPrice = 0;
    this->lbTotalPrice->setText(QString::number(this->totalPrice)+"€");
    this->moneyback = 0;
    this->lbMoneyBack->setText(QString::number( this->moneyback)+"€");
    this->payed = 0;
    this->lbPaidPrice->setText(QString::number(this->payed)+"€");
    //Incremente
    this->last_calc_id++;
    this->lbId->setText(QString::number(this->last_calc_id));


}

void CashboxWindow::delete_selected_table_row()
{
    int rowNum;
    QString hotkeyName;
    QList<QTableWidgetItem*> row = this->product_table->selectedItems();
    if(row.count()==4) {
    for(int i = 0; i < row.count();i++) {
        //Only delete rows..
        if(i == 0) {
            rowNum = row.at(i)->row();
            hotkeyName = row.at(1)->text();
        }
        if(rowNum == row.at(i)->row()) {
            row.at(i)->~QTableWidgetItem();
        }
        if(i == 3) {
            this->totalPrice -= row.at(i)->text().toDouble();
            this->lbTotalPrice->setText(QString::number(this->totalPrice)+"€");
        }
    }
    }
    //Set Hotkey-Count = 0
    for(int i = 0; i < MyHotkeys.count(); i++) {
        //Set count 0
        if(MyHotkeys.at(i)->getProductname()==hotkeyName) {
            MyHotkeys.at(i)->setCount(0);
        }
    }
    print_table();


}


