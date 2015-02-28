#ifndef MODEL_HPP
#define MODEL_HPP

#include <QWidget>

#include <iostream>
#include <vector>
#include <numeric>

#include "ParamModel.hpp"

class Model : public QWidget
{

  Q_OBJECT
 
protected :

  QStringList m_listFiles;
  std::vector<bool> m_isSelected;
  bool m_isSelectedAtLeastOneFile;
  std::vector<ParamModel> m_params;
  std::string m_id;

public :
  
  Model();
  
  void setListFiles(QStringList listFiles);
  QStringList getListFiles();   
  bool getIsSelected(int i);
  virtual void clearAllAttributs() = 0;
			   
public slots :
  
  void constructIsSelected();
  void setIsSelected(int i, bool value);
  void lookIfAtLeastOneFileIsSelected();
  virtual void run() = 0;
  
 signals :

  void listFilesLoaded();
  void runOff(bool = true);
  void runOn();
  void fileIsProcessed(int);
  void atLeastOneFileIsSelected(bool);
  void listFilesSelectedIsModified();
    
};

#endif
