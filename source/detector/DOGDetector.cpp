#include "DOGDetector.hpp"

using namespace std;
using namespace cv;


DOGDetector::DOGDetector(Mat image, int octave, int level, double k, double sigma): m_image(image), m_level(level), m_octave(octave), m_sigma(sigma), m_k(k), m_dogPyramid(DOGPyramid(image, octave, level - 1, k, sigma))
{
  CHECK_INVARIANTS();
}

vector<Feature> DOGDetector::getFeatures()
 {
   return m_features;
 }

int DOGDetector::getNumbersFeatures()
{
  return m_features.size();
}

void DOGDetector::operator()()
{
  CHECK_INVARIANTS();

  m_dogPyramid.build();  
  
  findExtrema();
  locateExtrema();
  

  CHECK_INVARIANTS();
}

bool DOGDetector::isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3)
{
  REQUIRE(roi1.cols == 3 && roi2.cols == 3 && roi3.cols == 3, "ROI must have a size 3*3");
  REQUIRE(roi1.size() == roi2.size() && roi2.size() == roi3.size(), "ROI must be have the same size");
  CHECK_INVARIANTS();
  
  bool isMaximum = false;
  double val, maxRoi1, maxRoi2, maxRoi3;
  Mat mask;
  int middleX = 1, middleY = 1;

  //Get the value of processed pixel 
  val = roi2.at<double>(middleX, middleY);

  //Construct the mask
  mask = Mat::ones(roi1.rows, roi1.cols, CV_8UC1);
  mask.at<uchar>(middleX, middleY) = 0;
  
  //Find the maximum inside the ROI
  minMaxLoc(roi1, 0, &maxRoi1);
  minMaxLoc(roi2, 0, &maxRoi2, 0, 0, mask);
  minMaxLoc(roi3, 0, &maxRoi3);

  //Compare this maxima with the value of processed pixel
  if(val > maxRoi1 && val > maxRoi2 && val > maxRoi3)
    isMaximum = true;

  //To do : Think at better ENSURE
  ENSURE(mask.cols == 3 && mask.rows == 3, "The mask must have 3 * 3 size");
  ENSURE(isMaximum == true || isMaximum == false, "Output have to be binary");
  CHECK_INVARIANTS();

  return isMaximum;
}

bool DOGDetector::isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3)
{
  REQUIRE(roi1.cols == 3 && roi2.cols == 3 && roi3.cols == 3, "ROI must have a size 3*3");
  REQUIRE(roi1.size() == roi2.size() && roi2.size() == roi3.size(), "ROI must be have the same size");
  CHECK_INVARIANTS();
  
  bool isMinimum = false;
  double val, minRoi1, minRoi2, minRoi3;
  Mat mask;
  int middleX = 1, middleY = 1;
  
  //Get the value of processed pixel 
  val = roi2.at<double>(middleX, middleY);

  //Construct the mask
  mask = Mat::ones(roi1.rows, roi1.cols, CV_8UC1);
  mask.at<uchar>(middleX, middleY) = 0;
  
  //Find the maximum inside the ROI
  minMaxLoc(roi1, &minRoi1);
  minMaxLoc(roi2, &minRoi2, 0, 0, 0, mask);
  minMaxLoc(roi3, &minRoi3);

  //Compare this maxima with the value of processed pixel
  if(val < minRoi1 && val < minRoi2 && val < minRoi3)
    isMinimum = true;

  ENSURE(mask.cols == 3 && mask.rows == 3, "The mask must have 3 * 3 size");
  ENSURE(isMinimum == true || isMinimum == false, "Output have to be binary");
  CHECK_INVARIANTS();

   return isMinimum;
};

bool DOGDetector::isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3)
{
  REQUIRE(roi1.cols == 3 && roi2.cols == 3 && roi3.cols == 3, "ROI must have a size 3*3");
  REQUIRE(roi1.size() == roi2.size() && roi2.size() == roi3.size(), "ROI must be have the same size");  
  CHECK_INVARIANTS();
  
  bool isMaximum(false), isMinimum(false), isExtrema;

  isMaximum = isLocalMaximum(roi1, roi2, roi3);
  isMinimum = isLocalMinimum(roi1, roi2, roi3); 
  isExtrema = isMinimum || isMaximum;

  ENSURE(isExtrema == isMaximum || isExtrema == isMinimum, "iSExtrema is not valid");
  CHECK_INVARIANTS();

  return isExtrema;
}


