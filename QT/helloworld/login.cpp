#include "login.h"
#include "ui_login.h"
#include<stdlib.h>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    show();
}

Login::~Login()
{
    delete ui;
}
