#include "Model.hpp"
#include "moc_Model.cpp"


using namespace std;


Model::Model() : m_isSelectedAtLeastOneFile(false)
{
  m_id = "Model";

  connect(this, SIGNAL(listFilesLoaded()), this, SLOT(constructIsSelected()));
  connect(this, SIGNAL(listFilesSelectedIsModified()), this, SLOT(lookIfAtLeastOneFileIsSelected()));
}


void Model::setListFiles(QStringList listFiles)
{
  clearAllAttributs(); 

  m_listFiles = listFiles;

  emit listFilesLoaded();
}

QStringList Model::getListFiles()
{
  return m_listFiles;
}

void Model::constructIsSelected()
{
  m_isSelected.clear();
  m_isSelected = vector<bool>(m_listFiles.count(), false);
  emit listFilesSelectedIsModified();
}

void Model::setIsSelected(int i, bool value)
{
  m_isSelected[i] = value;
  emit listFilesSelectedIsModified();
}

bool Model::getIsSelected(int i)
{
 return m_isSelected[i];
}


virtual std::string Model::getId()
{
  return m_id;

vector<ParamModel> Model::getParams()
{
  return m_params;

}

void Model::lookIfAtLeastOneFileIsSelected()
{
  m_isSelectedAtLeastOneFile = false;

  for(int i = 0; i < m_isSelected.size(); ++i)
      if(m_isSelected[i])
	{
	  m_isSelectedAtLeastOneFile = true;
	  break;
	}

  emit atLeastOneFileIsSelected(m_isSelectedAtLeastOneFile);
}


