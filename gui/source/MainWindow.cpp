#include "MainWindow.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(Model *ptrModel, QWidget *parent) : m_ptrModel(ptrModel), QMainWindow(parent), ui(new Ui::MainWindow), m_countListFiledSelected(0)
{
    ui->setupUi(this);

    //init the widgets
    initWidget();
    
    /*-------- Manage the events ---------*/
    //signals send of the controller
    connect(ui->openFiles, SIGNAL(triggered()), this, SLOT(setPath()));

    //listener toward the model
    connect(m_ptrModel, SIGNAL(listFilesLoaded()), this, SLOT(setListFiles()));
  
    //signals send of the view
    connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayWindow(int)));
    connect(ui->listFiles, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(countListFiledSelected(QListWidgetItem *)));
    connect(this, SIGNAL(listFiledSelected()), this, SLOT(enabledRun()));
    connect(this, SIGNAL(listFiledUnselected()), this, SLOT(unabledRun())); 
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::countListFiledSelected(QListWidgetItem *ptrItem)
{
   if (ptrItem->checkState() == 2)
     ++m_countListFiledSelected;
   else if (ptrItem->checkState() == 0) 
     --m_countListFiledSelected;

   if (m_countListFiledSelected)
     emit listFiledSelected();
   else
     emit listFiledUnselected();
}

void MainWindow::enabledRun()
{
  ui->run->setEnabled(true);
}

void MainWindow::unabledRun()
{
  ui->run->setEnabled(false);
}
