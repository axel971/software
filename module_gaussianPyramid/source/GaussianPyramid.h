#ifndef GaussianPyramid_h
#define GaussianPyramid_h

#include <vector>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "GaussianLevelPyramid.h"


class GaussianPyramid{

 public :

  GaussianPyramid(cv::Mat image, int octave, int level, double sigma0, double k);
  GaussianPyramid();

  cv::Mat  getLevelImage(int i, int j);
  double getLevelSigma(int i, int j);

  void build();


 protected: 
    int m_level;
    int m_octave;
    double m_sigma0;
    double m_k;
    cv::Mat m_image; 
    std::vector< GaussianLevelPyramid> m_data;

  
};

#endif 
