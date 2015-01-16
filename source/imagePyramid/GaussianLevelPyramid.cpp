#include "GaussianLevelPyramid.hpp"
#include <iostream>

using namespace cv;
using namespace std;

GaussianLevelPyramid::GaussianLevelPyramid(): m_level(0), m_octave(0), m_sigma(0)
{}

GaussianLevelPyramid::GaussianLevelPyramid(cv::Mat image, int octave, int level, double sigma):m_image(image), m_octave(octave), m_level(level), m_sigma(sigma) 
{}

cv::Mat const& GaussianLevelPyramid::getImage() const 
{
  return m_image;
}


double const& GaussianLevelPyramid::getSigma() const
{
  return m_sigma;
}


int const& GaussianLevelPyramid::getLevel() const
{
  return m_level;
}


int const& GaussianLevelPyramid::getOctave() const
{
  return m_octave;
}
