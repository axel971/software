#include <QApplication>
#include <QtWidgets>
#include "mvc/Controller.h"
#include "detector/DOGDetector.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  /*
  QApplication app(argc,argv);

  Controller controller;
  controller.showView();

  return app.exec();
  */

  Mat image;
  image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);

  DOGDetector DOGDetector(image, 3, 5, sqrt(2), 1.6);
  DOGDetector();
  cout << DOGDetector.getNumbersFeatures() << endl;

  //construct pyramide
  //GaussianPyramid pyramid(image, 3, 5, sqrt(2), 1.6);  
  //pyramid.build();
 

  return 0;

}
