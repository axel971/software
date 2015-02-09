#include "DOGDetector.hpp"

using namespace std;
using namespace cv;


DOGDetector::DOGDetector(Mat image, int octave, int level, double sigma): m_image(image), m_level(level), m_octave(octave), m_sigma(sigma), m_dogPyramid(DOGPyramid(image, octave, level - 1, sigma))
{
  CHECK_INVARIANTS();

  //Creat limit of offset
  m_offsetLimit = Mat(3, 1, CV_64F);
  m_offsetLimit.at<double>(0) = 0.5;
  m_offsetLimit.at<double>(1) = 0.5;
  m_offsetLimit.at<double>(2) = 0.5;
  
}

vector<Feature> DOGDetector::getFeatures()
 {
   return m_features;
 }

vector<Feature> DOGDetector::getFeaturesScaled()
{
  vector<Feature> features(m_features.size());

  for(int i = 0; i < m_features.size(); ++i)
    {
      features[i] = m_features[i];

      features[i].setRow(features[i].getRow() * pow(2, features[i].getOctave()));
      features[i].setCol(features[i].getCol() * pow(2, features[i].getOctave()));
    }

  return features;
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
  accurateKeyPointLocalization();

  /*
  vector<Feature> features = getFeaturesScaled();

  for(int i = 0; i < m_features.size(); ++i)
    {
      Point center(features[i].getCol(), features[i].getRow());
      circle(m_image, center, 2, Scalar(0, 0, 255), -1);
    }
  
  namedWindow( "Display window", WINDOW_AUTOSIZE );
  imshow( "Display window", m_image );               
  waitKey(0);   
  */

  CHECK_INVARIANTS();
}

bool DOGDetector::isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const
{
  REQUIRE(roi1.cols == 3 && roi2.cols == 3 && roi3.cols == 3, "ROI must have a size 3*3");
  REQUIRE(roi1.size() == roi2.size() && roi2.size() == roi3.size(), "ROI must be have the same size");
   
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
 

  return isMaximum;
}

bool DOGDetector::isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const
{
  REQUIRE(roi1.cols == 3 && roi2.cols == 3 && roi3.cols == 3, "ROI must have a size 3*3");
  REQUIRE(roi1.size() == roi2.size() && roi2.size() == roi3.size(), "ROI must be have the same size");
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
  
   return isMinimum;
};

bool DOGDetector::isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const
{
  REQUIRE(roi1.cols == 3 && roi2.cols == 3 && roi3.cols == 3, "ROI must have a size 3*3");
  REQUIRE(roi1.size() == roi2.size() && roi2.size() == roi3.size(), "ROI must be have the same size");  
  
  bool isMaximum(false), isMinimum(false), isExtrema(false);

  isMaximum = isLocalMaximum(roi1, roi2, roi3);
  isMinimum = isLocalMinimum(roi1, roi2, roi3); 
  isExtrema = isMinimum || isMaximum;

  ENSURE(isExtrema == isMaximum || isExtrema == isMinimum, "iSExtrema is not valid");

  return isExtrema;
}


void DOGDetector::findExtremaAux(LevelPyramid const& level1, LevelPyramid const& level2, LevelPyramid const& level3) 
 {
   REQUIRE(level1.getOctave() == level2.getOctave() && level1.getOctave() == level3.getOctave(), "the element must be in the same octave");
   REQUIRE(level1.getLevel() == level2.getLevel() - 1 && level3.getLevel() == level2.getLevel() + 1, "The level is in the same order");
 
   bool isExtrema(false);
   Mat img1, img2, img3, roi1, roi2, roi3;
   int  sizeRoi(3);

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
 
}

void DOGDetector::findExtrema()
{
  REQUIRE(m_dogPyramid.isBuild(), "DOG Pyramid must be processed");

  if(m_features.size() > 0)
    m_features.clear();

  for(int i = 0; i < m_dogPyramid.getOctave(); ++i)
    for(int j = 1; j < m_dogPyramid.getLevel(); ++j)
      findExtremaAux(m_dogPyramid.get(i, j - 1), m_dogPyramid.get(i, j), m_dogPyramid.get(i, j + 1));
}

