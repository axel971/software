#include <QApplication>
#include <QtWidgets>
#include "mvc/Controller.h"
#include "sift/Sift.hpp"

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
  image = imread("racoon.jpg", CV_LOAD_IMAGE_COLOR);

  Sift sift(image, 3, 5, sqrt(2), 1.6);
  sift();
  cout << sift.getNumbersFeatures() << endl;

  //construct pyramide
  //GaussianPyramid pyramid(image, 3, 5, sqrt(2), 1.6);  
  //pyramid.build();
 

  return 0;

}
