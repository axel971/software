#ifndef DOGDETECTOR_H
#define DOGDETECTOR_H

#define DOG_MAX_INTERP_STEPS 5
#define DOG_IMG_BORDER 1
#define R_THRESHOLD 10
#define DOG_IMAGE_SCALE_1 m_dogPyramid.getImage(feature.getOctave(), feature.getLevel() - 1)
#define DOG_IMAGE_SCALE_2 m_dogPyramid.getImage(feature.getOctave(), feature.getLevel())
#define DOG_IMAGE_SCALE_3 m_dogPyramid.getImage(feature.getOctave(), feature.getLevel() + 1)

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
  cv::Mat m_offsetLimit;

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
  std::vector<Feature> getFeaturesScaled();
  int getNumbersFeatures();

  void operator()();
  void findExtrema();
  void findExtremaAux(LevelPyramid const& level1, LevelPyramid const& level2, LevelPyramid const& level3);
  void accurateKeyPointLocalization();

private : //private methods
  bool isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3);
  bool isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3);
  bool isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3);
  cv::Mat computeOffset(Feature const& feature, double *pixelValue = 0, cv::Mat *grad = 0);
  cv::Mat computeHessian(Feature const&  feature);
  cv::Mat computeGradian(Feature const& feature);
  bool featureMustChange(cv::Mat offset) const;
  cv::Mat discretizeOffset(cv::Mat const& offset) const;
  void addOffset(Feature& feature, cv::Mat const& offset, bool isDiscretize = false);
  bool checkImageBorder(Feature const& feature) ;
  double offsetContrastReponse(double value, cv::Mat& gradian, cv::Mat& offset) const;
  double traceH(Feature const& feature);
  double detH(Feature const& feature);
};

#endif