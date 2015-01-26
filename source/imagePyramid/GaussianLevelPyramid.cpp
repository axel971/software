#include "GaussianLevelPyramid.hpp"
#include <iostream>

using namespace cv;
using namespace std;

GaussianLevelPyramid::GaussianLevelPyramid(): LevelPyramid(), m_sigma(0)
{}

GaussianLevelPyramid::GaussianLevelPyramid(cv::Mat image, int octave, int level, double sigma): LevelPyramid(image, octave, level), m_sigma(sigma) 
{}

double const& GaussianLevelPyramid::getSigma() const
{
  return m_sigma;
}




