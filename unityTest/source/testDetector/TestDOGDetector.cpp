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

void TestDOGDetector::findExtremaBorderInfConditionTest()
{
  DOGDetector detector(Mat::zeros(16, 16, CV_64F), 3, 5, 1.6, sqrt(2));
  LevelPyramid level1, level2, level3;
  vector<Feature> features;
  int row(4), col(4);

  //Initialisation step
  level1 = LevelPyramid(Mat::zeros(row, col, CV_64F), 0, 1, 0.);
  level2 = LevelPyramid(Mat::zeros(row, col, CV_64F), 0, 2, 0.);
  level3 = LevelPyramid(Mat::zeros(row, col, CV_64F), 0, 3, 0.);

  //Exercice step
  detector.findExtremaAux(level1, level2, level3);
  features = detector.getFeatures();

  //Check step
  CPPUNIT_ASSERT_EQUAL(true, features.empty()); 
}


void TestDOGDetector::findExtremaBorderSupConditionTest()
{
  DOGDetector detector(Mat::zeros(16, 16, CV_64F), 3, 5, 1.6, sqrt(2));
  LevelPyramid level1, level2, level3;
  vector<Feature> features;
  int row(4), col(4);
 
  //Initialisation step
  level1 = LevelPyramid(Mat::ones(row, col, CV_64F), 0, 1, 0.);
  level2 = LevelPyramid(Mat::ones(row, col, CV_64F), 0, 2, 0.);
  level3 = LevelPyramid(Mat::ones(row, col, CV_64F), 0, 3, 0.);

  //Exercice step
  detector.findExtremaAux(level1, level2, level3);
  features = detector.getFeatures();

  //Check step
  CPPUNIT_ASSERT_EQUAL(true, features.empty()); 
}

void TestDOGDetector::findExtremaLevel2isMaximaTest()
{
  DOGDetector detector(Mat::zeros(16, 16, CV_64F), 3, 5, 1.6, sqrt(2));
  LevelPyramid level1, level2, level3;
  vector<Feature> features;
  Mat img1, img2, img3;
  int iMax = 2, jMax = 2;

  //Initialisation step
  img1 = Mat::zeros(4, 4, CV_64F);
  img2 = Mat::zeros(4, 4, CV_64F);
  img3 = Mat::zeros(4, 4, CV_64F); 

  img2.at<double>(iMax, jMax) = 0.01;
 
  level1 = LevelPyramid(img1, 0, 1, 0.);
  level2 = LevelPyramid(img2, 0, 2, 0.);
  level3 = LevelPyramid(img3, 0, 3, 0.);

  //Exercice step
  detector.findExtremaAux(level1, level2, level3);
  features = detector.getFeatures();

  //Check step
  CPPUNIT_ASSERT_EQUAL(false, features.empty());
  CPPUNIT_ASSERT_EQUAL(iMax, features[0].getRow());
  CPPUNIT_ASSERT_EQUAL(jMax, features[0].getCol()); 
 }

void TestDOGDetector::findExtremaLevel2isMinimaTest()
{
  DOGDetector detector(Mat::zeros(16, 16, CV_64F), 3, 5, 1.6, sqrt(2));
  LevelPyramid level1, level2, level3;
  vector<Feature> features;
  Mat img1, img2, img3;
  int iMax = 2, jMax = 2;

  //Initialisation step
  img1 = Mat::zeros(4, 4, CV_64F);
  img2 = Mat::zeros(4, 4, CV_64F);
  img3 = Mat::zeros(4, 4, CV_64F); 

  img2.at<double>(iMax, jMax) = -0.1;
 
  level1 = LevelPyramid(img1, 0, 1, 0.);
  level2 = LevelPyramid(img2, 0, 2, 0.);
  level3 = LevelPyramid(img3, 0, 3, 0.);

  //Exercice step
  detector.findExtremaAux(level1, level2, level3);
  features = detector.getFeatures();

  //Check step
  CPPUNIT_ASSERT_EQUAL(false, features.empty());
  CPPUNIT_ASSERT_EQUAL(iMax, features[0].getRow());
  CPPUNIT_ASSERT_EQUAL(jMax, features[0].getCol()); 
 }

void TestDOGDetector::findExtremaIsFalseTest()
{
  DOGDetector detector(Mat::zeros(16, 16, CV_64F), 3, 5, 1.6, sqrt(2));
  LevelPyramid level1, level2, level3;
  vector<Feature> features;
  Mat img1, img2, img3;
  int iMax = 2, jMax = 2;

  //Initialisation step
  img1 = Mat::zeros(4, 4, CV_64F);
  img2 = Mat::zeros(4, 4, CV_64F);
  img3 = Mat::zeros(4, 4, CV_64F); 

  img2.at<double>(iMax, jMax) = 1;
  img1.at<double>(iMax - 1, jMax - 1) = 1;
  img3.at<double>(iMax + 1, jMax + 1) = -1;

  level1 = LevelPyramid(img1, 0, 1, 0.);
  level2 = LevelPyramid(img2, 0, 2, 0.);
  level3 = LevelPyramid(img3, 0, 3, 0.);

  //Exercice step
  detector.findExtremaAux(level1, level2, level3);
  features = detector.getFeatures();

  //Check step
  CPPUNIT_ASSERT_EQUAL(true, features.empty());
}
