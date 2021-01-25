#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <qmenu.h>
#include <iostream>
#include <QDebug>
#include <QGuiApplication>
using namespace std;

class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);

    /**
     * @brief 当前展示的 鸟动作
     */
    QImage BirdImg;

    /**
     * @brief 启动定时器 , 让鸟开始飞
     */
    void startFly();

private:

    /**
     * @brief 父窗口对象指针
     */
    QWidget * _parent;

    /**
     * @brief 存放 所有鸟动作图片
     */
    QVector<QVector<QImage>> _birdImgArr;

    int _min=0;
    int _index=0; // 当前鸟图片索引
    int _max=7;

    // 鸟头向右 状态
    bool _birdHeadRightState=true;

    // 鸟飞翔 定时器
    QTimer * _birdFlyTimer;


    // 自动飞翔
    QTimer* _autoMoveTimer;
    QPoint _autoMove_pos;

    // 鸟飞翔 方向
    bool _autoMoveDown =true;
    bool _autoMoveRight =true;

    /**
     * 点击的点与窗口左上角 相对距离点位
     */
    QPoint _pos;

    /**
     * 右键菜单
     */
    QMenu* _rightMenu;

    /**
     * 桌面范围信息
     */
    QRect _desktop;

    /**
      * 鼠标按下状态 (用于暂停鸟)
      */
    bool _mousePressState =false;

private:
    /**
     * 重写 鼠标按下 事件
     */
    void mousePressEvent(QMouseEvent*);


    /**
     * 重写 鼠标移动 事件
     */
    void mouseMoveEvent(QMouseEvent*);

    /**
     * 重写 鼠标释放 事件
     */
    void mouseReleaseEvent(QMouseEvent*);

    /**
     * 加载鸟的图片资源
     */
    void loadBirdImgs();

    /**
     * 监听 鸟飞行动作 定时器
     */
    void listenBirdFlyTimer();

    /**
     * 监听鸟 自动移动 定时器
     */
    void listenAutoMoveTimer();

    /**
     * 监听 右键菜单
     */
    void listenRightMenu();

signals:

    /**
     * @brief 图片改变 信号
     */
    void changeImg();

    /**
     * @brief 鼠标拖动 信号
     * @param point 坐标点
     */
    void moving(QPoint point);

};

#endif // BIRD_H
