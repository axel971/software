#ifndef DETECTORMANAGERMODEL_HPP
#define DETECTORMANAGERMODEL_HPP

#include <vector>
#include <QString>
#include "../Model/DOGDetectorModel.hpp"

class DetectorManagerModel
{

 private :

  std::vector<DetectorModel*> m_detectors;
  std::vector<QString> m_ids;

 public :

  DetectorManagerModel();
  ~DetectorManagerModel();

  std::vector<QString> getIds();
  DetectorModel* getModel(int i);

};

#endif
