#include "Controller.h"
#include "moc_Controller.cpp"

using namespace std;

Controller::Controller() : m_view(&m_model)
{
  //manage the events
   connect(&m_view, SIGNAL(setPathActived(QStringList)), this, SLOT(setListFiles(QStringList)));
   connect(&m_view, SIGNAL(fileClicked(int, bool)), &m_model, SLOT(setIsSelected(int, bool)));
}


void Controller::setListFiles(QStringList listFiles)
{
  m_model.setListFiles(listFiles);
}

void Controller::showView()
{
  m_view.show();
}
