#include "sysinfopanel.h"

SysInfoPanel::SysInfoPanel(UpdateSysInfo *object, QWidget *parent) :  QWidget(parent) {
//    widget=this-
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    sys_info = object;

    QVBoxLayout *mainlayout = new QVBoxLayout();
    QHBoxLayout *sys_info_layout = new QHBoxLayout();

    cpu_bar = new Circle_Progres_Bar(QSize(250, 250));
    cpu_bar->set_progress_show_center("cpu");
    cpu_bar->set_pen(QColor(qrand() % (255), qrand() % (255), qrand() % (255)), 20);
    mem_bar = new Circle_Progres_Bar(QSize(100, 100));
    mem_bar->set_progress_show_center("memery");
    mem_bar->set_pen(QColor(qrand() % (255), qrand() % (255), qrand() % (255)), 10);
    storage_bar = new Circle_Progres_Bar(QSize(100, 100));
    storage_bar->set_progress_show_center("storage");
    storage_bar->set_pen(QColor(qrand() % (255), qrand() % (255), qrand() % (255)), 10);

    label = new QLabel("233");
    sys_info_layout->addWidget(cpu_bar);
//    sys_info_layout->addStretch();
    sys_info_layout->addWidget(mem_bar);
    sys_info_layout->addWidget(storage_bar);
    mainlayout->addLayout(sys_info_layout);
//    sys_info_layout->addWidget(label);
    setLayout(mainlayout);

    //开新线程去更新数据
    QThread *thread = new QThread();
    //当线程启动时，执行Worker类的耗时函数doLongTimeWork()
    connect(thread, SIGNAL(started()), sys_info, SLOT(doUpdate()));
    //当耗时函数执行完毕，发出complete()信号时，删除worker实例
    connect(sys_info, SIGNAL(complete()), sys_info, SLOT(deleteLater()));
    //当worker对象实例销毁时，退出线程
    connect(sys_info, SIGNAL(destroyed(QObject *)), thread, SLOT(quit()));
    //当线程结束时，销毁线程对象实例
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //移动worker对象实例到线程中
    sys_info->moveToThread(thread);
    //启动线程
    thread->start();


//    this->layout()->addChildLayout(mainlayout);
//    this->resize(800, 400);
//    this->setVisible(true);
    timer = new QTimer();
    timer_count = 0;
    setconnection();
    timer->start(40);

    qDebug() << "sysinfopanel" << endl;
}

void SysInfoPanel::setconnection() {
    connect(timer, &QTimer::timeout, this, [ = ]() {
        if(this->isVisible()) {
            cpu_bar->set_progress(sys_info->getcpu());
            mem_bar->set_progress(sys_info->getmem());
            storage_bar->set_progress(sys_info->getdf());

        }
    });
//    connect(timer,&QTimer::timeout,this,[=](){
//        cpu_bar->set_progress(sys_info.get)
//    });
}


SysInfoPanel::~SysInfoPanel() {
    qDebug() << "sysinfopanel finish" << endl;
}

