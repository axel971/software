#include "Model.h"
#include "moc_Model.cpp"

using namespace std;

Model::Model() : m_isAllSelected(false)
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
  m_isSelected.clear();
  m_isSelected = vector<bool>(m_listFiles.count(), false);
  lookIsAllSelected();
}

void Model::setIsSelected(int i, bool value)
{
  m_isSelected[i] = value;
  lookIsAllSelected();
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

void Model::run()
{
  cout << "toto" << endl;
  // emit runFinished();
}
