#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // 初始化Qt
    QApplication app(argc, argv);

    // 初始化 main窗口
    MainWindow mainWindow;

    mainWindow.show();

    // 阻塞,让程序不退出
    // 进入主事件循环并等待直到调用exit（），
    // 然后返回设置为exit（）的值
    //（如果通过quit（）调用exit（），则该值为0）。
    return app.exec();
}
