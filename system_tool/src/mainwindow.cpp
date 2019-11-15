#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) : QWidget(parent) {
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
  QLabel *label = new QLabel("什么都没有啊23333");
  QHBoxLayout *l_layout = new QHBoxLayout();
  l_layout->addWidget(label);
  this->setLayout(l_layout);
  qDebug() << "mainwindow";
}

Mainwindow::~Mainwindow() { qDebug() << "mainwindow close"; }
