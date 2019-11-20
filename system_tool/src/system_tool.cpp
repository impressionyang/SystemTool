#include "system_tool.h"

SystemTool::SystemTool(QWidget *parent) : QWidget(parent, Qt::FramelessWindowHint) {
    //

    updatesysinfo = new UpdateSysInfo();
    timer_count = 0;
    timer = new QTimer(this);
    cpu_step = 0;
    sys_info = new System_Info();
    menu_click_times = 0;
    info_use_temp = 0;
//    main_window = new Mainwindow();
    setWindowIcon(QIcon(":/src/images/tray_ico.png"));

    //  , Qt::FramelessWindowHint
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                   Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint |
                   Qt::X11BypassWindowManagerHint | Qt::Tool);

    //获取主显示器参数
    QDesktopWidget *desktopWidget = QApplication::desktop();
    screenRect = desktopWidget->screenGeometry();

    menary_bar = new Circle_Progres_Bar(QSize(100, 100));
    cpu_bar = new Circle_Progres_Bar(QSize(100, 100));
    storage_bar = new Circle_Progres_Bar(QSize(100, 100));
    menary_bar->set_pen(QColor(qrand() % (255), qrand() % (255), qrand() % (255)), 8);
    cpu_bar->set_pen(QColor(qrand() % (255), qrand() % (255), qrand() % (255)), 8);
    storage_bar->set_pen(QColor(qrand() % (255), qrand() % (255), qrand() % (255)), 8);

    menary_bar->set_progress_show_center("内存");
    cpu_bar->set_progress_show_center("CPU");
    storage_bar->set_progress_show_center("储存");

    QImage *image_icon = new QImage(":/src/images/head_test.png");
    QImage *image = new QImage(":/src/images/impressionyang_logo.png");
    app_main_icon = QPixmap::fromImage(*image_icon);
    QPixmap image_to_show = QPixmap::fromImage(*image);

    robot = new welcom_robot(screenRect.height() / 7);
    //  robot->setSize();

    //以下标签label_show_imag的代码暂时不哟嗯
    label_show_image = new QLabel("test");
    //  label_show_image->setMaximumSize(robot->getHeight());
    //  qDebug() << "robor_size: " << robot->getHeight();

    QPixmap final_pic =
        app_main_icon.scaled(screenRect.height() / 8, screenRect.height() / 8);
    label_show_image->setPixmap(final_pic);

    show_today = new QLabel("default");
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText, QColor(100, 100, 100, 255));
    show_today->setPalette(pa);
    show_today->setStyleSheet(
        "background-color: rgba(230, 230, 230, .7);border-radius: 10px;");  // 设置QLabel背景的颜色
    //设置字号
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    show_today->setFont(ft);

    QHBoxLayout *layout_show_today = new QHBoxLayout();
    layout_show_today->addStretch();
    layout_show_today->addWidget(show_today);
    layout_show_today->addStretch();

    QHBoxLayout *layout_show_image = new QHBoxLayout();
    layout_show_image->addStretch();
    //  layout_show_image->addWidget(label_show_image);
    layout_show_image->addWidget(robot);
    layout_show_image->addStretch();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout_show_image);
    layout->addLayout(layout_show_today);

    //  layout->addWidget(menary_bar);
    //  layout->addWidget(cpu_bar);
    //  layout->addWidget(storage_bar);

    //  menary_bar->setMinimumSize(QSize(100, 100));
    //  cpu_bar->setMinimumSize(QSize(100, 100));
    //  storage_bar->setMinimumSize(QSize(100, 100));

    menary_bar->setMaximumSize(1, 1);
    cpu_bar->setMaximumSize(1, 1);
    storage_bar->setMaximumSize(1, 1);

    menary_bar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cpu_bar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    storage_bar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    menary_bar->setVisible(false);
    cpu_bar->setVisible(false);
    storage_bar->setVisible(false);

    QGridLayout *main_layout = new QGridLayout();
    //  main_layout->setSizeConstraint(QLayout::SetFixedSize);  //使得控件不推挤
    main_layout->setSpacing(10);
    main_layout->addWidget(cpu_bar, 1, 0);
    main_layout->addWidget(storage_bar, 0, 1);
    main_layout->addWidget(menary_bar, 1, 1);
    main_layout->addLayout(layout, 0, 0);

    main_layout->setRowStretch(0, 2);
    main_layout->setRowStretch(1, 3);
    main_layout->setColumnStretch(0, 2);
    main_layout->setColumnStretch(1, 3);

    setLayout(main_layout);
    //  label_show_image->show();

    //  this->move(QPoint(screenRect.width() / 2, screenRect.height() / 2) -
    //             QPoint(label_show_image->size().rwidth() + 50,
    //                    label_show_image->size().rheight() + 50));

    set_right_menu();
    set_tray_menu();

    //  menary_bar->show();
    //  cpu_bar->show();
    //  storage_bar->show();

    //  set_circle_pro_show_anmation();



    //开新线程去更新数据
    QThread *thread = new QThread();
    //当线程启动时，执行Worker类的耗时函数doLongTimeWork()
    connect(thread, SIGNAL(started()), updatesysinfo, SLOT(doUpdate()));
    //当耗时函数执行完毕，发出complete()信号时，删除worker实例
    connect(updatesysinfo, SIGNAL(complete()), updatesysinfo, SLOT(deleteLater()));
    //当worker对象实例销毁时，退出线程
    connect(updatesysinfo, SIGNAL(destroyed(QObject *)), thread, SLOT(quit()));
    //当线程结束时，销毁线程对象实例
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //移动worker对象实例到线程中
    updatesysinfo->moveToThread(thread);
    //启动线程
    thread->start();

    connect(robot, &welcom_robot::Hover_in, this, [ = ]() {
//    qDebug() << "in 233";

//      menary_bar->setVisible(true);
//      cpu_bar->setVisible(true);
//      storage_bar->setVisible(true);
        menary_bar->setVisible(true);
        cpu_bar->setVisible(true);
        storage_bar->setVisible(true);


        menary_bar->setMinimumSize(QSize(100, 100));
        cpu_bar->setMinimumSize(QSize(100, 100));
        storage_bar->setMinimumSize(QSize(100, 100));


        menary_bar->setMaximumSize(100, 100);
        cpu_bar->setMaximumSize(100, 100);
        storage_bar->setMaximumSize(100, 100);

        update();
    });

    connect(robot, &welcom_robot::Hover_out, this, [ = ]() {
//    qDebug() << "out 233";

//     menary_bar->setVisible(false);
//     cpu_bar->setVisible(false);
//     storage_bar->setVisible(false);
        menary_bar->setMinimumSize(QSize(1, 1));
        cpu_bar->setMinimumSize(QSize(1, 1));
        storage_bar->setMinimumSize(QSize(1, 1));

        menary_bar->setMaximumSize(1, 1);
        cpu_bar->setMaximumSize(1, 1);
        storage_bar->setMaximumSize(1, 1);

        menary_bar->setVisible(false);
        cpu_bar->setVisible(false);
        storage_bar->setVisible(false);

        update();
    });



    connect(timer, &QTimer::timeout, this, [ = ]() {
        //    QString time_now = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
        show_today->setText(QDateTime::currentDateTime().toString("   hh:mm:ss   "));

        cpu_bar->set_progress(updatesysinfo->getcpu());
        menary_bar->set_progress(updatesysinfo->getmem());
        storage_bar->set_progress(updatesysinfo->getdf());

        //    if (this->isVisible()) {
        //      robot->move_left_arm();
        //    }

//    timer_count++;
//    if(timer_count>=25){
//        timer_count=0;
//        last_cpu=sys_info->getcpu();
//        last_mem=sys_info->getmem();
//        //update system info
//        sys_info->value_update();
//        cpu_step=((sys_info->getcpu()-last_cpu)/25);
//        mem_step=((sys_info->getmem()-last_mem)/25);
//    }
//    last_mem=last_mem+mem_step;
//    menary_bar->set_progress(last_mem);
//      qDebug()<<"cpu_step="<<cpu_step<<"lastcpu="<<last_cpu<<"now cpu="<<sys_info->getcpu()<<endl;
//    last_cpu=last_cpu+cpu_step;
//    cpu_bar->set_progress(last_cpu);
//    storage_bar->set_progress(sys_info->getstor());

        //
    });
    timer->start(40);


    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, [ = ] {
    });
    timer2->start(1000);
    //  qDebug() << robot->width() << "," << robot->height();

    this->move(QPoint(screenRect.width() / 2, screenRect.height() / 2));
}

