#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <iostream>

#include "Model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
 private:
    Ui::MainWindow *ui;
    Model *m_ptrModel;
   
 public:
    explicit MainWindow(Model *ptrModel, QWidget *parent = 0);
    ~MainWindow();

    void initWidget();
    Ui::MainWindow *Ui();
    
    public slots :

      void setPath();
      void setListFiles();
      void displayWindow(int iListFiles);
      void listFilesClicked(QListWidgetItem*);
      void enabledRun(bool);   

 signals:
      void setPathActived(QStringList);
      void fileClicked(int, bool);
};

#endif // MAINWINDOW_H
