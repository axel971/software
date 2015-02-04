#include "DOGPyramid.hpp"

using namespace cv;
using namespace std;

DOGPyramid::DOGPyramid(){}

DOGPyramid::~DOGPyramid(){}

DOGPyramid::DOGPyramid(cv::Mat image, int octave, int level, double sigma, double k): Pyramid(image, octave, level), m_sigma(sigma), m_k(k)
{}

double DOGPyramid::getSigma(int i, int j)
{
  return get(i, j).getSigma();
}

void DOGPyramid::build()
{
  GaussianPyramid gaussianPyramid(m_image, m_octave, m_level + 1, m_sigma, m_k); 
  Mat im1, im2;

 
  gaussianPyramid.build();

  for(int i = 0; i < m_octave; ++i)
    for(int j = 0; j < m_levelInside; ++j)
      {

	//convert the image in gray scale image
	cvtColor(gaussianPyramid.getImage(i, j + 1), im1, CV_BGR2GRAY);
	cvtColor(gaussianPyramid.getImage(i, j), im2, CV_BGR2GRAY);

	//convert the images in double precision
	im1.convertTo(im1, CV_64F);
	im2.convertTo(im2, CV_64F);
	Mat dog = im1 - im2;
    
	
	//Normalize dog inside [|0,1|]
	double min, max;
	minMaxLoc(dog, &min);

	dog -= min;
	minMaxLoc(dog, 0, &max);

	dog /= max;

	/*
	namedWindow( "Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow( "Display window", dog );                   // Show our image inside it.
	waitKey(0);
	*/

	//Create the level
	LevelPyramid level(dog, i, j, gaussianPyramid.getSigma(i, j));
	set(level, i, j);
      }

  m_isBuild = true;
  
  ENSURE(getImage(0, 0).type() == CV_64F, "The images inside the DOG pyramid must be a double");
}

