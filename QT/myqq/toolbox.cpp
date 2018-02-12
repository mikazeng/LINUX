#include "toolbox.h"
#include "widget.h"
#include<QGroupBox>
#include<QVBoxLayout>
toolbox::toolbox(int userid,QString s,QWidget *parent)
    :QToolBox(parent),passwd(s),userid(userid)
{
        QString s1 = QString::number(userid);
        setWindowTitle(s1);
        //根据登录对话框中用户输入的ID号设置主窗口标题
        hostip = IP;
        hostport = PORT;
        init_username();
        init_toolBtn();
        this->setFixedSize(300,640);
        /*
        //根据登录对话框中用户输入的服务器IP和端口号连接到服务器
        sockClient = new QTcpSocket(this);
        connect(sockClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
                SLOT(sock_Error(QAbstractSocket::SocketError)));//设置socket出错时的槽函数
        connect(sockClient, SIGNAL(readyRead()), this, SLOT(read_Msg()));//设置socket读消息的槽函数
        connect(sockClient, SIGNAL(connected()), this, SLOT(socket_connected()));//设置socket完成连接消息的槽函数
        QHostAddress hostAddr(hostip);
        sockClient->connectToHost(hostAddr, hostport);
        */
}
void toolbox::init_toolBtn()//初始化所有的toolBtn
{
    QString imagename;
    for(int i = 0;i<CLINETCOUNT;i++ )
    {
        toolBtn[i] = new QToolButton();
        toolBtn[i]->setObjectName(QString::number(i));//为每个toolBtn设置ObjectName属性
        toolBtn[i]->installEventFilter(this);//toolBtn的点击事件由toolbox1来处理
        toolBtn[i]->setText(username[i]);//设置toolBtn标题
        imagename.sprintf(":/images/images/%d.png", i);

        toolBtn[i]->setIcon(QPixmap(imagename).scaled(100,100));////设置toolBtn图像

       // toolBtn[i]->setIconSize(QPixmap(imagename).size());//设置toolBtn大小和图像一致
        toolBtn[i]->setFixedSize(100,80);
        toolBtn[i]->setAutoRaise(true);//设置toolBtn自动浮起界面风格
       //toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置toolBtn文字在图像旁边
        toolBtn[i]->setToolTip(tr("未知"));//设置toolBtn 鼠标提示为“未知”
       // child[i] = new Widget1(toolBtn[i]->icon(), i, toolBtn[i]->text(), this);
    }

    QGroupBox *groupBox[2];//
    QVBoxLayout *layout[2];
    static int index = 0;
    for(int i=0;i<2;i++)
    {
        groupBox[i] = new QGroupBox;
        layout[i] = new QVBoxLayout(groupBox[i]);
        layout[i]->setMargin(10);//设置布局中各窗体的显示间距
        layout[i]->setAlignment(Qt::AlignHCenter);//设置布局中各窗体的位置
        for(int j=0;j<128;j++)
        {
            layout[i]->addWidget(toolBtn[index++]);
        }
        layout[i]->addStretch();//插入一个占位符
    }

    addItem((QWidget *)groupBox[0], tr("online好友"));
    addItem((QWidget *)groupBox[1], tr("not online"));
}
toolbox::~toolbox()
{
    ;
}
void toolbox::init_username()
{
    for(int i = 0;i<CLINETCOUNT;i++ )//将username[]数组中所有的成员初始化
    {
        username[i] = tr("用户") + QString::number(i);
    }
}
