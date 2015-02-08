#include "MainWindow.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(DOGDetectorModel *ptrModel, QWidget *parent) : m_ptrModel(ptrModel), QMainWindow(parent), ui(new Ui::MainWindow), m_waitBar(parent)
{
    ui->setupUi(this);

    //Initialisation of the widgets
    initWidget();
    
    //Signals send of the controller
    connect(ui->openFiles, SIGNAL(triggered()), this, SLOT(setPath()));
    connect(ui->run, SIGNAL(clicked()), this, SLOT(runClickedSlot()));

    //Listener toward the model
    connect(m_ptrModel, SIGNAL(listFilesLoaded()), this, SLOT(setListFiles()));
    //connect(m_ptrModel, SIGNAL(runOn()), &m_waitBar, SLOT(show()));
    //connect(m_ptrModel, SIGNAL(runOff()), &m_waitBar, SLOT(cancel()));
    //connect(m_ptrModel, SIGNAL(runChanged(int)), &m_waitBar, SLOT(setValue(int)));

    //Signals send of the view
    connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayWindow(int)));
    connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayOverlay(int)));
    connect(ui->listFiles, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listFilesClicked(QListWidgetItem *)));
    connect(m_ptrModel, SIGNAL(isAllSelected(bool)), this, SLOT(enabledRun(bool)));
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

  //init progressBar
  m_waitBar.setWindowModality(Qt::WindowModal); 
 m_waitBar.setRange(0, 100);
}


void MainWindow::setPath()
{
  QStringList listFiles = QFileDialog::getOpenFileNames(this, "ouvrir un fichier",  QString(),"Images all (*.jpg  *.png *.jpeg)");

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

void MainWindow::displayOverlay(int iListFiles)
{
  
  vector<Feature> features = m_ptrModel->getFeatures(iListFiles);
  QPixmap *image = (QPixmap *) ui->displayImage->pixmap();
  QPainter painter(image);

  painter.setBrush(Qt::red);

  for(int i = 0; i < features.size(); ++i)
    {
      QPointF center(features[i].getCol(), features[i].getRow());

      painter.drawEllipse(center, 1, 1);
    }
  
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

void MainWindow::runClickedSlot()
{
  emit runClicked();
}

