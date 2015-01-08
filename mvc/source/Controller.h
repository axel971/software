#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QWidget>
#include "MainWindow.h"
#include "Model.h"

class Controller : QWidget
{
  
  Q_OBJECT
 
 private :

  Model m_model; //To Do : utiliser un pointeur lors de l'initialisation de la vue n'es pas elegeant
  MainWindow m_view;
  
 public :
  
  Controller();
  void showView();
  
  public slots :
    
    void setListFiles(QStringList);
  
};
#endif
