#ifndef DOGDETECTORMODEL_HPP
#define DOGDETECTORMODEL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

#include <iostream>
#include <vector>
#include <numeric>

#include "../../detector/DOGDetector.hpp"
#include "DetectorModel.hpp"

class DOGDetectorModel : public  DetectorModel
{

  Q_OBJECT
 
protected :

  std::vector<DOGDetector> m_detectors;
  
public :
  
  DOGDetectorModel();
  
  virtual std::vector<Feature> getFeatures(int i);
  virtual void clearAllAttributs();
			   
public slots :
     
  virtual void run();
  virtual void constructDetectors();
  
};

#endif