void DOGDetector::findExtremaAux(LevelPyramid const& level1, LevelPyramid const& level2, LevelPyramid const& level3)
 {
   REQUIRE(level1.getOctave() == level2.getOctave() && level1.getOctave() == level3.getOctave(), "the element must be in the same octave");
   REQUIRE(level1.getLevel() == level2.getLevel() - 1 && level3.getLevel() == level2.getLevel() + 1, "The level is in the same order");
   CHECK_INVARIANTS();

   bool isExtrema(false);
   Mat img1, img2, img3, roi1, roi2, roi3;
   int  sizeRoi(3), countTest = m_features.size();

   //Get images
   img1 = level1.getImage();
   img2 = level2.getImage();
   img3 = level3.getImage();

   for(int i = 1; i < img1.rows - 1; ++i)
     for(int j = 1; j < img1.cols - 1; ++j) 
       {
	 //Construct the roi
	 roi1 = img1(Rect(j - 1, i - 1, sizeRoi, sizeRoi));
	 roi2 = img2(Rect(j - 1, i - 1, sizeRoi, sizeRoi));
	 roi3 = img3(Rect(j - 1, i - 1, sizeRoi, sizeRoi));
	   
	 //Find if the current pixel is an extrema
	 isExtrema = isLocalExtrema(roi1, roi2, roi3);
	 
	 if(isExtrema)
	   m_features.push_back(Feature(i, j, level2.getSigma(), 0, level2.getOctave(), level2.getLevel())); 
       }//end for 

   ENSURE(m_features.size() >= countTest, "The size of features array cannot decrease"); 
   CHECK_INVARIANTS();
}

void DOGDetector::findExtrema()
{
  REQUIRE(m_dogPyramid.isBuild(), "DOG Pyramid must be processed");

  for(int i = 0; i < m_dogPyramid.getOctave(); ++i)
    for(int j = 1; j < m_dogPyramid.getLevel(); ++j)
      findExtremaAux(m_dogPyramid.get(i, j - 1), m_dogPyramid.get(i, j), m_dogPyramid.get(i, j + 1));
}

Mat DOGDetector::computeHessian(int row, int col, Mat const& im1, Mat const& im2, Mat const& im3) const
{
  REQUIRE(im1.rows >= 3 && im1.cols >= 3, "Size of images must be superior or equal at 3");
  REQUIRE(im1.size() == im2.size() && im2.size() == im3.size(), "Dimension of images must be equal");
  REQUIRE(row > 0 && row < im1.rows, "Row don't be in the border");
  REQUIRE(col > 0 && col < im1.cols, "Col don't be in the border");
  
  Mat hessian(3, 3, CV_64F);
  double dRowRow, dRowCol, dRowSigma, dColRow, dColCol, dColSigma, dSigmaRow, dSigmaCol, dSigmaSigma ;

  //Compute the partial second derivate
  dRowRow = 0.25 * (im2.at<double>(row + 1, col) - 2 * im2.at<double>(row, col) + im2.at<double>(row - 1, col));

  dColCol = 0.25 * (im2.at<double>(row, col + 1) - 2 * im2.at<double>(row, col) + im2.at<double>(row, col -1));

  dSigmaSigma = 0.25 * (im3.at<double>(row, col) - 2 * im2.at<double>(row, col) + im1.at<double>(row, col));

  dRowCol = 0.25 * (im2.at<double>(row + 1, col + 1) - im2.at<double>(row + 1, col - 1) - im2.at<double>(row - 1, col + 1) + im2.at<double>(row - 1, col - 1));
  
  dRowSigma = 0.25 * (im3.at<double>(row + 1, col) - im1.at<double>(row + 1, col) - im3.at<double>(row - 1, col) + im1.at<double>(row - 1, col));

  dColRow = 0.25 * (im2.at<double>(row + 1, col + 1) - im2.at<double>(row - 1, col + 1) - im2.at<double>(row + 1, col - 1) + im2.at<double>(row - 1, col - 1)); 

  dColSigma = 0.25 * (im3.at<double>(row, col + 1) - im1.at<double>(row, col + 1) - im3.at<double>(row, col -1) + im1.at<double>(row, col -1));

  dSigmaRow = 0.25 * (im3.at<double>(row + 1, col) - im3.at<double>(row - 1, col) - im1.at<double>(row + 1, col) + im1.at<double>(row - 1, col));

  dSigmaCol = 0.25 * (im3.at<double>(row, col + 1) - im3.at<double>(row, col - 1) - im1.at<double>(row, col + 1) + im1.at<double>(row, col - 1));

  //Construct the hessian matrix
  hessian.at<double>(0, 0) = dRowRow; hessian.at<double>(0, 1) = dRowCol; hessian.at<double>(0, 2) = dRowSigma;
  hessian.at<double>(1, 0) = dColRow; hessian.at<double>(1, 1) = dColCol; hessian.at<double>(1, 2) = dColSigma;
  hessian.at<double>(2, 0) = dSigmaRow; hessian.at<double>(2, 1) = dSigmaCol; hessian.at<double>(2, 2) = dSigmaSigma;

  ENSURE(hessian.rows == 3 && hessian.cols == 3, "Hessian must be have the good dimension");
  
  return hessian;
}

