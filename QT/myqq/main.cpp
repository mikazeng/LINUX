#include "widget.h"
#include <QApplication>
#include"toolbox.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   toolbox *p =new toolbox(1000,"1555");
   p->show();
   return a.exec();
}
