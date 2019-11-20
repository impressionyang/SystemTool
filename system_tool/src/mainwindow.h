#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include "sysinfopanel.h"

class Mainwindow : public QWidget {
    Q_OBJECT
public:
    explicit Mainwindow(UpdateSysInfo *object, QWidget *parent = nullptr);
    ~Mainwindow() override;
    void showwindow(bool show);

private:
    SysInfoPanel *sys_info_panel;
    QTimer *timer;
    QRect screenRect;

protected:
    void closeEvent(QCloseEvent *event) override;
signals:

public slots:
};

#endif  // MAINWINDOW_H
