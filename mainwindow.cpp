#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置app图标
    this->setWindowIcon(QIcon(":/img/birdIcon.ico"));

    // 去掉标题栏 并 置顶窗口  ( 使用 this->windowFlags() 获取所有flag)
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 设置背景透明窗体, 120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 创建鸟对象
    this->_bird=new Bird(this);

    // 设置窗口尺寸 和鸟同样大
    this->setFixedSize(this->_bird->width(),this->_bird->height());

    // this-> listenBirdMove();
    // this-> listenBirdChangeImg();

    //启动鸟飞翔的动画
    this->_bird->startFly();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    // 将图片画到界面上
    QPainter (this).drawImage(0,0,this->_bird->BirdImg);
}

void MainWindow::listenBirdMove()
{
    connect(this->_bird,&Bird::moving,[=](QPoint point){
        this->move(point);
    });
}

void MainWindow::listenBirdChangeImg()
{
    connect(this->_bird,&Bird::changeImg,[=](){
        this->update();
    });
}


