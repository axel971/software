#ifndef GaussianLevelPyramid_hpp
#define GaussianLevelPyramid_hpp

/**
 * \file GaussianLevelPyramid.hpp
 * \brief Gaussian or DOG element pyramid
 * \author Axel Largent
 *\version 0.1
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LevelPyramid.hpp"

class GaussianLevelPyramid : public LevelPyramid
{

  /**
   *\class GaussianLevelPyramid
   *\brief Class whitch represent an element of Gaussian or DOG pryramid
   */
 
private:
  double m_sigma; /*!< scale */

public:
  /**
   *\brief Constructeur by default of the class GaussianLevelPyramid
   */
  GaussianLevelPyramid();

  /**
   * \brief Constructeur
   *
   *\param image : image of the pyramid at the current octave and level
   *\param octave : current octave of the pyramid
   *\param level : current level of the pyramid
   *\param sigma : current scale of the pyramid	
   */
  GaussianLevelPyramid(cv::Mat image, int octave, int level, double sigma);

  /**
   * \brief Get the scale
   * \return the scale 
   */
  double const& getSigma() const;

};

#endif 
