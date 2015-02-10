#include "TestDOGPyramid.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestDOGPyramid);

using namespace cv;
using namespace std;


void TestDOGPyramid::setUp()
{}

void TestDOGPyramid::tearUp()
{}

void TestDOGPyramid::pyramidSizeTest()
{
  int octave = 3, level = 5;
  double sigma = 1.6;
  Mat image;

  //Initialisation step
  image = imread("../../data/lena.jpg", CV_LOAD_IMAGE_COLOR);
  
  DOGPyramid pyramid(image, octave, level, sigma);
 
  //Exercice step
  pyramid.build();
  
  //Check step
  for(int i = 0; i < octave - 1; ++i)
    {
      double row = pyramid.getImage(i, level).rows;
      double rowAfter = pyramid.getImage(i + 1, level).rows;

      CPPUNIT_ASSERT_EQUAL(row, rowAfter * 2); 
    }
}

void TestDOGPyramid::eltPyramidDifferentTest()
{
  int octave = 3, level = 5;
  double sigma = 1.6;
  Mat image;

  //Initialisation step
  image = imread("../../data/lena.jpg", CV_LOAD_IMAGE_COLOR);
  
  DOGPyramid pyramid(image, octave, level, sigma);
 
  //Exercice step
  pyramid.build();
  for(int i = 0; i < octave; ++i)
    for(int j = 0; j < level; ++j)
      {
	Mat image = pyramid.getImage(i, j);
	Mat imageAfter = pyramid.getImage(i, j + 1);
 
	double res = norm(image - imageAfter, NORM_L1);
	
	CPPUNIT_ASSERT(res > DIFF_EPS);
     }
}

void TestDOGPyramid::twiceExecutionTest()
{
  int octave = 3, level = 5;
  double sigma = 1.6;
  Mat image;

  //Initialisation step
  image = imread("../../data/lena.jpg", CV_LOAD_IMAGE_COLOR);
  
  DOGPyramid pyramid(image, octave, level, sigma);
  
  //Exercice step
  pyramid.build();
  Mat image1 = pyramid.getImage(2, 2);
  
  pyramid.build();
  Mat image2 = pyramid.getImage(2, 2);
  	
  //Check step
  double res = norm(image1 - image2, NORM_L1);
	
  CPPUNIT_ASSERT(res < DIFF_EPS);
}
