#ifndef LevelPyramide_h
#define LevelPyramide_h

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class LevelPyramide {

 public:

  LevelPyramide();

  void build(cv::Mat image, double sigma, int octave, int level); 
  
  void setImage(cv::Mat image); //To Do : Delete this function here and the class diagramm
  cv::Mat getImage();
  double getSigma();
  int getLevel();
  int getOctave();


  
 private:
  int m_level;
  int m_octave; //To Do : Modify the class diagramm
  cv::Mat m_image;
  double m_sigma;

};

#endif // LevelPyramide_h