SystemTool::~SystemTool() {
    qDebug() << "float close";
}

void SystemTool::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {  //左键拖动窗体
        relativePos = this->pos() - event->globalPos();
    }
    if (event->button() == Qt::MidButton) {  //中键关闭窗体
        //    this->close();
        exit(0);
    }
    if (event->button() == Qt::RightButton) {  //右键打开网址或文件
        //    qDebug() << "click right btn!!!";
        //    this->setVisible(false);
        //在鼠标位置显示
        menu.exec(QCursor::pos());
    }
}

void SystemTool::mouseMoveEvent(QMouseEvent *event) { //移动窗体
//  qDebug() << "hover!";
    this->move(event->globalPos() + relativePos);  //- QPoint(50, 25)
    if (event->type() == QMouseEvent::HoverEnter) {
        menary_bar->setVisible(true);
        cpu_bar->setVisible(true);
        storage_bar->setVisible(true);
//    qDebug() << "visible!";
    }
    if (event->type() == QMouseEvent::HoverLeave) {
        menary_bar->setVisible(false);
        cpu_bar->setVisible(false);
        storage_bar->setVisible(false);
    }
}

void SystemTool::set_top_level(bool key) {}

void SystemTool::set_right_menu() {
    QAction *action_reset_location = new QAction("恢复初始位置", this);
    QAction *action_main_window = new QAction("设置", this);
    QAction *action_animate = new QAction("开始动画", this);
    QAction *action_hide = new QAction("隐藏             ", this);
    QAction *action_quit = new QAction("退出", this);

    //添加菜单项，指定图标、名称、响应函数
    menu.addAction(action_reset_location);
    menu.addAction(action_main_window);
    menu.addAction(action_animate);
    menu.addAction(action_hide);
    menu.addAction(action_quit);

    connect(action_reset_location, &QAction::triggered, this, [ = ]() {
        this->move(QPoint(screenRect.width(), screenRect.height()) -
                   QPoint(size().rwidth(), size().rheight()));
//    qDebug() << size();
    });
    connect(action_animate, &QAction::triggered, this, [ = ]() {
        if (action_animate->text() == "开始动画") {
            connect(timer2, &QTimer::timeout, robot,
            [ = ]() {
                robot->move_left_arm(1000);

            });
            action_animate->setText("停止动画");
        } else {
//      qDebug() << "stop animate";
            timer2->disconnect(robot);
            action_animate->setText("开始动画");
        }
    });

    connect(action_main_window, &QAction::triggered, this, [ = ]() {
//        main_window->showwindow(true);
        this->main_window = new Mainwindow(updatesysinfo);
        main_window->show();

    });
    connect(action_hide, &QAction::triggered, this,
    [ = ]() {
        this->setVisible(false);
    });
    connect(action_quit, &QAction::triggered, this, [ = ]() {
        exit(0);
    });
    //  menu.addAction(QIcon("1.png"), QStringLiteral("添加"), this,
    //                 SLOT(OnBscGroupRightAction()));
}

