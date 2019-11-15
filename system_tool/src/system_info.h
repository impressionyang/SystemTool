#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H
#include <QProcess>
#include <QTextStream>
#include <QDebug>

class System_Info {
 public:
  explicit System_Info();
  double getcpu();
  double getmem();
  double getstor();
  void value_update();


 private:
  //    Double cpu
    double cpu;
    double mem;
    double stor;
    double encodecpu(QString);
    double encodemem(QString);
    double encodedf(QString);

    QList<int>* getMemNumberList(QString);
    QList<double>* getCPUNumberList(QString);
    QList<int>* getStorNumberList(QString);
};

#endif  // SYSTEM_INFO_H
