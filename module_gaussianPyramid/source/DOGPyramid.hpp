#ifndef DOGPyramid_hpp
#define DOGPyramid_hpp

#include "GaussianPyramid.hpp"


class DOGPyramid : public GaussianPyramid
{

 private :
  GaussianPyramid m_gaussianPyramid;
   
 public :

  DOGPyramid();
  DOGPyramid(cv::Mat image, int octave, int level, double k, double sigma0);

  virtual void build();

};

#endif 