void SystemTool::set_tray_menu() {
    tray_menu = new QMenu(this);

    //新建QSystemTrayIcon对象
    tray_icon = new QSystemTrayIcon(this);
    //新建托盘要显示的icon
    QPixmap tray_ico = app_main_icon.scaled(100, 100);
    QIcon icon = QIcon(tray_ico);
    //将icon设到QSystemTrayIcon对象中
    tray_icon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    tray_icon->setToolTip(QObject::trUtf8("impressionyang"));
    //在系统托盘显示此对象
    tray_icon->show();

    QAction *action_show_main_win = new QAction("设置");
    QAction *action_show = new QAction("显示             ", this);
    QAction *action_hide = new QAction("隐藏", this);
    QAction *action_reset_location = new QAction("恢复初始位置", this);
    QAction *action_quit = new QAction("退出", this);

    //添加菜单项，指定图标、名称、响应函数
    tray_menu->addAction(action_show_main_win);
    tray_menu->addAction(action_show);
    tray_menu->addAction(action_hide);
    tray_menu->addAction(action_reset_location);
    tray_menu->addAction(action_quit);

    connect(action_show_main_win, &QAction::triggered, this, [ = ]() {
//        main_window->showwindow(true);
    });
    connect(tray_icon, &QSystemTrayIcon::activated, this, [ = ]() {
        menu_click_times++;
//    if (this->isVisible()) {
//      this->setVisible(false);
//    } else {
//      this->setVisible(true);
//    }

        main_window->showwindow(true);

    });

    connect(action_reset_location, &QAction::triggered, this, [ = ]() {
        this->move(QPoint(screenRect.width(), screenRect.height()) -
                   QPoint(size().rwidth(), size().rheight()));
    });
    connect(action_show, &QAction::triggered, this,
    [ = ]() {
        this->setVisible(true);
    });
    connect(action_hide, &QAction::triggered, this,
    [ = ]() {
        this->setVisible(false);
    });
    connect(action_quit, &QAction::triggered, this, [ = ]() {
        exit(0);
    });

    tray_icon->setContextMenu(tray_menu);
}

