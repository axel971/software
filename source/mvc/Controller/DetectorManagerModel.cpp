#include "DetectorManagerModel.hpp"

using namespace std;

DetectorManagerModel::DetectorManagerModel()
{

  m_detectors.push_back(new DOGDetectorModel());

}


DetectorManagerModel::~DetectorManagerModel()
{

  for(int i = 0; i < m_detectors.size(); ++i)
    delete m_detectors[i];
}

vector<QString> DetectorManagerModel::getIds()
{

  vector<QString> ids;

  for(int i = 0; i < m_detectors.size(); ++i)
    ids.push_back(QString::fromStdString(m_detectors[i]->getId()));
 
 return ids;    
}


DetectorModel* DetectorManagerModel::getModel(int i)
{
  return m_detectors[i];
}
