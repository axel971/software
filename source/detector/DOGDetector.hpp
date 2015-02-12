#ifndef DOGDETECTOR_H
#define DOGDETECTOR_H

#define INTENSITY_THRESHOLD 0.70
#define DOG_MAX_INTERP_STEPS 5
#define DOG_IMG_BORDER 1
#define R_THRESHOLD 10
#define DOG_IMAGE_SCALE_1 m_dogPyramid.getImage(feature.getOctave(), feature.getLevel() - 1)
#define DOG_IMAGE_SCALE_2 m_dogPyramid.getImage(feature.getOctave(), feature.getLevel())
#define DOG_IMAGE_SCALE_3 m_dogPyramid.getImage(feature.getOctave(), feature.getLevel() + 1)
#define DOG_LEVEL m_level - 1

#include "SiftDetector.hpp"
#include "../imagePyramid/DOGPyramid.hpp"
#include "../imagePyramid/GaussianPyramid.hpp"
#include "../contract/contract.hpp"

class DOGDetector : public SiftDetector
{

private :

  DOGPyramid m_dogPyramid;
  cv::Mat m_offsetLimit;
  double m_k;

public :

  //Constructeur
  DOGDetector(cv::Mat image, int octave, int level, double sigma);
  
  //Define invariant
  BEGIN_INVARIANT_BLOCK(DOGDetector) 
  INVARIANT(!m_image.empty(), "Image is empty");
  INVARIANT(m_level > 0, "Level must be superior at zero");
  INVARIANT(m_octave > 0, "Octave must be superior at zero");
  INVARIANT(m_sigma > 0, "Sigma must be superior at zero");
  INVARIANT(m_features.size() >= 0, "Number feature must be positif");
  END_INVARIANT_BLOCK


  virtual  void operator()();

private : //private methods
  bool isLocalMaximum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const;
  bool isLocalMinimum(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const;
  bool isLocalExtrema(cv::Mat const& roi1, cv::Mat const& roi2, cv::Mat const& roi3) const;
  void findExtrema();
  void findExtremaAux(LevelPyramid const& level1, LevelPyramid const& level2, LevelPyramid const& level3);
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
  void accurateKeyPointLocalization();
};

#endif
