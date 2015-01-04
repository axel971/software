#include <QApplication>
#include <QtWidgets>
#include "Controller.h"


int main(int argc, char** argv)
{

  QApplication app(argc,argv);

  Controller controller;
  controller.showView();

  return app.exec();
}
