#include "LevelPyramide.h"
#include <iostream>

using namespace cv;
using namespace std;

LevelPyramide::LevelPyramide():m_level(0), m_sigma(0), m_octave(0)
{}

void LevelPyramide::build(cv::Mat currentImage, double currentSigma, int currentOctave, int currentLevel)
{
  Mat resImage;

  if(currentLevel ==  0 && currentOctave != 0) // create the octave
    resize(currentImage,resImage, Size(), 0.5, 0.5); //downsample the image
  else 
    GaussianBlur(currentImage, resImage, Size(), currentSigma, currentSigma, BORDER_REPLICATE); 
 
  
  m_image = resImage;
  m_sigma = currentSigma;
  m_level = currentLevel;
  m_octave = currentOctave;

}

void LevelPyramide::setImage(cv::Mat image)
{
  m_image = image;
}

cv::Mat LevelPyramide::getImage()
{
  return m_image;
}


double LevelPyramide::getSigma()
{
  return m_sigma;
}


int LevelPyramide::getLevel()
{
  return m_level;
}


int LevelPyramide::getOctave()
{
  return m_octave;
}
