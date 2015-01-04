#include "Controller.h"
#include "moc_Controller.cpp"


Controller::Controller() : m_view(&m_model)
{
  //manage the events
   connect(&m_view, SIGNAL(setPathActived(QStringList)), this, SLOT(setListFiles(QStringList)));
}


void Controller::setListFiles(QStringList listFiles)
{
  m_model.setListFiles(listFiles);
}

void Controller::showView()
{
  m_view.show();
}
