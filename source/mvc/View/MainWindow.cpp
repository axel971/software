#include "MainWindow.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(DetectorModel *ptrModel, QWidget *parent) : m_model(ptrModel), QMainWindow(parent), ui(new Ui::MainWindow), m_waitBar(parent), m_paramsWidget(new ParamsWidget)
{
    ui->setupUi(this);
   
    listenerFromModel();
    listenerFromView();

    initWidget();
}

MainWindow::~MainWindow()
{

  if(m_paramsWidget != 0)
    delete m_paramsWidget;
  
    delete ui;
}
void MainWindow::listenerFromModel()
{
    //Listener toward the model
    connect(m_model, SIGNAL(listFilesLoaded()), this, SLOT(setListFiles()));
    connect(m_model, SIGNAL(atLeastOneFileIsSelected(bool)), ui->run, SLOT(setEnabled(bool)));
    connect(m_model, SIGNAL(runOff(bool)), ui->overlay, SLOT(setEnabled(bool)));
    connect(m_model, SIGNAL(runOff(bool)), ui->overlay, SLOT(setChecked(bool)));
    connect(m_model, SIGNAL(runOff()), this, SLOT(displayOverlay()));
    //connect(m_model, SIGNAL(runOn()), &m_waitBar, SLOT(show()));
    //connect(m_model, SIGNAL(runOff()), &m_waitBar, SLOT(cancel()));
    //connect(m_model, SIGNAL(runChanged(int)), &m_waitBar, SLOT(setValue(int)));

}

void MainWindow::listenerFromView()
{

  //Signals send of the controller
  connect(ui->openFiles, SIGNAL(triggered()), this, SLOT(setPath()));
  connect(ui->run, SIGNAL(clicked()), this, SIGNAL(runClicked()));
  connect(ui->chooseModel, SIGNAL(currentIndexChanged(int)), this, SIGNAL(setModel(int)));

  //Entire Signals from the view
  connect(this, SIGNAL(setPathActived(QStringList)), this, SLOT(initWidget()));
  connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayWindow()));
  connect(ui->listFiles, SIGNAL(currentRowChanged(int)), this, SLOT(displayOverlay()));
  connect(this, SIGNAL(paramsConstructed()), this, SLOT(displayParams()));
  connect(ui->listFiles, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listFilesClicked(QListWidgetItem *)));
  connect(ui->overlay, SIGNAL(stateChanged(int)), this, SLOT(displayOverlay()));
  connect(m_paramsWidget, SIGNAL(modified()), this,  SLOT(displayParams()));
  connect(ui->selectedAllFiles, SIGNAL(stateChanged(int)), this, SLOT(selectAllFiles(int)));
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
  ui->listFiles->addItems(m_model->getListFiles());

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


void MainWindow::displayWindow()
{
  QStringList listFiles;
  listFiles = m_model->getListFiles();

  int iListFiles =  ui->listFiles->currentRow();

  if(iListFiles >= 0) // This line avoid the bug when there aren't lisFile elements
    {
      ui->displayImage->setPixmap(QPixmap(listFiles.at(iListFiles).toLocal8Bit().constData()));
      ui->displayImage->setScaledContents(true);
    }
  else
    ui->displayImage->clear();

}

void MainWindow::displayOverlay()
{


  QStringList listFiles = m_model->getListFiles();
  int iListFiles =  ui->listFiles->currentRow();

  if(ui->overlay->checkState() == 0)
    displayWindow(); 
  
  else if(ui->overlay->checkState() == 2 && iListFiles >= 0)
    {
      vector<Feature> features = m_model->getFeatures(iListFiles);
      QPixmap image =  QPixmap(listFiles.at(iListFiles).toLocal8Bit().constData());
      QPainter painter(&image);
  
      painter.setPen(Qt::red);
      
      for(int i = 0; i < features.size(); ++i)
	{
	  QPointF center(features[i].getCol(), features[i].getRow());
	  painter.drawEllipse(center, features[i].getSigma(), features[i].getSigma());
	}

      ui->displayImage->setPixmap(image);
    }
}

void MainWindow::listFilesClicked(QListWidgetItem *ptrItem)
{
   if (ptrItem->checkState() == 2)
     emit fileClicked(ui->listFiles->row(ptrItem) , true);
   
   else if (ptrItem->checkState() == 0) 
     emit fileClicked(ui->listFiles->row(ptrItem), false);
}


void MainWindow::constructParamsModel()
{
  int nParams = (m_model->getParams()).size();
  
  m_paramsWidget->build(ui->layoutParams, nParams);

  ui->groupBoxParams->setLayout(ui->layoutParams);

  emit paramsConstructed();
}

void MainWindow::displayParams()
{
  vector<ParamModel> params =  m_model->getParams();
  
  m_paramsWidget->setParams(params);
}

void MainWindow::setListIdModel(vector<QString> ids)
{
  for(int i = 0; i < ids.size(); ++i)
    ui->chooseModel->addItem(ids[i]);
}

void MainWindow::selectAllFiles(int state)
{

  //Update the checkbox on the listWidgetItem
  for(int i = 0; i < ui->listFiles->count(); ++i)
    {
      if( state == 0)
	ui->listFiles->item(i)->setCheckState(Qt::Unchecked);
      else if(state == 2)
	ui->listFiles->item(i)->setCheckState(Qt::Checked);
    }
      emit selectedAllFiles(state);
}
