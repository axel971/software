#include "Controller.h"
#include "moc_Controller.cpp"

using namespace std;

Controller::Controller() : m_model(m_managerModel.getModel(0)), m_view(m_model)  
{
  //manage the events
  connect(&m_view, SIGNAL(setPathActived(QStringList)), this, SLOT(setListFiles(QStringList)));
  connect(&m_view, SIGNAL(fileClicked(int, bool)), m_model, SLOT(setIsSelected(int, bool)));
  connect(&m_view, SIGNAL(runClicked()), m_model, SLOT(run()));   
  connect(this, SIGNAL(sendIdModelToView(std::vector<QString>)), &m_view, SLOT(setListIdModel(std::vector<QString>)));
  connect(&m_view, SIGNAL(setModel(int)), this, SLOT(getModel(int)));
  connect(this, SIGNAL(modelChanged()), &m_view, SLOT(constructParamsModel()));
 
  //Initialize the view
  emit sendIdModelToView(m_managerModel.getIds());
}


void Controller::setListFiles(QStringList listFiles)
{
  m_model->setListFiles(listFiles);
}

void Controller::showView()
{
  m_view.show();
}

void Controller::getModel(int i)
{
  m_model = m_managerModel.getModel(i);

  emit modelChanged();
}