void SystemTool::set_circle_pro_show_anmation() {
    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation *animate = new QPropertyAnimation(menary_bar, "pos");
    animate->setDuration(1000);
    animate->setStartValue(QPoint(0, 0));
    animate->setEndValue(QPoint(-300, 0));
    //  animate->start();
    group->addAnimation(animate);

    animate = new QPropertyAnimation(cpu_bar, "pos");
    animate->setDuration(1000);
    animate->setStartValue(QPoint(0, 0));
    animate->setEndValue(QPoint(-150, -150));
    group->addAnimation(animate);

    animate = new QPropertyAnimation(storage_bar, "pos");
    animate->setDuration(1000);
    animate->setStartValue(QPoint(0, 0));
    animate->setEndValue(QPoint(0, -300));
    group->addAnimation(animate);

    group->start();

}

void SystemTool::focusInEvent(QFocusEvent *event) {
    menary_bar->setVisible(true);
    cpu_bar->setVisible(true);
    storage_bar->setVisible(true);
}

void SystemTool::focusOutEvent(QFocusEvent *event) {
    menary_bar->setVisible(false);
    cpu_bar->setVisible(false);
    storage_bar->setVisible(false);
}

void SystemTool::enterEvent(QEvent *event) {
    //  menary_bar->setVisible(true);
    //  cpu_bar->setVisible(true);
    //  storage_bar->setVisible(true);

    //  menary_bar->set_progress(80);
    //  cpu_bar->set_progress(80);
    //  storage_bar->set_progress(80);
    //  //  resize(QSize(screenRect.height() / 7 + 100, screenRect.height() / 7 +
    //  //  100));
    //  menary_bar->setMinimumSize(QSize(100, 100));
    //  cpu_bar->setMinimumSize(QSize(100, 100));
    //  storage_bar->setMinimumSize(QSize(100, 100));

    //  menary_bar->setMaximumSize(100, 100);
    //  cpu_bar->setMaximumSize(100, 100);
    //  storage_bar->setMaximumSize(100, 100);

    //  qDebug() << "enter event!";
}

void SystemTool::leaveEvent(QEvent *event) {
    //  menary_bar->setVisible(false);
    //  cpu_bar->setVisible(false);
    //  storage_bar->setVisible(false);
    //  //  resize(QSize(screenRect.height() / 7, screenRect.height() / 7));
    //  menary_bar->setMinimumSize(QSize(1, 1));
    //  cpu_bar->setMinimumSize(QSize(1, 1));
    //  storage_bar->setMinimumSize(QSize(1, 1));

    //  menary_bar->setMaximumSize(1, 1);
    //  cpu_bar->setMaximumSize(1, 1);
    //  storage_bar->setMaximumSize(1, 1);
    //  qDebug() << "leave event!";
}

