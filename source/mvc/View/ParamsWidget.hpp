#ifndef PARAMSWIDGET_HPP
#define PARAMSWIDGET_HPP

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QGridLayout>

#include "../Model/ParamModel.hpp"

class ParamsWidget : public QWidget
{
  
  Q_OBJECT
  
private :
  
  int m_nParams;
  std::vector<QLabel *> m_labels;
  std::vector<QLineEdit *> m_lineEdits;
  
public :
  
  ParamsWidget();

  void build(QGridLayout*& layout, int nParams);	 
  
  void setParams(std::vector<ParamModel>& params);

public slots :
  
  void modifiedAux();

signals :

  void modified();
};

#endif
