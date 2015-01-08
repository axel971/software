#include "MainWindow.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(Model *ptrModel, QWidget *parent) : m_ptrModel(ptrModel), QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init the widgets
    initWidget();
    
    //signals send of the controller
    connect(ui->openFiles, SIGNAL(triggered()), this, SLOT(setPath()));

    //listener toward the model
    connect(m_ptrModel, SIGNAL(listFilesLoaded()), this, SLOT(setListFiles()));
  
    //signals send of the view
    connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayWindow(int)));
    connect(ui->listFiles, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listFilesClicked(QListWidgetItem *)));
    connect(m_ptrModel, SIGNAL(isAllSelected(bool)), this, SLOT(enabledRun(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::Ui()
{
  return ui;
} 

void MainWindow::initWidget()
{
  //making process widget disable
  ui->run->setEnabled(false);
  ui->overlay->setEnabled(false);
}

void MainWindow::setPath()
{
  QStringList listFiles;
  listFiles =  QFileDialog::getOpenFileNames(this, "ouvrir un fichier",  QString(),"Images all (*.jpg  *.png *.jpeg)");
  emit setPathActived(listFiles);
}

void MainWindow::setListFiles()
{
  //clear thelistFiles
  ui->listFiles->clear(); //if m_listFile isn't empty so clear listFiles 
  
  //add item (list elements) inside the liste
  ui->listFiles->addItems(m_ptrModel->getListFiles());

  //Init the current item at the first item
  if(ui->listFiles->count()> 0)
    ui->listFiles->setCurrentRow(0);

  //Creat  checkboxes for each item
  for(int i = 0; i < ui->listFiles->count(); ++i)
    {
      ui->listFiles->item(i)->setFlags(ui->listFiles->item(i)->flags()|Qt::ItemIsUserCheckable);
      ui->listFiles->item(i)->setCheckState(Qt::Unchecked);
    }

  //display list and check boxes
  ui->listFiles->show();

}


void MainWindow::displayWindow(int iListFiles)
{
  QStringList listFiles;
  listFiles = m_ptrModel->getListFiles();

  if(iListFiles >= 0) // This line avoid the bug when there aren't lisFile elements
    {
      ui->displayImage->setPixmap(QPixmap(listFiles.at(iListFiles).toLocal8Bit().constData()));
      ui->displayImage->setScaledContents(true);
    }
  else
    ui->displayImage->clear();
}


void MainWindow::listFilesClicked(QListWidgetItem *ptrItem)
{
   if (ptrItem->checkState() == 2)
     emit fileClicked(ui->listFiles->row(ptrItem) , true);
   
   else if (ptrItem->checkState() == 0) 
     emit fileClicked(ui->listFiles->row(ptrItem), false);
}

void MainWindow::enabledRun(bool value)
{
  ui->run->setEnabled(value);
}
