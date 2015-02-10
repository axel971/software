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
  image = imread("../data/lena.jpg", CV_LOAD_IMAGE_COLOR);
  
  DOGDetector detector(image, 3, 5, 1.6);
  detector();
    
  vector<Feature> features = detector.getFeaturesScaled();
  
  for(int i = 0; i < features.size(); ++i)
    {
      Point center(features[i].getCol(), features[i].getRow());
      circle(image, center, 2, Scalar(0, 0, 255), -1);
    }
  
  namedWindow("Display window", WINDOW_AUTOSIZE );
  imshow("Display window", image );               
  waitKey(0);   


  cout << detector.getNumbersFeatures() << endl;

  return 0;
  
}
