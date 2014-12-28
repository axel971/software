#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void initWidget();
  
 private:
    Ui::MainWindow *ui;
    QStringList m_listFiles;

    public slots :
      void getListFiles();
      void setListFiles();
      void displayWindow(int iListFiles);
      void enabledRun();

 signals:
      void listFilesIsChanged();
      void listFilesIsLoaded();
};

#endif // MAINWINDOW_H
