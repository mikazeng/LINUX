#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_eixtBtn_clicked();

    void on_loginBtn_clicked();

    void on_registbtn_clicked();

public:

    Ui::Widget *ui;
};

#endif
