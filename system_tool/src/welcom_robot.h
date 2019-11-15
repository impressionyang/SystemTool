#ifndef WELCOM_ROBOT_H
#define WELCOM_ROBOT_H

#include <QDebug>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QWidget>

class welcom_robot : public QWidget {
  Q_OBJECT
 public:
  explicit welcom_robot(int height, QWidget *parent = nullptr);
  void set_head();
  void set_arms();
  void set_body();
  void animate_head();
  void animate_arms();
  void animate_body();
  void setSize(int size);
  int getHeight();
  int getWidth();
  void move_left_arm(int duaration);

 private:
  int size;

  QVBoxLayout *main_layout;

  QHBoxLayout *head_layout;

  QHBoxLayout *down_layout;

  QHBoxLayout *left_arm_layout;
  QHBoxLayout *right_arm_layout;
  QHBoxLayout *body_layout;

  QLabel *head_show;
  QLabel *left_arm_show;
  QLabel *right_arm_show;
  QLabel *body_show;

  QPixmap *pic_head;
  QPixmap *pic_left_arm;
  QPixmap *pic_rifht_arm;
  QPixmap *pic_body;

 protected:
  void enterEvent(QEvent *event) override { emit Hover_in(); }
  void leaveEvent(QEvent *event) override { emit Hover_out(); }

 signals:
  void Hover_in();
  void Hover_out();

 public slots:
};

#endif  // WELCOM_ROBOT_H
