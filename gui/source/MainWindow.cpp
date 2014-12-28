#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init the widgets
    initWidget();

    //manage the events
    connect(ui->openFiles, SIGNAL(triggered()), this, SLOT(getListFiles()));
    connect(this, SIGNAL(listFilesIsChanged()), this, SLOT(setListFiles()));
    connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayWindow(int)));
    connect(this, SIGNAL(listFilesIsLoaded()), this, SLOT(enabledRun()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getListFiles()
{
  m_listFiles.clear();
  m_listFiles =  QFileDialog::getOpenFileNames(this, "ouvrir un fichier",  QString(),"All Files (*.*)");

  emit listFilesIsChanged();
}

void MainWindow::initWidget()
{
  //making process widget disable
  ui->run->setEnabled(false);
  ui->overlay->setEnabled(false);
}

void MainWindow::setListFiles()
{
  //clear thelistFiles
  ui->listFiles->clear(); //if m_listFile isn't empty so clear listFiles 
  
  //add item (list elements) inside the liste
  ui->listFiles->addItems(m_listFiles);

  //Init the current item at the first item
  if(ui->listFiles->count()> 0)
    ui->listFiles->setCurrentRow(0);

  //Creat  checkboxes for each item
  for(int i = 0; i < ui->listFiles->count(); ++i)
    {
      ui->listFiles->item(i)->setFlags(ui->listFiles->item(i)->flags()|Qt::ItemIsUserCheckable);
      ui->listFiles->item(i)->setCheckState(Qt::Unchecked);
    }

  // display list and check boxes
  ui->listFiles->show();

  emit listFilesIsLoaded();
}

void MainWindow::displayWindow(int iListFiles)
{
  if(iListFiles >= 0) // This line avoid the bug when there aren't lisFile elements
    ui->displayImage->setPixmap(QPixmap(m_listFiles.at(iListFiles).toLocal8Bit().constData()));
  else
    ui->displayImage->clear();
}

void MainWindow::enabledRun()
{
  ui->run->setEnabled(true);
}
