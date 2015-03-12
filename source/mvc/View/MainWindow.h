#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <iostream>
#include <QProgressDialog>
#include <QPainter>

#include "../Model/DetectorModel.hpp"
#include "ParamsWidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
 private:
    Ui::MainWindow *ui;
    DetectorModel *m_model;
    QProgressDialog m_waitBar;
    ParamsWidget* m_paramsWidget;
       
 public:
    explicit MainWindow(DetectorModel *ptrModel, QWidget *parent = 0);
    ~MainWindow();

        
    public slots :

      void listenerFromView();
      void listenerFromModel();
      void setPath();
      void setListFiles();
      void initWidget();
      void displayWindow();
      void displayOverlay();
      void displayParams();
      void listFilesClicked(QListWidgetItem*);
      void constructParamsModel();
      void setListIdModel(std::vector<QString> ids);
      void selectAllFiles(int state);

 signals:
      void setPathActived(QStringList);
      void fileClicked(int, bool);
      void runClicked();
      void paramsConstructed();
      void setModel(int);
      void selectedAllFiles(int state);      
};

#endif 
