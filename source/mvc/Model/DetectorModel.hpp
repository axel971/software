#ifndef DETECTORMODEL_HPP
#define DETECTORMODEL_HPP

#include "Model.hpp"


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

#include <iostream>
#include <vector>
#include <numeric>

#include "../../detector/Feature.hpp"

class DetectorModel : public Model
{

 Q_OBJECT

protected :

  std::vector<cv::Mat> m_images;

public :
 
  DetectorModel();
  
  virtual std::vector<Feature> getFeatures(int i) = 0;
						   
public slots :

  void constructImages();
  virtual void constructDetectors() = 0;

signals :
  void imagesLoaded();
  void detectorsLoaded();
};

#endif
