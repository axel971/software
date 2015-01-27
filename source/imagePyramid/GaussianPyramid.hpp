#ifndef GaussianPyramid_hpp
#define GaussianPyramid_hpp

#include <vector>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "Pyramid.hpp"

class GaussianPyramid : public Pyramid
{

protected :
  double m_sigma;
  double m_k;
   
public :

  GaussianPyramid(cv::Mat image, int octave, int level, double sigma, double k);
  GaussianPyramid();
  
  double getSigma(int i, int j);
  
 
  virtual void build();

};

#endif 
