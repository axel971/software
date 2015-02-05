#ifndef DOGPyramid_hpp
#define DOGPyramid_hpp

#include "Pyramid.hpp"
#include "GaussianPyramid.hpp"
#include "../contract/contract.hpp"

class DOGPyramid : public Pyramid
{

 private :
  double m_sigma;
  double m_k;
   
 public :

  DOGPyramid();
  DOGPyramid(cv::Mat image, int octave, int level, double sigma);
  ~DOGPyramid();

  double getSigma(int i, int j);

  virtual void build();

};

#endif 
