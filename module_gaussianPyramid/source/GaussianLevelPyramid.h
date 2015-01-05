#ifndef GaussianLevelPyramid_h
#define GaussianLevelPyramid_h

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class GaussianLevelPyramid {

 public:

  GaussianLevelPyramid();
  GaussianLevelPyramid(cv::Mat image, int octave, int level, double sigma);

  cv::Mat getImage();
  double getSigma();
  int getLevel();
  int getOctave();


  
 private:
  int m_level;
  int m_octave; 
  cv::Mat m_image;
  double m_sigma;

};

#endif // GaussianLevelPyramid_h
