#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <iostream>
#include <QProgressDialog>
#include <QPainter>

#include "DOGDetectorModel.hpp"

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
   
 public:
    explicit MainWindow(DOGDetectorModel *ptrModel, QWidget *parent = 0);
    ~MainWindow();

    void initWidget();
        
    public slots :

      void setPath();
      void setListFiles();
      void displayWindow();
      void displayOverlay();
      void listFilesClicked(QListWidgetItem*);
      void enabledRun(bool);    
      void runClickedSlot();

 signals:
      void setPathActived(QStringList);
      void fileClicked(int, bool);
      void runClicked();
};

#endif 
