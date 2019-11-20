#ifndef SYSINFOPANEL_H
#define SYSINFOPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include "circle_progres_bar.h"
#include "updatesysinfo.h"

class SysInfoPanel : public QWidget {
    Q_OBJECT
public:
    explicit SysInfoPanel(UpdateSysInfo *onject = nullptr, QWidget *parent = nullptr);
    ~SysInfoPanel();
private:
    Circle_Progres_Bar *cpu_bar;
    Circle_Progres_Bar *mem_bar;
    Circle_Progres_Bar *storage_bar;
    QTimer *timer;
    UpdateSysInfo *sys_info;
    int timer_count;
    double last_cpu;
    double cpu_step;
    double last_mem;
    double mem_step;
    QWidget *widget;
    QLabel *label;



    void setconnection();

signals:

public slots:
};

#endif // SYSINFOPANEL_H
