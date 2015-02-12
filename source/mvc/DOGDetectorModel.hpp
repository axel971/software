#ifndef DOGDETECTORMODEL_HPP
#define DOGDETECTORMODEL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

#include <iostream>
#include <vector>
#include <numeric>

#include "../detector/DOGDetector.hpp"


class DOGDetectorModel : public QWidget
{

  Q_OBJECT
 
protected :

  QStringList m_listFiles;
  std::vector<bool> m_isSelected;
  bool is_atLeastOneSelected;
  std::vector<cv::Mat> m_images;
  std::vector<DOGDetector> m_detectors;
  
public :
  
  DOGDetectorModel();
  
  void setListFiles(QStringList listFiles);
  QStringList getListFiles();   
  bool getIsSelected(int i);
  std::vector<Feature> getFeatures(int i);
  void clearAll();
			   
public slots :
  
    void initIsSelected();
    void setIsSelected(int i, bool value);
    void initImages();
    void lookIsAllSelected();
    void run();
    void initDetector();

 signals :

  void listFilesLoaded();
  void runOff(bool = true);
  void runOn();
  void runChanged(int);
  void isAllSelected(bool);
  void isSelectedChanged();
  void imagesLoaded();
  

};

#endif
