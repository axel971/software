#ifndef SIFTDETECTOR_HPP
#define SIFTDETECTOR_HPP

#include <vector>
#include <opencv2/core/core.hpp>
#include "Feature.hpp"


class SiftDetector
{
protected :

  cv::Mat m_image;
  int m_level;
  int m_octave;
  double m_sigma;
  std::vector<Feature> m_features;

public :

  SiftDetector(cv::Mat image, int octave, int level, double sigma);

  std::vector<Feature> getFeatures();
  std::vector<Feature> getFeaturesScaled();
  int getNumbersFeatures();

  virtual void operator()() = 0;
};

#endif