Mat DOGDetector::computeGradian(int row, int col, cv::Mat const& im1, cv::Mat const& im2, cv::Mat const& im3) const
{
  REQUIRE(im1.rows >= 3 && im1.cols >= 3, "Size of images must be superior or equal at 3");
  REQUIRE(im1.size() == im2.size() && im2.size() == im3.size(), "Dimension of images must be equal");
  REQUIRE(row > 0 && row < im1.rows, "Row don't be in the border");
  REQUIRE(col > 0 && col < im1.cols, "Col don't be in the border");
  
  Mat gradian(3, 1, CV_64F);

  //Compute gradian
  gradian.at<double>(0) = 0.5 *(im2.at<double>(row + 1, col) - im2.at<double>(row - 1, col));
  gradian.at<double>(1) = 0.5 *(im2.at<double>(row, col + 1) - im2.at<double>(row, col -1));
  gradian.at<double>(2) = 0.5 *(im3.at<double>(row, col) - im1.at<double>(row, col));

  ENSURE(gradian.rows == 3 && gradian.cols == 1, "Gradian must be have the good dimension");
  
  return gradian;
}

Mat DOGDetector::computeDelta(Feature const& feature) 
{
  REQUIRE(feature.getRow() > 0 && feature.getRow() < m_image.rows, "Feature.row must be inside this definition field");
  REQUIRE(feature.getCol() > 0 && feature.getCol() < m_image.cols, "Feature.col must be inside this definition field");
  REQUIRE(m_dogPyramid.isBuild(), "DOG Pyramid must be processed");
  CHECK_INVARIANTS();

  Mat delta, gradian(3, 1, CV_64F), hessian(3, 3, CV_64F);
  Mat im1, im2, im3;
  int row = feature.getRow(), col = feature.getCol();

  //Get the images
  im1 = m_dogPyramid.getImage(feature.getOctave(), feature.getLevel() - 1);
  im2 = m_dogPyramid.getImage(feature.getOctave(), feature.getLevel());
  im3 = m_dogPyramid.getImage(feature.getOctave(), feature.getLevel() + 1);

  //Compute the gradian
  gradian = computeGradian(row, col, im1, im2,  im3);

  //Compute the hessian
  hessian = computeHessian(row, col, im1, im2, im3);
  
  //Compute the delta
  delta = - hessian.inv() * gradian;

  ENSURE(delta.rows == 3 && delta.cols == 1, "Delta must be have the good dimension");
  CHECK_INVARIANTS();

  return delta;
}

bool DOGDetector::isSupHalfOfStep(cv::Mat delta) const
{
  REQUIRE(delta.rows == 3 && delta.cols == 1, "Delta must have the size 3 * 1 ");

  bool isTrue = false;

  abs(delta);

  if(delta.at<double>(0) > 0.5)
    isTrue = true;

  else if(delta.at<double>(1) > 0.5)
    isTrue = true;

  else if(delta.at<double>(2) > m_k * m_sigma * 0.5)
    isTrue = true;
}

cv::Mat DOGDetector::delataConvertToImageFrame(cv::Mat delta) const
{
  REQUIRE(delta.rows == 3 && delta.cols == 1, "Delta must have the size 3 * 1 ");

  Mat res(3, 1, CV_64F), sup, inf, deltaBorder(3, 1, CV_64F);

  //Creat border
  deltaBorder.at<double>(0) = 0.5;
  deltaBorder.at<double>(1) = 0.5;
  deltaBorder.at<double>(2) = m_k * m_sigma * 0.5;

  //Binarize the delta
  sup = delta > deltaBorder;
  inf = delta < - 1 * deltaBorder;
  
  sup.convertTo(sup, CV_64F);
  inf.convertTo(inf, CV_64F); 
  inf *= -1;

  res = (sup + inf)/255;

  ENSURE(sum(res)[0] <= 3 && sum(res)[0] >= -3, "The convert delta must be have elements equal to  one or zero");
  
  return res;

}

void DOGDetector::locateExtrema()
{
  CHECK_INVARIANTS();

  for(int i = 0; i < m_features.size(); ++i)
    {
      Mat delta = computeDelta(m_features[i]);
      cout << isSupHalfOfStep(delta) << " " << delta << " " << delataConvertToImageFrame(delta) << endl;
    }

  CHECK_INVARIANTS();
}
