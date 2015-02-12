#include "DOGDetectorModel.hpp"
#include "moc_DOGDetectorModel.cpp"


using namespace std;
using namespace cv;

DOGDetectorModel::DOGDetectorModel() : is_atLeastOneSelected(false)
{
  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(initIsSelected()));
  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(initImages()));
  connect(this, SIGNAL(isSelectedChanged()), this, SLOT(lookIsAllSelected()));
  connect(this, SIGNAL(imagesLoaded()), this, SLOT(initDetector()));
}

void DOGDetectorModel::clearAll()
{
  m_listFiles.clear();
  m_isSelected.clear();
  m_images.clear();
  m_detectors.clear();
  is_atLeastOneSelected = false;
}

void DOGDetectorModel::setListFiles(QStringList listFiles)
{
  clearAll(); 

  m_listFiles = listFiles;

  emit listFilesLoaded();
}

QStringList DOGDetectorModel::getListFiles()
{
  return m_listFiles;
}

void DOGDetectorModel::initIsSelected()
{
  m_isSelected.clear();
  m_isSelected = vector<bool>(m_listFiles.count(), false);
  emit isSelectedChanged();
}

void DOGDetectorModel::setIsSelected(int i, bool value)
{
  m_isSelected[i] = value;
  emit isSelectedChanged();
}

bool DOGDetectorModel::getIsSelected(int i)
{
 return m_isSelected[i];
}

void DOGDetectorModel::lookIsAllSelected()
{
  is_atLeastOneSelected = false;

  for(int i = 0; i < m_isSelected.size(); ++i)
      if(m_isSelected[i])
	{
	  is_atLeastOneSelected = true;
	  break;
	}

  emit isAllSelected(is_atLeastOneSelected);
}

void DOGDetectorModel::initImages()
{
  //generation of image array 
  m_images.clear();
  m_images.resize(m_listFiles.count());

  for(int i = 0; i < m_listFiles.count(); ++i)
    m_images[i] = imread(m_listFiles.at(i).toLocal8Bit().constData(), CV_LOAD_IMAGE_COLOR);
    
  emit imagesLoaded();
}

void DOGDetectorModel::initDetector()
{
  m_detectors.clear();

  for(int i = 0; i < m_listFiles.count(); ++i)
    m_detectors.push_back(DOGDetector(m_images[i], 3, 5, 1.6));
    
}

void DOGDetectorModel::run()
{
  int allCount = std::accumulate(m_isSelected.begin(), m_isSelected.end(), 0);
  int count(0);

  emit runOn();
  
  for(int i = 0; i < m_listFiles.count(); ++i)
    if(m_isSelected[i])
      {
	//Process dog detector
	m_detectors[i]();

	//display
	cout << "Image " << i + 1 << " is processed." << endl;

	count++;
	emit runChanged(100 * count / (allCount));
      }
  
  emit runOff();
}

vector<Feature> DOGDetectorModel::getFeatures(int i)
{
  return m_detectors[i].getFeaturesScaled();
}

