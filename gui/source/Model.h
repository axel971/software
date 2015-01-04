#ifndef MODEL_H
#define MODEL_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QWidget>

#include <iostream>

class Model : public QWidget
{

  Q_OBJECT
 
 protected :

  QStringList m_listFiles;
  bool m_isSelected;
  bool m_isProcessed;
  //  cv::Mat m_images;

 public :

  Model();
  void run();
  void setListFiles(QStringList listFiles);
  QStringList getListFiles();

 signals :

  void listFilesLoaded();
  void runFinished();

};

#endif
