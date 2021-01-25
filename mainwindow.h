#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bird.h"
#include <QMainWindow>
#include <qtimer.h>
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "QMessageBox"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief 鸟对象的指针
     */
    Bird * _bird;

    /**
     * @brief 重写 绘图事件
     */
    void paintEvent(QPaintEvent*);

    void listenBirdMove();
    void listenBirdChangeImg();

private:
    Ui::MainWindow *ui; // 窗口中控件 对象
};
#endif // MAINWINDOW_H
