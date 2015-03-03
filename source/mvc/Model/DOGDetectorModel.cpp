#include "DOGDetectorModel.hpp"
#include "moc_DOGDetectorModel.cpp"


using namespace std;
using namespace cv;

DOGDetectorModel::DOGDetectorModel() : DetectorModel() 
{

  m_id = "DOGDetector";

  //Construct the params by default
  ParamModel level(5, "level", "int"), octave(3, "Octave", "int"), sigma(1.6, "Sigma", "double");

  m_params.push_back(octave);
  m_params.push_back(level);
  m_params.push_back(sigma);

  connect(this, SIGNAL(imagesLoaded()), this, SLOT(constructDetectors()));
}

void DOGDetectorModel::clearAllAttributs()
{
  m_listFiles.clear();
  m_isSelected.clear();
  m_images.clear();
  m_detectors.clear();
  m_isSelectedAtLeastOneFile = false;
}


void DOGDetectorModel::constructDetectors()
{
  m_detectors.clear();

  for(int i = 0; i < m_listFiles.count(); ++i)
    m_detectors.push_back(DOGDetector(m_images[i], m_params[0].getValue(), 
				      m_params[1].getValue(), m_params[2].getValue()));

  emit detectorsLoaded();    
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
	emit fileIsProcessed(100 * count / (allCount));
      }
  
  emit runOff();
}


vector<Feature> DOGDetectorModel::getFeatures(int i)
{
  return m_detectors[i].getFeaturesScaled();
}

