#ifndef DOGPyramid_h
#define DOGPyramid_h

#include "GaussianPyramid.h"


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
