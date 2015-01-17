#include "TestSift.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION (TestSift);

using namespace cv;
using namespace std;



void TestSift::setUp()
{
  m_sift = Sift();
}

void TestSift::tearUp()
{}

void TestSift::findExtremaBorderInfConditionTest()
{
  Sift sift;
  GaussianLevelPyramid level1, level2, level3;
  vector<Feature> features;
  int row(4), col(4);

  //Initialisation step
  level1 = GaussianLevelPyramid(Mat::zeros(row, col, CV_64F), 0, 1, 0.);
  level2 = GaussianLevelPyramid(Mat::zeros(row, col, CV_64F), 0, 2, 0.);
  level3 = GaussianLevelPyramid(Mat::zeros(row, col, CV_64F), 0, 3, 0.);

  //Exercice step
  features = sift.findExtremaAux(level1, level2, level3);

  //Check step
  CPPUNIT_ASSERT_EQUAL(true, features.empty()); 
}


void TestSift::findExtremaBorderSupConditionTest()
{
  Sift sift;
  GaussianLevelPyramid level1, level2, level3;
  vector<Feature> features;
  int row(4), col(4);
 
  //Initialisation step
  level1 = GaussianLevelPyramid(Mat::ones(row, col, CV_64F), 0, 1, 0.);
  level2 = GaussianLevelPyramid(Mat::ones(row, col, CV_64F), 0, 2, 0.);
  level3 = GaussianLevelPyramid(Mat::ones(row, col, CV_64F), 0, 3, 0.);

  //Exercice step
  features = sift.findExtremaAux(level1, level2, level3);

  //Check step
  CPPUNIT_ASSERT_EQUAL(true, features.empty()); 
}

void TestSift::findExtremaLevel2isMaximaTest()
{
  Sift sift;
  GaussianLevelPyramid level1, level2, level3;
  vector<Feature> features;
  Mat img1, img2, img3;
  int iMax = 2, jMax = 2;

  //Initialisation step
  img1 = Mat::zeros(4, 4, CV_64F);
  img2 = Mat::zeros(4, 4, CV_64F);
  img3 = Mat::zeros(4, 4, CV_64F); 

  img2.at<double>(iMax, jMax) = 1;
 
  level1 = GaussianLevelPyramid(img1, 0, 1, 0.);
  level2 = GaussianLevelPyramid(img2, 0, 2, 0.);
  level3 = GaussianLevelPyramid(img3, 0, 3, 0.);

  //Exercice step
  features = sift.findExtremaAux(level1, level2, level3);

  //Check step
  CPPUNIT_ASSERT_EQUAL(false, features.empty());
  CPPUNIT_ASSERT_EQUAL(iMax, features[0].getX());
  CPPUNIT_ASSERT_EQUAL(jMax, features[0].getY()); 
 }

void TestSift::findExtremaLevel2isMinimaTest()
{
  Sift sift;
  GaussianLevelPyramid level1, level2, level3;
  vector<Feature> features;
  Mat img1, img2, img3;
  int iMax = 2, jMax = 2;

  //Initialisation step
  img1 = Mat::zeros(4, 4, CV_64F);
  img2 = Mat::zeros(4, 4, CV_64F);
  img3 = Mat::zeros(4, 4, CV_64F); 

  img2.at<double>(iMax, jMax) = -1;
 
  level1 = GaussianLevelPyramid(img1, 0, 1, 0.);
  level2 = GaussianLevelPyramid(img2, 0, 2, 0.);
  level3 = GaussianLevelPyramid(img3, 0, 3, 0.);

  //Exercice step
  features = sift.findExtremaAux(level1, level2, level3);

  //Check step
  CPPUNIT_ASSERT_EQUAL(false, features.empty());
  CPPUNIT_ASSERT_EQUAL(iMax, features[0].getX());
  CPPUNIT_ASSERT_EQUAL(jMax, features[0].getY()); 
 }

void TestSift::findExtremaIsFalseTest()
{
  Sift sift;
  GaussianLevelPyramid level1, level2, level3;
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

  level1 = GaussianLevelPyramid(img1, 0, 1, 0.);
  level2 = GaussianLevelPyramid(img2, 0, 2, 0.);
  level3 = GaussianLevelPyramid(img3, 0, 3, 0.);

  //Exercice step
  features = sift.findExtremaAux(level1, level2, level3);

  //Check step
  CPPUNIT_ASSERT_EQUAL(true, features.empty());
}
