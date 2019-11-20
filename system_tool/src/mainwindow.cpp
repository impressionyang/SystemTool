#include "mainwindow.h"

Mainwindow::Mainwindow(UpdateSysInfo *object, QWidget *parent) : QWidget(parent) {
    sys_info_panel = new SysInfoPanel(object);
    //获取主显示器参数
    //  QWidget *widget = new QWidget;
    QDesktopWidget *desktopWidget = QApplication::desktop();
    screenRect = desktopWidget->screenGeometry();
    setWindowTitle("设置");

    setWindowIcon(QIcon(":/src/images/tray_ico.png"));
    this->resize(screenRect.width() / 2, screenRect.height() / 2);
    //  this->resize(800, 400);
    this->move(screenRect.width() / 2 - this->size().width() / 2,
               screenRect.height() / 2 - this->size().height() / 2);
    QLabel *label = new QLabel("什么都没有啊23333\n233333");
    QHBoxLayout *l_layout = new QHBoxLayout();
    l_layout->addWidget(label);
    l_layout->addWidget(sys_info_panel);
    this->setLayout(l_layout);
    setVisible(false);
    qDebug() << "mainwindow";
    setFixedSize(this->width(), this->height());                    // 禁止拖动窗口大小
}

void Mainwindow::showwindow(bool show) {
    setVisible(show);
}

Mainwindow::~Mainwindow() {
    qDebug() << "mainwindow close";
}

void Mainwindow::closeEvent(QCloseEvent *event) { //此函数在QWidget关闭时执行
    qDebug() << "click close" << endl;
//    setVisible(false);
}

