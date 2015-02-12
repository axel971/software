#include "DOGDetector.hpp"

using namespace std;
using namespace cv;


DOGDetector::DOGDetector(Mat image, int octave, int level, double sigma) : SiftDetector(image, octave, level, sigma), m_dogPyramid(DOGPyramid(image, octave, level - 1, sigma))
{
  CHECK_INVARIANTS();

  //Creat limit of offset
  m_offsetLimit = Mat(3, 1, CV_64F);
  m_offsetLimit.at<double>(0) = 0.5;
  m_offsetLimit.at<double>(1) = 0.5;
  m_offsetLimit.at<double>(2) = 0.5;

  //Create m_k
  double k = pow(2, 1. / (level - 2));
  m_k = k;
  
}

void DOGDetector::operator()()
{
  CHECK_INVARIANTS();

  m_dogPyramid.build();  
  
  findExtrema();
  accurateKeyPointLocalization();
  
  
  CHECK_INVARIANTS();
}

bool DOGDetector::isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const
{
  double val;
  int middleX = 1, middleY = 1;
  Mat mat;

  //Get the value of processed pixel 
  val = roi2.at<double>(middleX, middleY);

  mat.push_back(roi1);
  mat.push_back(roi2);
  mat.push_back(roi3);
  
  for(int i = 0; i < mat.rows; ++i)
    for(int j = 0; j < mat.cols; ++j)
      if(val < mat.at<double>(i, j))
	return 0;
 
  return 1; 
}

bool DOGDetector::isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const
{
  double val;
  int middleX = 1, middleY = 1;
  Mat mat;

  //Get the value of processed pixel 
  val = roi2.at<double>(middleX, middleY);

  mat.push_back(roi1);
  mat.push_back(roi2);
  mat.push_back(roi3);
  
  for(int i = 0; i < mat.rows; ++i)
    for(int j = 0; j < mat.cols; ++j)
      if(val > mat.at<double>(i, j))
	return 0;
 
  return 1; 
};

bool DOGDetector::isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const
{
  bool isMaximum(false), isMinimum(false), isExtrema(false);

  isMaximum = isLocalMaximum(roi1, roi2, roi3);
  isMinimum = isLocalMinimum(roi1, roi2, roi3); 
 
  if(isMinimum + isMaximum == 1)
    return true;

  return false;
}


void DOGDetector::findExtremaAux(LevelPyramid const& level1, LevelPyramid const& level2, LevelPyramid const& level3) 
 {
   REQUIRE(level1.getOctave() == level2.getOctave(), "" );
   REQUIRE(level1.getOctave() == level3.getOctave(), "");
   REQUIRE(level1.getLevel() == level2.getLevel() - 1, "");
   REQUIRE(level3.getLevel() == level2.getLevel() + 1, "");
 
   Mat img1, img2, img3, roi1, roi2, roi3;
   int  sizeRoi(3);

   //Get images
   img1 = level1.getImage();
   img2 = level2.getImage();
   img3 = level3.getImage();

   for(int i = DOG_IMG_BORDER; i < img1.rows - DOG_IMG_BORDER; ++i)
     for(int j =  DOG_IMG_BORDER; j < img1.cols - DOG_IMG_BORDER; ++j) 
       {
	 //Construct the roi
	 roi1 = img1(Rect(j - 1, i - 1, sizeRoi, sizeRoi));
	 roi2 = img2(Rect(j - 1, i - 1, sizeRoi, sizeRoi));
	 roi3 = img3(Rect(j - 1, i - 1, sizeRoi, sizeRoi));
	
	 double val = roi2.at<double>(1, 1);

	 if(abs(val) < INTENSITY_THRESHOLD)
	   continue;

	 if(isLocalExtrema(roi1, roi2, roi3))
	   m_features.push_back(Feature(i, j, level2.getSigma(), 0, level2.getOctave(), level2.getLevel())); 
       }//end for 
 
}

void DOGDetector::findExtrema()
{
  REQUIRE(m_dogPyramid.isBuild(), "");

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
  REQUIRE(feature.getLevel() < DOG_LEVEL, "" );

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
  REQUIRE(feature.getLevel() < DOG_LEVEL, "" );

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

  REQUIRE(m_dogPyramid.isBuild(), "");
  REQUIRE(feature.getLevel() < DOG_LEVEL, "");
  REQUIRE(feature.getLevel() > 0, "");

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
  REQUIRE(feature.getRow() < m_image.rows/ pow(2, feature.getOctave()), "");
  REQUIRE(feature.getCol() < m_image.cols/ pow(2, feature.getOctave()), "");

  feature.setRow(feature.getRow() + offset.at<double>(0));
  feature.setCol(feature.getCol() + offset.at<double>(1));
  
  if(isDiscretize)
    {
      double sigma = m_dogPyramid.getSigma(feature.getOctave(), feature.getLevel());     

      feature.setLevel(feature.getLevel() + offset.at<double>(2));
      feature.setSigma(sigma * pow(m_k, offset.at<double>(2))) ;
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
      level >= DOG_LEVEL ||
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
