#include "GaussianPyramid.hpp"
using namespace cv;
using namespace std;

GaussianPyramid::GaussianPyramid(){};

GaussianPyramid::GaussianPyramid(cv::Mat image, int octave, int level, double sigma0, double k) : m_image(image), m_level(level), m_octave(octave),m_sigma0(sigma0), m_k(k), m_data(vector< GaussianLevelPyramid>(octave * (level + 1)) )
{ 
} 


cv::Mat GaussianPyramid::getImage(int i, int j)
{
  return m_data[i * (m_level + 1) + j].getImage();
}

double GaussianPyramid::getSigma( int i, int j)
{
  return m_data[i * (m_level + 1) + j].getSigma();
}


void GaussianPyramid::build()
{
  int index = 0;
  double sigmas[m_level + 1];
  double scale;

  //create the first element of the first octave
  m_data[0] = GaussianLevelPyramid(m_image, 0, 0, m_sigma0);

  //create the array of sigma
  for(int i = 0; i < m_level + 1; ++i)
    sigmas[i] = pow(m_k,i) * m_sigma0;
  
 // constuction of pyramid
  for(int i = 0; i < m_octave; ++i)
    for(int j = 0; j < m_level + 1; ++j)
      {
	if(i == 0 && j == 0)
	  continue;

	else if (j != 0)
	  {
	    //construct levels of this octave	    
	    Mat out;
	    scale = m_data[i * (m_level + 1)].getSigma() * pow(m_k, j); 
 	    GaussianBlur(m_data[i * (m_level + 1)].getImage(), out, Size(0,0), sigmas[j]);
	    m_data[i * (m_level + 1) + j] = GaussianLevelPyramid(out, 0, 0, scale);
	  }
	else
	  {
	    //construct the octave i
	    Mat out;
	    scale = m_data[(i - 1) * (m_level + 1) + 2].getSigma();
	    resize(m_data[(i - 1) * (m_level + 1) + 2].getImage(), out, Size(0,0), 0.5, 0.5);
	    m_data[i * (m_level + 1)] = GaussianLevelPyramid(out, 0, 0, scale);
	  }
      }
}


