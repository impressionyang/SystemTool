#include "welcom_robot.h"

welcom_robot::welcom_robot(int height, QWidget *parent) : QWidget(parent) {
  this->setAttribute(Qt::WA_TranslucentBackground, true);
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                 Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint |
                 Qt::X11BypassWindowManagerHint | Qt::Tool);

  size = height / 3;
  pic_head = new QPixmap();
  pic_body = new QPixmap();
  pic_left_arm = new QPixmap();
  pic_rifht_arm = new QPixmap();

  main_layout = new QVBoxLayout(this);
  head_layout = new QHBoxLayout();
  down_layout = new QHBoxLayout();
  left_arm_layout = new QHBoxLayout();
  body_layout = new QHBoxLayout();
  right_arm_layout = new QHBoxLayout();

  head_show = new QLabel("head");
  left_arm_show = new QLabel("left_arm");
  right_arm_show = new QLabel("right_arm");
  body_show = new QLabel("body");

  head_layout->addStretch();
  head_layout->addWidget(head_show);
  head_layout->addStretch();

  left_arm_layout->addStretch();
  left_arm_layout->addWidget(left_arm_show);
  right_arm_layout->addWidget(right_arm_show);
  right_arm_layout->addStretch();
  body_layout->addWidget(body_show);

  down_layout->addLayout(left_arm_layout);
  down_layout->addLayout(body_layout);
  down_layout->addLayout(right_arm_layout);

  main_layout->addLayout(head_layout);
  main_layout->addLayout(down_layout);

  set_head();
  set_arms();
  set_body();

  this->setLayout(main_layout);
  //  this->resize(size * 3, size * 3);
}

void welcom_robot::set_head() {
  QImage *img_temp_set;
  img_temp_set = new QImage(":/src/images/head_test.png");
  *pic_head = QPixmap::fromImage(*img_temp_set);
  head_show->setPixmap(pic_head->scaled(size, size));
}

void welcom_robot::set_arms() {
  QImage *img_temp_set;
  img_temp_set = new QImage(":/src/images/left_arm_test.png");
  *pic_left_arm = QPixmap::fromImage(*img_temp_set);
  left_arm_show->setPixmap(pic_left_arm->scaled(size, size));
  img_temp_set = new QImage(":/src/images/right_arm_test.png");
  *pic_rifht_arm = QPixmap::fromImage(*img_temp_set);
  right_arm_show->setPixmap(pic_rifht_arm->scaled(size, size));
}

void welcom_robot::set_body() {
  QImage *img_temp_set;
  img_temp_set = new QImage(":/src/images/thin_body_test.png");
  *pic_body = QPixmap::fromImage(*img_temp_set);
  body_show->setPixmap(pic_body->scaled(size / 1.2, size));
}

void welcom_robot::setSize(int size) {
  this->size = size;
  set_head();
  set_body();
  set_arms();
  this->repaint();
}

int welcom_robot::getHeight() { return main_layout->widget()->height(); }
int welcom_robot::getWidth() { return main_layout->widget()->width(); }

void welcom_robot::move_left_arm(int duaration) {
  QParallelAnimationGroup *group = new QParallelAnimationGroup();
  QPropertyAnimation *animate =
      new QPropertyAnimation(left_arm_show, "geometry");
  animate->setDuration(duaration);
  animate->setStartValue(QRect(0, size + 12, size, size));
  animate->setEndValue(QRect(1.4 * size, size + 12, size, size));
  //  animate->start();
  group->addAnimation(animate);

  animate = new QPropertyAnimation(right_arm_show, "pos");
  animate->setDuration(duaration);
  animate->setStartValue(QPoint(2.2 * size, size + 12));
  animate->setEndValue(QPoint(size * 0.9, size + 12));

  group->addAnimation(animate);

  animate = new QPropertyAnimation(head_show, "pos");
  animate->setDuration(duaration);
  animate->setStartValue(QPoint(1.15 * size, 5));
  animate->setEndValue(QPoint(1.15 * size, 10));

  group->addAnimation(animate);

  group->start();
//  qDebug() << "start animate!!";
}
