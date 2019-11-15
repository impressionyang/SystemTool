#include <QApplication>
#include "circle_progres_bar.h"
#include "system_tool.h"
#include "welcom_robot.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SystemTool w;
  w.show();

  return a.exec();
}
