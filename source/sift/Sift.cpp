#include "Sift.hpp"

using namespace std;
using namespace cv;


Sift::Sift() : m_k(0), m_level(0), m_octave(0), m_sigma(0)
{}

Sift::Sift(Mat image, int octave, int level, double k, double sigma): m_image(image), m_level(level), m_octave(octave), m_sigma(sigma), m_k(k), m_dogPyramid(DOGPyramid(image, octave, level, k, sigma))
{}

bool Sift::isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3, int i, int j)
{
  bool isMaximum = false;
  double val, maxRoi1, maxRoi2, maxRoi3;
  Mat mask;
    
  //Check the argument of the function
  assert((!roi1.empty()) && (!roi2.empty()) && (!roi3.empty()));
  assert(roi1.size() == roi2.size() && roi2.size() == roi3.size());

  //Get the value of processed pixel 
  val = roi2.at<double>(i, j);

  //Construct the mask
  mask = Mat::ones(roi1.rows, roi1.cols, CV_8UC1);
  mask.at<uchar>(i, j) = 0;
  
  //Find the maximum inside the ROI
  minMaxLoc(roi1, 0, &maxRoi1);
  minMaxLoc(roi2, 0, &maxRoi2, 0, 0, mask);
  minMaxLoc(roi3, 0, &maxRoi3);

  //Compare this maxima with the value of processed pixel
  if(val > maxRoi1 && val > maxRoi2 && val > maxRoi3)
    isMaximum = true;

   return isMaximum;
}

bool Sift::isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3, int i, int j)
{
  bool isMinimum = false;
  double val, minRoi1, minRoi2, minRoi3;
  Mat mask;

  //Check the argument of the function
  assert((!roi1.empty()) && (!roi2.empty()) && (!roi3.empty()));
  assert(roi1.size() == roi2.size() && roi2.size() == roi3.size());

  //Get the value of processed pixel 
  val = roi2.at<double>(i, j);

  //Construct the mask
  mask = Mat::ones(roi1.rows, roi1.cols, CV_8UC1);
  mask.at<uchar>(i, j) = 0;
  
  //Find the maximum inside the ROI
  minMaxLoc(roi1, &minRoi1);
  minMaxLoc(roi2, &minRoi2, 0, 0, 0, mask);
  minMaxLoc(roi3, &minRoi3);

  //Compare this maxima with the value of processed pixel
  if(val < minRoi1 && val < minRoi2 && val < minRoi3)
    isMinimum = true;

   return isMinimum;
};

bool Sift::isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3, int i, int j)
{
  bool isMaximum(false), isMinimum(false);

  isMaximum = isLocalMaximum(roi1, roi2, roi3, i, j);
  isMinimum = isLocalMinimum(roi1, roi2, roi3, i, j);
   
  return (isMinimum || isMaximum) ;
}


vector<Feature> Sift::findExtremaAux(GaussianLevelPyramid const& level1, GaussianLevelPyramid const& level2, GaussianLevelPyramid const& level3)
 {
   vector<Feature> features;
   bool isExtrema(false);
   Mat img1, img2, img3, roi1, roi2, roi3;
   int centerPixelI(1), centerPixelJ(1), sizeRoi(3);

   //Initialisation
   img1 = level1.getImage();
   img2 = level2.getImage();
   img3 = level3.getImage();

   //Check the argument of the function
   assert((!img1.empty()) && (!img2.empty()) && (!img3.empty()));
   assert(img1.size() == img2.size() && img2.size() == img3.size());
   assert(img2.rows >= sizeRoi && img2.cols >= sizeRoi);

     for(int i = 1; i < img1.rows - 1; ++i)
       for(int j = 1; j < img1.cols - 1; ++j) 
	 {
	   //Construct the roi
	   roi1 = img1(Rect(j-1, i-1, sizeRoi, sizeRoi));
	   roi2 = img2(Rect(j-1, i-1, sizeRoi, sizeRoi));
	   roi3 = img3(Rect(j-1, i-1, sizeRoi, sizeRoi));
	   
	   //Find if the current pixel is an extrema
	   isExtrema = isLocalExtrema(roi1, roi2, roi3, centerPixelI, centerPixelJ);
	   
	   if(isExtrema)
	     features.push_back(Feature(i, j, level2.getSigma(), 0)); 
	 }// end for
 
   return features; 
 }
