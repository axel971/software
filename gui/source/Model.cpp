#include "Model.h"
#include "moc_Model.cpp"

using namespace std;

Model::Model(){}

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

void Model::run()
{
  cout << "toto" << endl;
  // emit runFinished();
}
