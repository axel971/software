#ifndef Pyramide_h
#define Pyramide_h

#include <vector>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "LevelPyramide.h"


class Pyramide {

 public :

  Pyramide(cv::Mat mainImage, int octave, int level, double sigma0, double k);

  cv::Mat  getImage(int i, int j);
  double getSigma(int i, int j);

  void build();


 private: 
    int m_level;
    int m_octave;
    double m_sigma0;
    double m_k;
    cv::Mat m_mainImage; 

 private:

    /**
     * @element-type LevelPyramide
     */
    std::vector< LevelPyramide > m_data;

  
};

#endif // Pyramide_h
