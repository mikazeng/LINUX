#include "widget.h"
#include "ui_widget.h"
#include "toolbox.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->qq->setPixmap((QPixmap(":/images/images/qq.png")));
    ui->youxi->setPixmap((QPixmap(":/images/images/youxi.png")));
    ui->IDEdit->setFocus();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_eixtBtn_clicked()
{
    close();
}

void Widget::on_loginBtn_clicked()
{
    if (ui->IDEdit->text().isEmpty())
        //如果lineEditUserID控件内容为空，提示用户错误
       {
           QMessageBox::information(this, tr("错误"), tr("用户ID不能为空"));
           ui->IDEdit->setFocus();
       }
       else
       {
           bool ok;
           int userid =  ui->IDEdit->text().toInt(&ok);
           if (!ok)//如果lineEditUserID控件内容不是数字，提示用户错误
           {
              QMessageBox::information(this, tr("错误"), tr("用户ID必须是从0到255的数字"));
              ui->IDEdit->setFocus();
           }
           else if(userid < 10000||userid >= 99999)//如果用户输入的userid小于0，大于255，提示错误，程序退出
           {
               QMessageBox::information(this, tr("错误"), tr("无效用户ID号"));
               ui->IDEdit->setFocus();
           }
           else
           {
              QString s =  ui->pass_Edit->text();
             //toolbox *p =new toolbox(userid,s);
              //p->show();
              close();
           }
       }
}

void Widget::on_registbtn_clicked()
{
    on_loginBtn_clicked();
}
