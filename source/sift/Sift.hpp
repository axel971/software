#ifndef SIFT_H
#define SIFT_H

#include "Feature.hpp"
#include "DOGPyramid.hpp"
#include <vector>

class Sift
{

private :
  int m_level;
  int m_octave;
  double m_sigma;
  vector<Feature> features;
  DOGPyramid dogPyramid;
  
public:
  Sift();
  Sift(int octave, int level, int sigma);
  
  void operator()();
  void localExtrema();
  vector<Feature> localExtremaAux(cv::Mat const& img1, cv::Mat const& img2, cv::Mat const& img3);

private : //private methods
  bool isLocalExtrema(cv::Mat const& roiImg1, cv::Mat const& roiImg2, cv::Mat const& roiImg3);

};

#endif
