#include<QApplication>
#include<QWidget>
#include"login.h"
int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    Login g;
    app.exec();
    return 0;
}
