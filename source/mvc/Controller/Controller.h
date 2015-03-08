#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QWidget>
#include "../View/MainWindow.h"
#include "../Model/DOGDetectorModel.hpp"
#include "DetectorManagerModel.hpp"

class Controller : QWidget
{
  
  Q_OBJECT
 
 private :
  DetectorManagerModel m_managerModel;
  DetectorModel *m_model; 
  MainWindow m_view;
  
 public :
  
  Controller();
  void showView();
  
  public slots :
    
    void setListFiles(QStringList);
    void getModel(int i);
  
 signals :
 
    void modelChanged();
    void sendIdModelToView(std::vector<QString>);
};
#endif
