#ifndef DETECTORMANAGERMODEL_HPP
#define DETECTORMANAGERMODEL_HPP

#include <vector>
#include <QString>
#include <QWidget>
#include "../Model/DOGDetectorModel.hpp"


class DetectorManagerModel : public QWidget
{

Q_OBJECT

private :

  std::vector<DetectorModel*> m_detectors;
  std::vector<QString> m_ids;

 public :

  DetectorManagerModel();
  ~DetectorManagerModel();

  std::vector<QString> getIds();
  DetectorModel* getModel(int i);

signals :

void dataLoaded();
};

#endif
