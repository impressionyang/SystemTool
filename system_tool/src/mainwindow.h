#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>

class Mainwindow : public QWidget {
  Q_OBJECT
 public:
  explicit Mainwindow(QWidget *parent = nullptr);
  ~Mainwindow();

 private:
  QRect screenRect;

 signals:

 public slots:
};

#endif  // MAINWINDOW_H
