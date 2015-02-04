
#include "Pyramid.hpp"

using namespace cv;
using namespace std;

Pyramid::Pyramid(){} 

Pyramid::Pyramid(cv::Mat image, int octave, int level) : m_image(image), m_level(level), m_levelInside(level + 1), m_octave(octave), m_isBuild(0)
{ 
  for(int i = 0; i < m_levelInside * m_octave; ++i)
    m_data.push_back(LevelPyramid());
} 

Pyramid::~Pyramid(){}

LevelPyramid Pyramid::get(int i, int j)
{
  return m_data[i * m_levelInside + j];
}


void Pyramid::set(LevelPyramid level, int i, int j)
{
  m_data[i * m_levelInside + j] = level;
}

cv::Mat Pyramid::getImage(int i, int j)
{
  return get(i, j).getImage();
}

int Pyramid::getLevel()
{
  return m_level;
}

int Pyramid::getOctave()
{
  return m_octave;
}

bool Pyramid::isBuild()
{
  return m_isBuild;
}
