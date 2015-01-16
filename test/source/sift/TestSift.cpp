#include "TestSift.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION (TestSift);

using namespace cv;
using namespace std;


void TestSift::isExtremaTest()
{
  
  Sift sift;
  Mat img1, img2, img3;
  int i, j;
  bool isExtrema = false;

  //Construct Test 1
  img1 = Mat::zeros(3, 3, CV_64F);//variable initialisation
  img2 = Mat::zeros(3, 3, CV_64F);
  img3 = Mat::zeros(3, 3, CV_64F); 
  i = 2; j = 2;
  img2.at<double>(i, j) = -1.; // put the extrema in this image (test 1)

  isExtrema = sift.isLocalExtrema(img1, img2, img3, i, j); //process

  CPPUNIT_ASSERT_EQUAL(isExtrema, true); //check isExtrema result
  
 
  //Construct Test 2
  img1 = Mat::zeros(3, 3, CV_64F);
  img2 = Mat::zeros(3, 3, CV_64F);
  img3 = Mat::zeros(3, 3, CV_64F); 
  i = 2; j = 2;
  img2.at<double>(i, j) = -1.; // put the extrema in this image
  img2.at<double>(0,0) = -1.;
 
  isExtrema = sift.isLocalExtrema(img1, img2, img3, i, j); //process

  CPPUNIT_ASSERT_EQUAL(isExtrema, false); //check isExtrema result
  
}


void TestSift::setUp()
{}

void TestSift::tearUp()
{}
