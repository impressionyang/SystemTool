#ifndef CIRCLE_PROGRES_BAR_H
#define CIRCLE_PROGRES_BAR_H

#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPainter>
#include <QSize>
#include <QTimer>
#include <QWidget>
#include <QPropertyAnimation>

class Circle_Progres_Bar : public QWidget {
  Q_OBJECT
 public:
  explicit Circle_Progres_Bar(QSize size, QWidget *parent = nullptr);
  void set_progress(double progress);
  void set_progress_show_center(QString content);

 protected:
  void paintEvent(QPaintEvent *event) override;
  //  void resizeEvent(QResizeEvent *event) override;

 private:
  QTimer *time_test;
  QSize size;
  QColor take_up_progress_color;
  QColor left_progress_color;
  QLabel *progress_show_center;
  double progress;
  double lastprogress;
  double set;
  double time;
  double step;

  QRect screenRect;

 signals:

 public slots:
};

#endif  // CIRCLE_PROGRES_BAR_H
