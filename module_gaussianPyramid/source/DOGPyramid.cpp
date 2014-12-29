#include "DOGPyramid.h"

using namespace cv;
using namespace std;

DOGPyramid::DOGPyramid(){};

DOGPyramid::DOGPyramid(cv::Mat image, int octave, int level, double k, double sigma0): GaussianPyramid(image, octave, level, k, sigma0), m_gaussianPyramid(image, octave, level+1, k, sigma0)
{}

void DOGPyramid::build()
{
  m_gaussianPyramid.build();
  Mat im1, im2;
  
  for(int i = 0; i < m_octave; ++i)
    for(int j = 0; j < m_level; ++j)
      {
	m_gaussianPyramid.getLevelImage(i, j+1).convertTo(im1,CV_64FC1);
	m_gaussianPyramid.getLevelImage(i, j).convertTo(im2, CV_64FC1);
	m_data[i*m_level+j].build(im1-im2, 1, i, j);
      }
  
}

