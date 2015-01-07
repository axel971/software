#include "GaussianPyramid.hpp"
using namespace cv;
using namespace std;

GaussianPyramid::GaussianPyramid(){};

GaussianPyramid::GaussianPyramid(cv::Mat image, int octave, int level, double sigma0, double k) : m_image(image), m_level(level), m_octave(octave),m_sigma0(sigma0), m_k(k), m_data(vector< GaussianLevelPyramid>(octave*level))
{
} 


cv::Mat GaussianPyramid::getLevelImage(int i, int j)
{
  return m_data[i*m_level+ j].getImage();
}

double GaussianPyramid::getLevelSigma( int i, int j)
{
  return m_data[i*m_level+j].getSigma();
}


void GaussianPyramid::build()
{
  int index = 0;
  double aSigma[m_level]; //array to keep the different values of sigma

  for(int i = 0; i < m_level; ++i) //compute the sigma
    aSigma[i] = pow(m_k, i) * m_sigma0;

  //create the first element of the first octave
  Mat imgDst;
  GaussianBlur(m_image, imgDst, Size(0,0), m_sigma0);
  m_data[0] = GaussianLevelPyramid(imgDst, 0, 0, m_sigma0);

 // constuction of pyramid
  for(int i = 0; i < m_octave; ++i)
    for(int j = 0; j < m_level; ++j)
      {
	if(i == 0 && j == 0)
	  continue;

	else if (j != 0)
	  {
	    //construct levels of this octave	    
	    Mat out;
 	    GaussianBlur(m_data[i * m_level].getImage(), out, Size(0,0), aSigma[j]);
	    m_data[i * m_level + j] = GaussianLevelPyramid(out, 0, 0, aSigma[j]);
	  }
	else
	  {
	    //construct the octave i
	    Mat out;
	    resize(m_data[ (i - 1) * m_level + 2].getImage(), out, Size(0,0), 0.5, 0.5);
	    m_data[i * m_level + j] = GaussianLevelPyramid(out, 0, 0, aSigma[j]);

	  }
      }
}


