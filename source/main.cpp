#include <QApplication>
#include <QtWidgets>
#include "mvc/Controller.h"
#include "sift/Sift.hpp"

int main(int argc, char** argv)
{

  QApplication app(argc,argv);

  Controller controller;
  controller.showView();

  return app.exec();
}
