#include "GaussianLevelPyramid.h"
#include <iostream>

using namespace cv;
using namespace std;

GaussianLevelPyramid::GaussianLevelPyramid():m_level(0), m_sigma(0), m_octave(0)
{}

void GaussianLevelPyramid::build(cv::Mat image, double sigma, int octave, int level)
{
  Mat resImage;

  if(level ==  0 && octave != 0) 
    resize(image,resImage, Size(), 0.5, 0.5); //downsample the image
  else 
    GaussianBlur(image, resImage, Size(), sigma, sigma, BORDER_REPLICATE); //apply the filter  
 
  
  m_image = resImage;
  m_sigma = sigma;
  m_level = level;
  m_octave = octave;

}

void GaussianLevelPyramid::setImage(cv::Mat image)
{
  m_image = image;
}

cv::Mat GaussianLevelPyramid::getImage()
{
  return m_image;
}


double GaussianLevelPyramid::getSigma()
{
  return m_sigma;
}


int GaussianLevelPyramid::getLevel()
{
  return m_level;
}


int GaussianLevelPyramid::getOctave()
{
  return m_octave;
}
