#ifndef DOGDETECTOR_H
#define DOGDETECTOR_H

#include "Feature.hpp"
#include "../imagePyramid/DOGPyramid.hpp"
#include "../imagePyramid/GaussianPyramid.hpp"
#include <vector>
#include "../contract/contract.hpp"

class DOGDetector
{

private :
  cv::Mat m_image;
  int m_level;
  int m_octave;
  double m_k;
  double m_sigma;
  std::vector<Feature> m_features;
  DOGPyramid m_dogPyramid;

public:

  //Constructeur
  DOGDetector(cv::Mat image, int octave, int level, double k, double sigma);
  
  //Define invariant
  BEGIN_INVARIANT_BLOCK(DOGDetector) 
  INVARIANT(!m_image.empty(), "Image is empty");
  INVARIANT(m_level > 0, "Level must be superior at zero");
  INVARIANT(m_octave > 0, "Octave must be superior at zero");
  INVARIANT(m_sigma > 0, "Sigma must be superior at zero");
  INVARIANT(m_features.size() >= 0, "Number feature must be positif");
  END_INVARIANT_BLOCK


  std::vector<Feature> getFeatures();
  int getNumbersFeatures();

  void operator()();
  void findExtrema();
  void findExtremaAux(LevelPyramid const& level1, LevelPyramid const& level2, LevelPyramid const& level3);
  void locateExtrema();

private : //private methods
  bool isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3);
  bool isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3);
  bool isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3);
  cv::Mat computeDelta(Feature const& feature);
  cv::Mat computeHessian(int row, int col, cv::Mat const& im1, cv::Mat const& im2, cv::Mat const& im3)const ;
  cv::Mat computeGradian(int row, int col, cv::Mat const& im1, cv::Mat const& im2, cv::Mat const& im3)const;
  bool isSupHalfOfStep(cv::Mat delta) const;
  cv::Mat delataConvertToImageFrame(cv::Mat delta) const;
 
};

#endif
