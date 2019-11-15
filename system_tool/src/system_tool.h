#ifndef SYSTEM_TOOL_H
#define SYSTEM_TOOL_H

#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QRect>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>
#include <QtDebug>
#include "circle_progres_bar.h"
#include "mainwindow.h"
#include "welcom_robot.h"
#include "system_info.h"

class SystemTool : public QWidget {
  Q_OBJECT

 public:
  SystemTool(QWidget *parent = nullptr);
  ~SystemTool();

 private:
  Mainwindow *main_window;
  QTimer *timer;
  QTimer *timer2;
  welcom_robot *robot;
  QLabel *label_show_image;
  QPixmap app_main_icon;
  QPoint relativePos;
  QSystemTrayIcon *tray_icon;
  QMenu menu;  //右键按钮
  QMenu *tray_menu;
  QLabel *show_today;
  int menu_click_times;
  QRect screenRect;
  int info_use_temp;
  int timer_count;

  double last_cpu;
  double cpu_step;
  double last_mem;
  double mem_step;

  System_Info *sys_info;
  Circle_Progres_Bar *menary_bar;
  Circle_Progres_Bar *cpu_bar;
  Circle_Progres_Bar *storage_bar;

  void set_top_level(bool key);
  void set_right_menu();
  void set_tray_menu();
  void set_circle_pro_show_anmation();

 protected:
  //   void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void focusInEvent(QFocusEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;
  void enterEvent(QEvent *event) override;
  void leaveEvent(QEvent *event) override;
};


#endif // SYSTEM_TOOL_H
