#ifndef PYRAMID_HPP
#define PYRAMID_HPP
 
#include <vector>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "LevelPyramid.hpp"

class Pyramid
{

protected :

  int m_level;
  int m_levelInside;
  int m_octave;
  cv::Mat m_image; 
  std::vector<LevelPyramid> m_data;
  bool m_isBuild;

public :

  Pyramid(cv::Mat image, int octave, int level);
  Pyramid();
  virtual ~Pyramid();

  cv::Mat getImage(int i, int j);
  LevelPyramid get(int i, int j);
  int getLevel();
  int getOctave();

  virtual void build() = 0; 

  bool isBuild();
  
protected : //protected method

  void set(LevelPyramid level, int i, int j);

};

#endif
