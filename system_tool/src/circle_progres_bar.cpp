#include "circle_progres_bar.h"

Circle_Progres_Bar::Circle_Progres_Bar(QSize size, QWidget *parent)
    : QWidget(parent) {
  this->setAttribute(Qt::WA_TranslucentBackground, true);
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                 Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint |
                 Qt::X11BypassWindowManagerHint | Qt::Tool);
  this->size = size;
  this->progress = 0;
  this->pen=new QPen(Qt::green, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

  QDesktopWidget *desktopWidget = QApplication::desktop();
  screenRect = desktopWidget->screenGeometry();

  progress_show_center = new QLabel("default");
  progress_show_center->setMaximumWidth(size.width()/2);
  //  progress_show_center->move(screenRect.width() / 2 - this->size.width() /
  //  2,
  //                             screenRect.height() / 2 - this->size.height() /
  //                             2);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addStretch();
  layout->addWidget(progress_show_center);
  layout->addStretch();

  setLayout(layout);
  resize(this->size);
  //  time_test = new QTimer();
  //  connect(time_test, &QTimer::timeout, this, [=]() {
  //    progress = (progress + 1) % 100;
  //    update();
  //    //    qDebug() << progress_show_center->text() + "  adding!";
  //  });
  //  time_test->start(50);

//  time=10;
//  QTimer *t=new QTimer(this);
//  connect(t,&QTimer::timeout,this,[=](){
//      qDebug()<<"time circle add"<< set<<endl;
//     set=set+step;
//     this->update();
//  });
//  t->start(time);
//  this->set_pen(QColor(255,0,0),5);
}

void Circle_Progres_Bar::set_progress(double progress) {
//  QPropertyAnimation a(this,"progress");
  this->set=lastprogress;
  lastprogress=this->progress;
  this->progress = progress;
//  a.setStartValue(lastprogress);
//  a.setEndValue(progress);
//  a.start();
  update();
//  step=(lastprogress-progress)/(600/time);
//  qDebug()<<"step="<<step<<endl;

}

void Circle_Progres_Bar::set_pen(QColor color, int width=8){
    this->pen->setColor(color);
    this->pen->setWidth(width);
}

void Circle_Progres_Bar::set_progress_show_center(QString content) {
  this->progress_show_center->setText(content);
  QFont font;
  font.setBold(true);
  font.setPixelSize(this->size.height() / 5);
  this->progress_show_center->setFont(font);
}
void Circle_Progres_Bar::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  //  坐标系转换
  painter.setWindow(-width() / 2, height() / 2, width(), -height());

//  QPen pen;

//  pen.setStyle(Qt::SolidLine);
//  pen.setWidth(1);
//  pen.setBrush(Qt::black);
//  pen.setCapStyle(Qt::RoundCap);
//  pen.setJoinStyle(Qt::RoundJoin);
  //  painter.setPen(pen);

  //反走样
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(*this->pen);
  QRectF rectangle(
      QPoint(-this->size.width() / 2 + 10, -this->size.height() / 2 + 10),
      QSize(this->size.width() - 20,
            this->size.height() - 20));  //矩形
  int startAngle = 0 * 16;               //起始角度
  int spanAngle ;
//  = 3.6 * set * 16;   //跨越度数
  if(progress>=0){
      spanAngle = 3.6 * progress * 16;
  }else {

      spanAngle = 0;
    }
  painter.drawArc(rectangle, startAngle, spanAngle);
//  painter.setPen(
//      QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  //  painter.drawRect(rectangle);
  //画弧线时，角度被分成了十六分之一，就是说，要想为30度，就得是30*16。它有起始角度和跨度，还有位置矩形
}
