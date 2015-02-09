#include "TestDOGDetector.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION (TestDOGDetector);

using namespace cv;
using namespace std;


void TestDOGDetector::setUp()
{
  // m_dogDetector = DOGDetector();
}

void TestDOGDetector::tearUp()
{}

void TestDOGDetector::executionTest()
{
  Mat image = imread("../../data/lena.jpg", CV_LOAD_IMAGE_COLOR);
  int level = 5, octave = 3;
  double sigma = 1.6;

  //Initialisation step
  DOGDetector detector (image, octave, level, sigma);
  
  //Exercice step
  detector();

  //Check step
  CPPUNIT_ASSERT(detector.getNumbersFeatures() > 0);
}


void TestDOGDetector::twiceExecutionTest()
{
 Mat image = imread("../../data/lena.jpg", CV_LOAD_IMAGE_COLOR);
  int level = 5, octave = 3;
  double sigma = 1.6;

  //Initialisation step
  DOGDetector detector (image, octave, level, sigma);
  
  //Exercice step
  detector();
  int n1 = detector.getNumbersFeatures();

  detector();
  int n2 = detector.getNumbersFeatures();

  //Check test
  CPPUNIT_ASSERT_EQUAL(n1, n2);
}

void TestDOGDetector::limitCaseTest()
{
  Mat image = Mat::ones(512, 512, CV_8UC3);

  int level = 5, octave = 3;
  double sigma = 1.6;

  //Initialisation step
  DOGDetector detector (image, octave, level, sigma);
  
  //Exercice step
  detector();

  //Check step
  CPPUNIT_ASSERT_EQUAL(0, detector.getNumbersFeatures());
}
