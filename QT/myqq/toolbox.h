#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <QObject>
#include <QToolBox>
#include <QWidget>
#include <QTcpSocket>
#include<QHostAddress>
#include<QToolButton>
#include"widget.h"
#define PORT 6666
#define IP "127.0.0.1"
//friend list
#define CLINETCOUNT 256  //最大客户端数量
class toolbox : public QToolBox
{
Q_OBJECT
public:
    explicit toolbox(int userid,QString s,QWidget *parent= 0);
    virtual ~toolbox();
    void   init_toolBtn();
    void  init_username();
public:
    int userid;
    QString passwd;
    QString hostip;
    int hostport;
    QString username[CLINETCOUNT];
    QToolButton *toolBtn[CLINETCOUNT];
    QTcpSocket *sockClient;
};

#endif // TOOLBOX_H
