#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("登录界面"));
    //标题处理
        //居中
        ui->title->setAlignment(Qt::AlignHCenter);
        //字体
        QFont font ( "Microsoft YaHei", 20, QFont::Bold);
        ui->title->setFont(font);
    //登录界面
        //字体
        QFont log_font ( "Microsoft YaHei", 10, QFont::Bold);
        ui->ID->setFont(log_font);
        ui->ID_Edit->setPlaceholderText("请输入用户名");
        ui->password->setFont(log_font);
        ui->password_Edit->setPlaceholderText("请输入密码");
        //密码格式
        ui->password_Edit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//进入登录界面
void MainWindow::on_my_login_clicked()
{
    QString _ID=ui->ID_Edit->text();
    QString Pword=ui->password_Edit->text();

    //search 用于在数据库中查找未登录账号
    QString search=QString("select * from user where userName='%1' and userPwd='%2' and status='false' ").arg(_ID).arg(Pword);
    //if_login 用于判断是否已经登录
    QString if_login=QString("select * from user where userName='%1' and userPwd='%2' and status='true' ").arg(_ID).arg(Pword);
    //update 用于登录后更新登录状态
    QString update=QString("update user set status='true' where userName='%1';").arg(_ID);
    QSqlQuery query;
    query.exec(search);
    if(query.first())
    {
        //更新登录状态
        query.exec(update);
        //关闭现有窗口，进入登录界面
        login * v=new login();
        v->show();
        this->close();
        qDebug()<<"登录成功"<<endl;
    }
    else if(query.exec(if_login))
    {
        QMessageBox::warning(NULL,"Error","当前用户已经登录，请勿重复登录！！！");
    }
    else
    {

        QMessageBox::warning(NULL,"Error","登录失败，用户名或密码错误！！！");
    }
}

//进入注册界面
void MainWindow::on_my_register_clicked()
{
    myregister * v=new myregister();
    v->setModal(true);
    v->show();
}



//设置背景
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/background/sea.jpg"));
}
