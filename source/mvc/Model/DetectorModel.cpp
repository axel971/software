#include "DetectorModel.hpp"
#include "moc_DetectorModel.cpp"

using namespace std;
using namespace cv;


DetectorModel::DetectorModel() : Model()
{
  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(constructImages()));
}

void DetectorModel::constructImages()
{
  //generation of image array 
  m_images.clear();
  m_images.resize(m_listFiles.count());

  for(int i = 0; i < m_listFiles.count(); ++i)
    m_images[i] = imread(m_listFiles.at(i).toLocal8Bit().constData(), CV_LOAD_IMAGE_COLOR);
    
  emit imagesLoaded();
}
