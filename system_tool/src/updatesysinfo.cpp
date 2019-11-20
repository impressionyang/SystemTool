#include "updatesysinfo.h"

UpdateSysInfo::UpdateSysInfo(QObject *parent) : QObject(parent) {
    lock = true;

    lastcpu = 0;
    lastmem = 0;
    lastdf = 0;

    nowcpu = 0;
    nowmem = 0;
    nowdf = 0;

    progresscpu = 0;
    progressmem = 0;
    progressdf = 0;

    sysinfo = new System_Info();

    connect(this, SIGNAL(valueupdatefinish()), this, SLOT(updateprogress()));

}

void UpdateSysInfo::doUpdate() {
    while(lock) {
        //
        lastcpu = sysinfo->getcpu();
        lastmem = sysinfo->getmem();
        lastdf = sysinfo->getstor();
        sysinfo->value_update();
        nowcpu = sysinfo->getcpu();
        nowmem = sysinfo->getmem();
        nowdf = sysinfo->getstor();

        emit valueupdatefinish();
        QThread::msleep(1000);
    }
    emit complete();
}

void UpdateSysInfo::updateprogress() {
    int step = 25;
    double cpustep = (nowcpu - lastcpu) / step;
    double memstep = (nowmem - lastmem) / step;
    double dfstep = (nowdf - lastdf) / step;

    progresscpu = lastcpu;
    progressdf = lastdf;
    progressmem = lastmem;

    while (step--) {
        progresscpu = progresscpu + cpustep;
        progressdf = progressdf + dfstep;
        progressmem = progressmem + memstep;
        QThread::msleep(40);
    }
}

double UpdateSysInfo::getcpu() {
    return this->progresscpu;
}

double UpdateSysInfo::getmem() {
    return this->progressmem;
}

double UpdateSysInfo::getdf() {
    return this->progressdf;
}
