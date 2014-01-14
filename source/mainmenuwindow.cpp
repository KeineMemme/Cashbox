#include "mainmenuwindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Cashbox Application - Main Menu");
    this->setFixedSize(MAX_WIDTH, MAX_HEIGHT);   //Fixed Size pls
    create_Cashbox_Layout_Creator_Window_Button();
    create_Cashbox_Manager_Window_Button();
}

MainMenuWindow::~MainMenuWindow()
{

}

void MainMenuWindow::create_Cashbox_Layout_Creator_Window_Button()
{
    btCashboxLayoutCreator = new QPushButton("Create Cashbox Layout");
    btCashboxLayoutCreator->setGeometry(this->width()/2-100, 50, 200, 25);
    connect(btCashboxLayoutCreator,SIGNAL(clicked()),SLOT(create_Cashbox_Layout_Creator_Window()));
            this->layout()->addWidget(btCashboxLayoutCreator);
    this->layout()->addWidget(btCashboxLayoutCreator);
}

void MainMenuWindow::create_Cashbox_Layout_Creator_Window()
{
    CashboxLayoutCreatorWindow mCashboxLayoutCreatorWindow;
    mCashboxLayoutCreatorWindow.exec();

}

void MainMenuWindow::create_Cashbox_Manager_Window_Button()
{
    btCashboxManager = new QPushButton("Cashbox Manager");
    btCashboxManager->setGeometry(this->width()/2-100, 150, 200, 25);
    connect(btCashboxManager, SIGNAL(clicked()), SLOT(create_Cashbox_Manager_Window()));
    this->layout()->addWidget(btCashboxManager);
}

void MainMenuWindow::create_Cashbox_Manager_Window()
{
    CashBoxManagerWindow mCashBoxManagerWindow;
    mCashBoxManagerWindow.exec();
}


