#ifndef SIFT_H
#define SIFT_H

#include "Feature.hpp"
#include "../imagePyramid/DOGPyramid.hpp"
#include <vector>
#include <cassert>

class Sift
{

private :
  cv::Mat m_image;
  int m_level;
  int m_octave;
  double m_k;
  double m_sigma;
  std::vector<Feature> m_features;
  DOGPyramid m_dogPyramid;

public:

  Sift();
  Sift(cv::Mat image, int octave, int level, double k, double sigma);
  
  void operator()();
  void findExtrema();
  std::vector<Feature> findExtremaAux(GaussianLevelPyramid const& level1, GaussianLevelPyramid const& level2, GaussianLevelPyramid const& level3);

private : //private methods
  bool isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3, int i, int j);
  bool isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3, int i, int j);
  bool isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3, int i, int j);

};

#endif
