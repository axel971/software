#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <iostream>
#include <QProgressDialog>
#include <QPainter>

#include "../Model/DOGDetectorModel.hpp"
#include "ParamsWidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
 private:
    Ui::MainWindow *ui;
    DOGDetectorModel *m_ptrModel;
    QProgressDialog m_waitBar;
    ParamsWidget* m_paramsWidget;
       
 public:
    explicit MainWindow(DOGDetectorModel *ptrModel, QWidget *parent = 0);
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
      void runClickedSlot();
      void constructParams();
      
 signals:
      void setPathActived(QStringList);
      void fileClicked(int, bool);
      void runClicked();
      void paramsConstructed();
      void loadParams();
};

#endif 
