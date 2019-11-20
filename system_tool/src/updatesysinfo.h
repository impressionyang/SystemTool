#ifndef UPDATESYSINFO_H
#define UPDATESYSINFO_H

#include <QObject>
#include <QThread>
#include <system_info.h>


class UpdateSysInfo : public QObject {
    Q_OBJECT
public:
    explicit UpdateSysInfo(QObject *parent = nullptr);

    double getcpu();
    double getmem();
    double getdf();

private:
    System_Info *sysinfo;

    bool lock;

    double lastcpu;
    double lastmem;
    double lastdf;

    double nowcpu;
    double nowmem;
    double nowdf;

    //避免线程间资源问题，因为这个数据要一直更新
    double progresscpu;
    double progressmem;
    double progressdf;

signals:
    void valueupdatefinish();
    void complete();

public slots:
    void doUpdate();
    void updateprogress();
};

#endif // UPDATESYSINFO_H
