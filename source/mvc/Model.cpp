#include "Model.h"
#include "moc_Model.cpp"


using namespace std;
using namespace cv;

Model::Model() : m_isAllSelected(false)
{
  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(initIsSelected()));
  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(initImages()));
  connect(this, SIGNAL(isSelectedChanged()), this, SLOT(lookIsAllSelected()));
}

void Model::setListFiles(QStringList listFiles)
{
  m_listFiles.clear();
  m_listFiles = listFiles;

  emit listFilesLoaded();
}

QStringList Model::getListFiles()
{
  return m_listFiles;
}

void Model::initIsSelected()
{
  m_isSelected.clear();
  m_isSelected = vector<bool>(m_listFiles.count(), false);
  emit isSelectedChanged();
}

void Model::setIsSelected(int i, bool value)
{
  m_isSelected[i] = value;
  emit isSelectedChanged();
}

bool Model::getIsSelected(int i)
{
 return m_isSelected[i];
}

void Model::lookIsAllSelected()
{
  m_isAllSelected = false;

  for(int i = 0; i < m_isSelected.size(); ++i)
      if(m_isSelected[i])
	{
	  m_isAllSelected = true;
	  break;
	}

  emit isAllSelected(m_isAllSelected);
}

void Model::initImages()
{
  //generation of image array 
  m_images.clear();
  m_images.resize(m_listFiles.count());

  for(int i = 0; i < m_listFiles.count(); ++i)
    m_images[i] = imread(m_listFiles.at(i).toLocal8Bit().constData(), CV_LOAD_IMAGE_COLOR);
    
}

void Model::run()
{
  int nAllSelected = std::accumulate(m_isSelected.begin(), m_isSelected.end(), 0);
  int count(0);

  emit runOn();

  for(int i = 0; i < m_listFiles.count(); ++i)
    if(m_isSelected[i])
      {
	emit runChanged(100 * count / (nAllSelected - 1));
	count++;
      }
  
  emit runOff();
}
