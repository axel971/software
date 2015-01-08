#include "Model.h"
#include "moc_Model.cpp"

using namespace std;

Model::Model()
{
  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(initIsSelected()));
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
  m_isSelected = vector<bool>(m_listFiles.count(), false);
}

void Model::run()
{
  cout << "toto" << endl;
  // emit runFinished();
}
