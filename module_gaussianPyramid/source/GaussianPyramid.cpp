#include "GaussianPyramid.h"

using namespace cv;
using namespace std;

GaussianPyramid::GaussianPyramid(){};

GaussianPyramid::GaussianPyramid(cv::Mat image, int octave, int level, double sigma0, double k) : m_image(image), m_level(level), m_octave(octave),m_sigma0(sigma0), m_k(k)
{
  //dynamic data allocation for the pyramid
  m_data.resize(octave*level);
} 


cv::Mat GaussianPyramid::getLevelImage(int i, int j)
{
  return m_data[i*m_level+ j].getImage();
}

double GaussianPyramid::getLevelSigma( int i, int j)
{
  return m_data[i*m_level+j].getSigma();
}

void GaussianPyramid::setImage(Mat image)
{
  m_image = image;
}

void GaussianPyramid::setOctave(int octave)
{
  m_octave = octave;
}

void GaussianPyramid::setLevel(int level)
{ m_level = level;
}

void GaussianPyramid::setSigma0(double sigma0)
{
  m_sigma0 = sigma0;
}

void GaussianPyramid::setK(double k)
{
  m_k =k;
}

void GaussianPyramid::build()
{
  int index = 0;
  double aSigma[m_level]; //array to keep the different values of sigma

  for(int i = 0; i< m_level; ++i) //compute the sigma
    aSigma[i] = pow(m_k,i)*m_sigma0;

  //create the first levelPyramide
  m_data[0].build(m_image, m_sigma0, 0, 0);

  // constuction of the other pyramide levels
  for(int i = 0; i < m_octave; ++i)
    for(int j = 0; j < m_level; ++j)
      {
	if(i == 0 && j == 0)
	  continue;
	else
	  {
	    m_data[index+1].build(m_data[index].getImage(), aSigma[j], i, j);
	    index++;
	  }
      }
}


