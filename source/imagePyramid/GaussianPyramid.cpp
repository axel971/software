#include "GaussianPyramid.hpp"

using namespace cv;
using namespace std;

GaussianPyramid::GaussianPyramid() : m_sigma(0), m_k(0)
{} 

GaussianPyramid::GaussianPyramid(cv::Mat image, int octave, int level, double sigma, double k) : Pyramid(image, octave, level), m_sigma(sigma), m_k(k) 
{ } 

double GaussianPyramid::getSigma(int i, int j)
{
  return get(i, j).getSigma();
}

void GaussianPyramid::build()
{
  int i2Sigma = 2; 
  double sigmas[m_levelInside];
  double scale;

  //Create the first element of octave zero
  set(LevelPyramid(m_image, 0, 0, m_sigma), 0, 0);
 
  //Create the array of sigma
  for(int i = 0; i < m_levelInside; ++i)
    sigmas[i] = pow(m_k, i) * m_sigma;
  
 //Constuction of pyramid
  for(int i = 0; i < m_octave; ++i)
    for(int j = 0; j < m_levelInside; ++j)
      {
	if(i == 0 && j == 0)
	  continue;

	else if (j != 0)
	  {
	    //Construct levels of this octave	    
	    Mat out;
	    scale = getSigma(i, 0) * pow(m_k, j); 
 	    GaussianBlur(getImage(i, 0), out, Size(0, 0), sigmas[j]);
	    set(LevelPyramid(out, i, j, scale), i, j);
	  }
	else
	  {
	    //Construct the ith octave
	    Mat out;
	    scale = getSigma(i - 1, i2Sigma);
	    resize(getImage(i - 1, i2Sigma), out, Size(0, 0), 0.5, 0.5);
	    set(LevelPyramid(out, i, j, scale), i, j);
	  }
      }//end for

  m_isBuild == true;
}


