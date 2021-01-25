#include "bird.h"

Bird::Bird(QWidget *parent) : QWidget(parent)
{
    // 创建 二维数组  8,2
    _birdImgArr= QVector<QVector<QImage>>(8,QVector<QImage>(2));

    _parent= parent;

    this->loadBirdImgs();

    // 初始化 一个鸟
    BirdImg= _birdImgArr[0][0];

    // 获取屏幕信息
    _desktop= QGuiApplication::primaryScreen()->geometry();

    // 创建 鸟动作 定时器
    this->_birdFlyTimer=new QTimer(this);

    // 创建 鸟移动 定时器
    this->_autoMoveTimer = new QTimer(this);

    // 创建 菜单
    this->_rightMenu= new QMenu ();

    // 设置 鸟起始Y (放在屏幕高 中间)
    this->_autoMove_pos.setY(this->_desktop.height()/2-this->BirdImg.height());

    // 设置窗口的尺寸 为 鸟的尺寸
    this->setFixedSize(this->BirdImg.width(),this->BirdImg.height());

    this->listenBirdFlyTimer();
    this->listenAutoMoveTimer();
    this->listenRightMenu();

}

void Bird::startFly()
{
    this->_birdFlyTimer->start(100);
    this->_autoMoveTimer ->start (100);
}


void Bird::loadBirdImgs()
{
    // 加载所有鸟的资源
    for (int i=0 ;i<=this->_max ;i++ ) {
        QString imgPath= QString(":/img/bird%1").arg(i+1);

        // 读取资源图片
        QImage rightImage(imgPath);

        // 镜像反转为左侧图
        QImage leftImage = rightImage.mirrored(true, false);

        // 存入数组
        _birdImgArr[i][0]= leftImage;
        _birdImgArr[i][1]= rightImage;
    }
}

void Bird::listenBirdFlyTimer()
{
    // 监听定时器 timeout 信号
    connect(this->_birdFlyTimer,&QTimer::timeout,[=](){

        this->BirdImg = this->_birdImgArr[this->_index][_birdHeadRightState];

        this->_index++;
        if(this->_index>this->_max)
        {
            this->_index=this->_min;
        }

        // 更新界面, 触发父窗口 paintEvent
        // emit changeImg();
        _parent->update();

    });
}

void Bird::listenAutoMoveTimer()
{
    // 监听 autoMove 定时器
    connect (this->_autoMoveTimer,&QTimer::timeout,[=](){

        // 鼠标按下,停下鸟
        if(this->_mousePressState)
        {
            return ;
        }

        if(this->_autoMoveRight)
        {
            // 往右飞
            this->_autoMove_pos.setX(this->_autoMove_pos.x()+10);

            if(this->_autoMove_pos.x() > this->_desktop.width()-this->BirdImg.width())
            {
                this->_autoMoveRight=false;
                this->_birdHeadRightState=false;
            }
        }else{
            // 往左飞
            this->_autoMove_pos.setX(this->_autoMove_pos.x()-10);

            if(this->_autoMove_pos.x() < this->BirdImg.width())
            {
                this-> _autoMoveRight=true;
                this->_birdHeadRightState=true;
            }
        }

        if(this->_autoMoveDown)
        {
            // 往下飞
            this->_autoMove_pos.setY(this->_autoMove_pos.y()+10);

            if(this->_autoMove_pos.y() >= this->_desktop.height()-this->BirdImg.height())
            {
                this->_autoMoveDown=false;
            }
        }else{
            // 往上飞
            this->_autoMove_pos.setY(this->_autoMove_pos.y()-10);

            if(this->_autoMove_pos.y() <= this->BirdImg.height())
            {
                this->_autoMoveDown=true;
            }
        }
        // 改变鸟的位置
        // emit this->moving(point);
        _parent->move(this->_autoMove_pos);
    });
}

void Bird::listenRightMenu()
{
    //监听 菜单点击"退出"的 信号
    connect(this->_rightMenu->addAction("退出"),&QAction::triggered,[=](){
        exit(0); // 退出程序
    });
}

void Bird::mousePressEvent(QMouseEvent * e)
{

    //点击的点与窗口左上角 相对距离 =  当前点击的点  - 窗口距离屏幕左上角的距离
    this->_pos= e->globalPosition().toPoint() - ((QWidget*)this->parent())->frameGeometry().topLeft();

    // 暂停 鸟
    this->_mousePressState=true;

    // 如果点击的是鼠标右键,则弹出菜单
    if(e->button()==Qt::RightButton)
    {
        //弹出菜单, 弹出的位置和鼠标当前位置一致;
        this->_rightMenu->popup(QCursor::pos());

        // 监听 菜单消失 信号
        connect(this->_rightMenu,&QMenu::aboutToHide,[=](){
            this->_mousePressState=false; // 让鸟继续飞
        });
    }
}

void Bird::mouseMoveEvent(QMouseEvent * e)
{
    auto point=e->globalPosition ().toPoint () - this->_pos;

    this-> _autoMove_pos=point; //设置鸟的位置

    // 拖动 改变鸟的位置
    // emit this->moving(point);
    _parent->move(this->_autoMove_pos);

}


void Bird::mouseReleaseEvent(QMouseEvent *)
{
    // 鸟继续飞
    this->_mousePressState=false;
}


