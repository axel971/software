#include "Controller.h"
#include "moc_Controller.cpp"

using namespace std;

Controller::Controller() : m_model(m_managerModel.getModel(0)), m_view(m_model)  
{
  //manage the events
  connect(&m_view, SIGNAL(setPathActived(QStringList)), this, SLOT(setListFiles(QStringList)));
  connect(&m_view, SIGNAL(fileClicked(int, bool)), m_model, SLOT(setIsSelected(int, bool)));
  connect(&m_view, SIGNAL(runClicked()), m_model, SLOT(run()));   
  connect(&m_view, SIGNAL(initializedView()), this, SLOT(setListIdToView()));

  //Initialize the view
  m_view.initWidget();
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
}

void Controller::setListIdToView()
{
  m_view.initChooseModelWidget(m_managerModel.getIds());
}
