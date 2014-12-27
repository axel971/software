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

  bool  getOpenFiles();
  void initWidget();
  
 private:
    Ui::MainWindow *ui;
    QStringList m_listFiles;

    public slots :
      void setListFiles();
      void displayWindow(int iListFiles);
};

#endif // MAINWINDOW_H
