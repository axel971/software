#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QWidget>
#include "../View/MainWindow.h"
#include "../Model/DOGDetectorModel.hpp"

class Controller : QWidget
{
  
  Q_OBJECT
 
 private :

  DOGDetectorModel m_model; 
  MainWindow m_view;
  
 public :
  
  Controller();
  void showView();
  
  public slots :
    
    void setListFiles(QStringList);
      
};
#endif
