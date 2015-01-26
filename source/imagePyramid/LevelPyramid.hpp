#ifndef LEVELPYRAMID_HPP
#define LEVELPYRAMID_HPP


/**
 * \file LevelPyramid.hpp
 * \brief element of pyramid
 * \author Axel Largent
 *\version 0.1
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class LevelPyramid
{
  /**
   *\class LevelPyramid
   *\brief Class whitch represent an element of Pryramid
   */
 
protected :
  int m_level; /*!< level current of the pyramid */
  int m_octave; /*!< current octave of the pyramid */
  cv::Mat m_image; /*!< image at the current octave and level of the pyramid */

public :
  /**
   *\brief Constructeur by default of the class LevelPyramid
   */
  LevelPyramid();

  /**
   * \brief Constructeur
   *
   *\param image : image of the pyramid at the current octave and level
   *\param octave : current octave of the pyramid
   *\param level : current level of the pyramid
   */
  LevelPyramid(cv::Mat image, int octave, int level);

  /**
   * \brief Get the image
   * \return the image
   */
  cv::Mat const& getImage() const;

  /**
   * \brief Get the curent level
   * \return the level 
   */					
  int const& getLevel() const;

  /**
   * \brief Get the current octave
   * \return the octave 
   */					
  int const& getOctave() const;


};
#endif