Mat DOGDetector::computeHessian(Feature const& feature)
{
  REQUIRE(feature.getRow() > 0, "Row don't be in the border");
  REQUIRE(feature.getCol() > 0, "Col don't be in the border");
  REQUIRE(feature.getLevel() > 0, "Level must be superior at zero");
  REQUIRE(feature.getRow() < m_image.rows / pow(2, feature.getOctave()), "");
  REQUIRE(feature.getCol() < m_image.cols / pow(2, feature.getOctave()), "");
  REQUIRE(feature.getLevel() < m_level + 1, "" );

  double dRowRow, dRowCol, dRowSigma, dColCol, dColSigma, dSigmaSigma ;
  int row = feature.getRow(), col = feature.getCol();
  Mat im1 = DOG_IMAGE_SCALE_1;
  Mat im2 = DOG_IMAGE_SCALE_2;
  Mat im3 = DOG_IMAGE_SCALE_3;
  Mat hessian(3, 3, CV_64F);

  //Compute the partial second derivate
  dRowRow = (im2.at<double>(row + 1, col) - 2 * im2.at<double>(row, col)
             + im2.at<double>(row - 1, col));

  dColCol = (im2.at<double>(row, col + 1) - 2 * im2.at<double>(row, col) 
             + im2.at<double>(row, col -1));

  dSigmaSigma = (im3.at<double>(row, col) - 2 * im2.at<double>(row, col)
		 + im1.at<double>(row, col));

  dRowCol = 0.25 * (im2.at<double>(row + 1, col + 1) - im2.at<double>(row + 1, col - 1)
		    - im2.at<double>(row - 1, col + 1) + im2.at<double>(row - 1, col - 1));
  
  dRowSigma = 0.25 * (im3.at<double>(row + 1, col) - im1.at<double>(row + 1, col)
		      - im3.at<double>(row - 1, col) + im1.at<double>(row - 1, col));

  dColSigma = 0.25 * (im3.at<double>(row, col + 1) - im1.at<double>(row, col + 1)
		      - im3.at<double>(row, col -1) + im1.at<double>(row, col -1));

  //Construct the hessian matrix
  hessian.at<double>(0, 0) = dRowRow;
  hessian.at<double>(0, 1) = dRowCol;
  hessian.at<double>(0, 2) = dRowSigma;
  hessian.at<double>(1, 0) = dRowCol;
  hessian.at<double>(1, 1) = dColCol;
  hessian.at<double>(1, 2) = dColSigma;
  hessian.at<double>(2, 0) = dRowSigma;
  hessian.at<double>(2, 1) = dColSigma;
  hessian.at<double>(2, 2) = dSigmaSigma;
  
 
  ENSURE(hessian.rows == 3 && hessian.cols == 3, "");
  
  return hessian;
}

Mat DOGDetector::computeGradian(Feature const& feature)
{
  REQUIRE(feature.getRow() > 0, "Row don't be in the border");
  REQUIRE(feature.getCol() > 0, "Col don't be in the border");
  REQUIRE(feature.getLevel() > 0, "Level must be superior at zero");
  REQUIRE(feature.getRow() < m_image.rows / pow(2, feature.getOctave()), "");
  REQUIRE(feature.getCol() < m_image.cols / pow(2, feature.getOctave()), "");
  REQUIRE(feature.getLevel() < m_level + 1, "" );

  int row = feature.getRow(), col = feature.getCol();
  Mat im1 = DOG_IMAGE_SCALE_1;
  Mat im2 = DOG_IMAGE_SCALE_2;
  Mat im3 = DOG_IMAGE_SCALE_3;
  Mat gradian(3, 1, CV_64F);

  //Compute gradian
  gradian.at<double>(0) = 0.5 *(im2.at<double>(row + 1, col) - im2.at<double>(row - 1, col));
  gradian.at<double>(1) = 0.5 *(im2.at<double>(row, col + 1) - im2.at<double>(row, col -1));
  gradian.at<double>(2) = 0.5 *(im3.at<double>(row, col) - im1.at<double>(row, col));

  ENSURE(gradian.rows == 3 && gradian.cols == 1, "Gradian must be have the good dimension");
  
  return gradian;
}

Mat DOGDetector::computeOffset(Feature const& feature, double *pixelValue, Mat *grad) 
{
  REQUIRE(m_dogPyramid.isBuild(), "DOG Pyramid must be processed");
  CHECK_INVARIANTS();

  Mat offset, gradian(3, 1, CV_64F), hessian(3, 3, CV_64F);
  Mat im1, im2, im3;
 
  //Compute the gradian
  gradian = computeGradian(feature);

  //Compute the hessian
  hessian = computeHessian(feature);
  
  //Compute the offset
  offset = -1 * hessian.inv(DECOMP_SVD) * gradian;

  if(grad != 0)
    *grad = gradian;

  if(pixelValue != 0)
    *pixelValue = m_dogPyramid.getImage(feature.getOctave(), 
					feature.getLevel()).at<double>(feature.getRow(),
								       feature.getCol());

  ENSURE(offset.rows == 3 && offset.cols == 1, "Offset must be have the good dimension");
  CHECK_INVARIANTS();

  return offset;
}

bool DOGDetector::featureMustChange(cv::Mat offset) const
{
  REQUIRE(offset.rows == 3 && offset.cols == 1, "Offset must have the size 3 * 1 ");

  bool res = false;

  if(sum(abs(offset))[0] > sum(m_offsetLimit)[0])
    res = true;

  return res;
}

cv::Mat DOGDetector::discretizeOffset(cv::Mat const& offset) const
{
  REQUIRE(offset.rows == 3 && offset.cols == 1, "");

  Mat res(3, 1, CV_64F);

  //Discretize the offset
  res.at<double>(0) = round(offset.at<double>(0));
  res.at<double>(1) = round(offset.at<double>(1));
  res.at<double>(2) = round(offset.at<double>(2));

  return res;

}

