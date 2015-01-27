#include "LevelPyramid.hpp"
#include <iostream>

using namespace cv;
using namespace std;

LevelPyramid::LevelPyramid(): m_level(0), m_octave(0), m_sigma(0)
{}

LevelPyramid::LevelPyramid(cv::Mat image, int octave, int level, double sigma) : m_image(image), m_octave(octave), m_level(level), m_sigma(sigma)
{}

cv::Mat const& LevelPyramid::getImage() const 
{
  return m_image;
}


int const& LevelPyramid::getLevel() const
{
  return m_level;
}


int const& LevelPyramid::getOctave() const
{
  return m_octave;
}

double const& LevelPyramid::getSigma() const
{
  return m_sigma;
}
