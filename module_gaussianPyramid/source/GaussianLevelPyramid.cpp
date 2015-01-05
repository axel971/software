#include "GaussianLevelPyramid.h"
#include <iostream>

using namespace cv;
using namespace std;

GaussianLevelPyramid::GaussianLevelPyramid(): m_level(0), m_octave(0), m_sigma(0)
{}

GaussianLevelPyramid::GaussianLevelPyramid(cv::Mat image, int octave, int level, double sigma):m_image(image), m_octave(octave), m_level(level), m_sigma(sigma) 
{}

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
