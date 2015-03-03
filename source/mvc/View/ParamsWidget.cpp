#include "ParamsWidget.hpp"
#include "moc_ParamsWidget.cpp"

using namespace std;

ParamsWidget::ParamsWidget(): m_labels(0), m_lineEdits(0)
{}

void ParamsWidget::build(QGridLayout*& layout, int nParams)
{
  m_nParams = nParams;

  m_labels.clear();
  m_lineEdits.clear();

  for(int i = 0; i < m_nParams; ++i)
    {
      m_labels.push_back(new QLabel);
      m_lineEdits.push_back(new QLineEdit);

      layout->addWidget(m_labels.back(), i + 1, 0);
      layout->addWidget(m_lineEdits.back(), i + 1, 1);

      connect(m_lineEdits.back(), SIGNAL(editingFinished()), this, SLOT(modifiedAux()));
    }

}

void ParamsWidget::setParams(vector<ParamModel>& params)
{
  for(int i = 0; i < params.size(); ++i)
    {
      m_labels[i]->setText(QString::fromStdString(params[i].getId()));
      m_lineEdits[i]->setText(QString::number(params[i].getValue()));
    }
}

void ParamsWidget::modifiedAux()
{
  emit modified();
}
