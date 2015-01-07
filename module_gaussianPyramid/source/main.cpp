#include "DOGPyramid.hpp"
#include <iostream>


using namespace std;
using namespace cv;

main(int argc, char* argv[])
{

  Mat image;

  image = imread("racoon.jpg", CV_LOAD_IMAGE_COLOR);

  //construct pyramide
  // GaussianPyramid pyramid(image, 3, 5, sqrt(2), 1.6);  
  //pyramid.build();

  DOGPyramid dogPyramid(image, 3, 4, sqrt(2), 1.6);
  dogPyramid.build();
  
  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  
  for(int i = 0; i < 3; ++i)
    for(int j= 0; j < 4; ++j)
      {
	imshow( "Display window", dogPyramid.getLevelImage(i,j)); // Show our image inside it.
	waitKey(0);   
      }
 
  return 0;

}
