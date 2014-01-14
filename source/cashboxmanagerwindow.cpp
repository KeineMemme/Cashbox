#include "cashboxmanagerwindow.h"

CashBoxManagerWindow::CashBoxManagerWindow(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Cashbox Application - Cashboxmanager");
    //Leftside
    leftLayout = new QVBoxLayout();
    outputCREATECASHBOX = new QLabel("<b>Create Cashbox</b>");
    outputCASHBOXNAME = new QLabel("Cashbox-Name:");
    inputCashboxName = new QLineEdit();
    outputWhatLayout = new QLabel("Layout");
    listCashboxLayouts = new QListWidget();
    btCreateCashbox = new QPushButton("Create Cashbox");
    //Rightside
    rightLayout = new QVBoxLayout();
    outputLOADCASHBOX = new QLabel("<b>Load Cashbox</b>");
    freeSpace = new QLabel("");
    listCashboxs = new QListWidget();
    rightControlLayout = new QHBoxLayout();
    btLoadCashbox = new QPushButton("Load Cashbox");
    btDeleteCashbox = new QPushButton("Delete Cashbox");
    //TotalLayout
    totalLayout = new QHBoxLayout();
    create_ui();
    //Load Layouts in listCashboxLayouts
    QDir DirLayout("Layout/");
    QStringList filesList = DirLayout.entryList(QDir::Files);
    for(int i = 0; i < filesList.count();i++) {
        listCashboxLayouts->addItem(filesList.at(i));

    }

    DirLayout.setPath("Cashboxes");
    QStringList dirList = DirLayout.entryList(QDir::Dirs);
    for(int i = 0; i < dirList.count();i++) {
        if(dirList.at(i)!="."&&dirList.at(i)!="..") {
            listCashboxs->addItem(dirList.at(i));
        }
    }
    DirLayout.~QDir();
}

CashBoxManagerWindow::~CashBoxManagerWindow()
{

}

void CashBoxManagerWindow::create_ui()
{
    //Leftside
    leftLayout->addWidget(outputCREATECASHBOX);
    leftLayout->addWidget(outputCASHBOXNAME);
    leftLayout->addWidget(inputCashboxName);
    leftLayout->addWidget(outputWhatLayout);
    leftLayout->addWidget(listCashboxLayouts);
    leftLayout->addWidget(btCreateCashbox);
    connect(btCreateCashbox,SIGNAL(clicked()),SLOT(create_cashbox()));
    //Rightside
    rightControlLayout->addWidget(btDeleteCashbox); //TODO: SIGNAL SLOT
    connect(btDeleteCashbox,SIGNAL(clicked()),SLOT(delete_cashbox()));
    rightControlLayout->addWidget(btLoadCashbox);
    connect(btLoadCashbox,SIGNAL(clicked()),SLOT(load_cashbox()));
    rightLayout->addWidget(outputLOADCASHBOX);
    rightLayout->addWidget(freeSpace);
    rightLayout->addWidget(listCashboxs);
    rightLayout->addLayout(rightControlLayout);
    //Totalside
    totalLayout->addLayout(leftLayout);
    totalLayout->addLayout(rightLayout);
    setLayout(totalLayout);
}

void CashBoxManagerWindow::create_cashbox()
{
    if(listCashboxLayouts->currentItem()!=NULL) {
        //Create Folder "CASHBOXNAME"
        QDir cashboxFolder;
        if(!QDir(inputCashboxName->text()).exists()) {
            cashboxFolder.mkdir("Cashboxes/");
            cashboxFolder.mkdir("Cashboxes/"+inputCashboxName->text());
            //Save Layout in CASHBOXNAME/LAYOUTNAME
            QFile::copy("Layout/"+listCashboxLayouts->currentItem()->text(),"Cashboxes/"+inputCashboxName->text()+"/"+listCashboxLayouts->currentItem()->text());
            //Create File in CASHBOXNAME/bilance.csv
            QFile file2("Cashboxes/"+inputCashboxName->text()+"/bilance.csv");
            file2.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream out(&file2);
            out << "";
            file2.close();
            //Add Casbox to listCashboxs
            listCashboxs->addItem(inputCashboxName->text());
        }
        else {
            //When already exist..
            QMessageBox::information(this,"Error","Cashbox already exists");

        }
    }
    else {
        QMessageBox::information(this,"Error","Please select Layout");
    }
}

void CashBoxManagerWindow::load_cashbox()
{
    if(listCashboxs->currentItem()!=NULL) {
        //TODO: Load with CASHBOXNAME/LAYOUTNAME and CASHBOXNAME/bilance.csv a new Cashbox
        CashboxWindow Cashbox("Cashboxes/"+listCashboxs->currentItem()->text()+"/");
        Cashbox.exec();
    }
}

void CashBoxManagerWindow::delete_cashbox()
{
    if(listCashboxs->currentItem()!=NULL) {
        //Remove Cashbox-Directory
        QDir cashboxFolder("Cashboxes/"+listCashboxs->currentItem()->text());
        cashboxFolder.removeRecursively();
        //Clean listCashboxs
        QListWidgetItem *lI = listCashboxs->currentItem();
        lI->~QListWidgetItem();
    }
}
