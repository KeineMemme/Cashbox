#include"cashboxlayoutcreatorwindow.h"
CashboxLayoutCreatorWindow::CashboxLayoutCreatorWindow(QWidget *parent) :
    QDialog(parent)
{
    this->numHotkeys = 0;   //Count Hotkeys in Layout
    this->setWindowTitle("Cashbox Application - Cashbox Layout Creator");
    id = 0;
    create_awesome_ui();
    //Load Layouts..
    //Load Layouts
    QDir DirLayout;
    if(!QDir("Layout/").exists()) {
        DirLayout.mkdir("Layout/");
    }
    DirLayout.setPath("Layout/");
    QStringList filesList = DirLayout.entryList(QDir::Files);
    for(int i = 0; i < filesList.count();i++) {
        List_Layouts->addItem(filesList.at(i));
        Layouts.append(filesList.at(i));
    }

}

CashboxLayoutCreatorWindow::~CashboxLayoutCreatorWindow() {


}

void CashboxLayoutCreatorWindow::create_awesome_ui()
{
    //TopLayout
    QHBoxLayout *topLayout;
    topLayout = new QHBoxLayout();
    //Hotkey_Configuration_Layout
    Hotkey_Conf_Layout = new QVBoxLayout();
    Output_HotkeyConfiguration = new QLabel("<b>Hotkey-Configuration</b>");
    Hotkey_Conf_Layout->addWidget(Output_HotkeyConfiguration);
    List_Hotkeys = new QListWidget();
    Hotkey_Conf_Layout->addWidget(List_Hotkeys);
    Hotkey_Name_Layout = new QHBoxLayout();
    Output_Hotkeyname = new QLabel("Hotkey-Name:");
    Hotkey_Name_Layout->addWidget(Output_Hotkeyname);
    Input_Hotkeyname = new QLineEdit();
    Hotkey_Name_Layout->addWidget(Input_Hotkeyname);
    Hotkey_Conf_Layout->addLayout(Hotkey_Name_Layout);
    Hotkey_Price_Layout = new QHBoxLayout();
    Output_HotkeyPrice = new QLabel("Hotkey-Price(€)");
    Hotkey_Price_Layout->addWidget(Output_HotkeyPrice);
    Input_HotkeyPrice = new QLineEdit();
    Hotkey_Price_Layout->addWidget(Input_HotkeyPrice);
    Hotkey_Conf_Layout->addLayout(Hotkey_Price_Layout);
    Buttons_Layout = new QHBoxLayout();
    btOk = new QPushButton("OK");
    connect(btOk,SIGNAL(clicked()),SLOT(add_ToMyHotkeys_And_ListHotkeys()));
    Buttons_Layout->addWidget(btOk);
    btDelete = new QPushButton("Remove Hotkey");
    connect(btDelete,SIGNAL(clicked()),SLOT(delete_Hotkey()));
    Buttons_Layout->addWidget(btDelete);
    Hotkey_Conf_Layout->addLayout(Buttons_Layout);
    topLayout->addLayout(Hotkey_Conf_Layout);
    //Rightside.. ListLayout
    List_Layout = new QVBoxLayout();
    Output_Layout_Overview = new QLabel("<b>Layout-Overview:</b>");
    List_Layout->addWidget(Output_Layout_Overview);
    List_Layouts = new QListWidget();
    List_Layout->addWidget(List_Layouts);
    btDeleteLayout = new QPushButton("Delete Layout");
    List_Layout->addWidget(btDeleteLayout);
    connect(btDeleteLayout,SIGNAL(clicked()),SLOT(delete_Layout()));
    topLayout->addLayout(List_Layout);
    //Bottom.. SaveLayout
    saveLayout = new QHBoxLayout();
    Output_Save_Layout = new QLabel("Layoutname:");
    saveLayout->addWidget(Output_Save_Layout);
    Input_Layoutname = new QLineEdit();
    saveLayout->addWidget(Input_Layoutname);
    btSaveLayout = new QPushButton("Save Layout");
    connect(btSaveLayout,SIGNAL(clicked()),SLOT(save_Layout()));
    saveLayout->addWidget(btSaveLayout);
    totalLayout = new QVBoxLayout();
    totalLayout->addLayout(topLayout);
    totalLayout->addLayout(saveLayout);

    this->setLayout(totalLayout);
}

void CashboxLayoutCreatorWindow::add_ToMyHotkeys_And_ListHotkeys()
{
    bool okNumber = true;
    QString item_str;
    //TODO: Check for fail Inputs..
    if(this->numHotkeys < 10) {
        Input_HotkeyPrice->text().toDouble(&okNumber);
        if(okNumber) {
            if(this->id,Input_Hotkeyname->text()!=""&&Input_HotkeyPrice->text()!="") {
                MyHotkeys.append(new Hotkey(this->id,Input_Hotkeyname->text(),Input_HotkeyPrice->text().toDouble()));
                item_str = Input_Hotkeyname->text() + ":" + Input_HotkeyPrice->text()+"€";
                List_Hotkeys->addItem(item_str);
                id++;
                this->numHotkeys++;
            }
            else {
                QMessageBox::information(this,"ERROR","Input Error..");
            }
        }
        else {
            QMessageBox::information(this,"ERROR","Pls a number for Price..");
        }
    }
    else {
        QMessageBox::information(this,"ERROR","Maximal 10 Hotkeys..");
    }
}

void CashboxLayoutCreatorWindow::delete_Hotkey()
{
    if(List_Hotkeys->currentItem()!=NULL) {
        QListWidgetItem *lI = List_Hotkeys->currentItem();
        lI->~QListWidgetItem();
        MyHotkeys.removeAt(List_Hotkeys->currentRow());
        this->numHotkeys--;
    }
    else {
        QMessageBox::information(this,"ERROR","Please select Hotkey");
    }
}

void CashboxLayoutCreatorWindow::save_Layout()
{
    bool checkLayout = true;
    for(int i = 0; i < Layouts.count(); i++) {
        if(QString::compare(Layouts.at(i),Input_Layoutname->text())==0) {
            checkLayout = false;
        }
    }
    if(checkLayout) {
        //Append Item Layoutname to List_Layouts
        List_Layouts->addItem(Input_Layoutname->text());
        //Save Hotkeys in .csv Datei
           QFile layoutFile("Layout/"+Input_Layoutname->text());
           layoutFile.open(QIODevice::WriteOnly);
           QTextStream out(&layoutFile);
           for(int i = 0; i < MyHotkeys.count(); i++) {
               out << QString::number(MyHotkeys.at(i)->getId())<< "," << MyHotkeys.at(i)->getProductname() << "," << MyHotkeys.at(i)->getPrice()<<";\n";
           }
           layoutFile.close();
           //Add to Layouts
           Layouts.append(Input_Layoutname->text());
           this->numHotkeys = 0;
    }
    else {
        QMessageBox::information(this,"ERROR","Layout already exists");
    }

}

void CashboxLayoutCreatorWindow::delete_Layout()
{
    //Delete List_Layouts->currentItem()
    if(List_Layouts->currentItem()!=NULL) {
        //Remove string from Layouts:
        for(int i = 0; i < Layouts.count(); i++) {
            if(QString::compare(Layouts.at(i),List_Layouts->currentItem()->text())==0) {
                Layouts.removeAt(i);
            }
        }
        //Delete File
        QFile file("Layout/"+List_Layouts->currentItem()->text());
        file.remove();
        //Clean ListWidget
        QListWidgetItem *lI = List_Layouts->currentItem();
        lI->~QListWidgetItem();
    }
    else {
        QMessageBox::information(this,"ERROR","Please select Layout");
    }

}

