#ifndef MODEL_H
#define MODEL_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

#include <iostream>
#include <vector>

class Model : public QWidget
{

  Q_OBJECT
 
 protected :

  QStringList m_listFiles;
  std::vector<bool> m_isSelected;
  bool m_isAllSelected;
  std::vector<cv::Mat> m_images;

 public :
  
  Model();
  
  void run();
  void setListFiles(QStringList listFiles);
  QStringList getListFiles();   
  bool getIsSelected(int i);
  
  public slots :
    void initIsSelected();
    void setIsSelected(int i, bool value);
    void initImages();
    void lookIsAllSelected();

 signals :

  void listFilesLoaded();
  void runFinished();
  void isAllSelected(bool);
  void isSelectedChanged();
};

#endif
