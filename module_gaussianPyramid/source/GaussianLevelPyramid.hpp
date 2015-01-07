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

class GaussianLevelPyramid {

  /**
   *\class GaussianLevelPyramid
   *\brief Class whitch represent an element of Gaussian or DOG pryramid
   */
 
private:
  int m_level; /*!< level current of the pyramid */
  int m_octave; /*!< current octave of the pyramid */
  cv::Mat m_image; /*!< image at the current octave and level of the pyramid */
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
   * \brief Get the image
   * \return the image
   */
  cv::Mat getImage();

  /**
   * \brief Get the scale
   * \return the scale 
   */
  double getSigma();

  /**
   * \brief Get the curent level
   * \return the level 
   */					
  int getLevel();

  /**
   * \brief Get the current octave
   * \return the octave 
   */					
  int getOctave();

};

#endif 
