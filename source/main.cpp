#include <QApplication>
#include <QtWidgets>
#include "mvc/Controller/Controller.h"
#include "detector/DOGDetector.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  
  QApplication app(argc,argv);

  Controller controller;
  controller.showView();

  return app.exec();  
  

  //  Mat image = imread("../data/lena.jpg", CV_LOAD_IMAGE_COLOR);

  // DOGDetector detector(image, 3, 5, 1.6);
 
  //detector(); 
}
