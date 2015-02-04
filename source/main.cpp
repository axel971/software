#include <QApplication>
#include <QtWidgets>
#include "mvc/Controller.h"
#include "detector/DOGDetector.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

  QApplication app(argc,argv);

  Controller controller;
  controller.showView();

  return app.exec();

}