void DOGDetector::addOffset(Feature& feature, Mat const& offset, bool isDiscretize)
{
  REQUIRE(feature.getRow() > 0 && feature.getCol() > 0, "");
  REQUIRE(feature.getRow() < m_image.rows/ pow(2, feature.getOctave()) && feature.getCol() < m_image.cols/ pow(2, feature.getOctave()), "The feature must be stay inside the image");

  feature.setRow(feature.getRow() + offset.at<double>(0));
  feature.setCol(feature.getCol() + offset.at<double>(1));
  
  if(isDiscretize)
    {
      feature.setLevel(feature.getLevel() + offset.at<double>(2));
      double sigma = m_dogPyramid.getSigma(feature.getOctave(), feature.getLevel());
      feature.setSigma(sigma) ;
    }
}


bool DOGDetector::checkImageBorder(Feature const& feature) 
{
  bool res = false;
  int level = feature.getLevel(), 
    octave = feature.getOctave(),
    row = feature.getRow(),
    col = feature.getCol(),
    imgRow = m_image.rows / pow(2, feature.getOctave()),
    imgCol = m_image.cols / pow(2, feature.getOctave());

  if( level < 1  ||
      level > m_level  ||
      row < DOG_IMG_BORDER ||
      col < DOG_IMG_BORDER ||
      row >= imgRow - DOG_IMG_BORDER  ||
      col >= imgCol - DOG_IMG_BORDER )
    res = true;

  return res;
}

double DOGDetector::offsetContrastReponse(double value, Mat& gradian, Mat& offset) const
{
  REQUIRE(offset.rows == 3 && offset.cols == 1, "Offset must have the size 3 * 1");
  REQUIRE(gradian.rows == 3 && gradian.cols == 1, "Offset must have the size 3 * 1");

  double res;
  Mat tmp(1, 1, CV_64F);

  tmp = abs(value + (0.5 * gradian.t() * offset));
  res = tmp.at<double>(0);

  return res;
}

double DOGDetector::traceH(Feature const& feature)
{
  double dxx, dyy;
  int row = feature.getRow(), col = feature.getCol();
  Mat im1 = DOG_IMAGE_SCALE_1;
  Mat im2 = DOG_IMAGE_SCALE_2;
  Mat im3 = DOG_IMAGE_SCALE_3;
 
  dxx = (im2.at<double>(row + 1, col) - 2 * im2.at<double>(row, col)
             + im2.at<double>(row - 1, col));

  dyy = (im2.at<double>(row, col + 1) - 2 * im2.at<double>(row, col) 
             + im2.at<double>(row, col -1));

  return dxx + dyy;
}

double DOGDetector::detH(Feature const& feature)
{
  double dxx, dyy, dxy;
  int row = feature.getRow(), col = feature.getCol();
  Mat im1 = DOG_IMAGE_SCALE_1;
  Mat im2 = DOG_IMAGE_SCALE_2;
  Mat im3 = DOG_IMAGE_SCALE_3;
  
  //Compute the partial second derivate
  dxx = (im2.at<double>(row + 1, col) - 2 * im2.at<double>(row, col)
             + im2.at<double>(row - 1, col));

  dyy = (im2.at<double>(row, col + 1) - 2 * im2.at<double>(row, col) 
             + im2.at<double>(row, col -1));

  dxy = 0.25 * (im2.at<double>(row + 1, col + 1) - im2.at<double>(row + 1, col - 1)
		    - im2.at<double>(row - 1, col + 1) + im2.at<double>(row - 1, col - 1));

  return dxx*dyy - dxy*dxy;
}


void DOGDetector::accurateKeyPointLocalization()
{
  CHECK_INVARIANTS();
  REQUIRE(m_features.size() > 0, "");

  vector<Feature>::iterator  itFeature = m_features.begin();


  while(itFeature != m_features.end())
    {
      Mat offset, gradian;
      double value;
      int i = 0;

      //Compute the offset and add it of current feature coordinates 
      while(i < DOG_MAX_INTERP_STEPS)
	{
	  offset = computeOffset(*itFeature, &value, &gradian);
	  
	  if(!featureMustChange(offset))
	    break;
	  
	  addOffset(*itFeature, discretizeOffset(offset), true);
	  
	  if(checkImageBorder(*itFeature)) //Delete the feature
	    {
	      itFeature = m_features.erase(itFeature);
	      break;
	    }

	  i++;
	}//end while
      
      if(i == DOG_MAX_INTERP_STEPS) //You must assure the convergence of algorithme 
	{
	  itFeature = m_features.erase(itFeature);
	  continue;
	}
  

      //Filter low contrast responses
      if(abs(offsetContrastReponse(value, gradian, offset)) < 0.03)
	{
	  itFeature = m_features.erase(itFeature);
	  continue;
	}

      //Eliminate edge responses
      double tr = traceH(*itFeature),
	det = detH(*itFeature);

      if(det < 0 ||
	  tr * tr / det > (R_THRESHOLD + 1) * (R_THRESHOLD + 1) / R_THRESHOLD) 
	{
	  itFeature = m_features.erase(itFeature);
	  continue;
	}

      addOffset(*itFeature, offset);

      itFeature++;
    }//end while
 
  CHECK_INVARIANTS();
}
