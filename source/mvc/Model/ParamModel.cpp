#include "ParamModel.hpp"

using namespace std;

ParamModel::ParamModel(double value, std::string id, std::string type, std::string unity)
{
  m_value = value;
  m_id = id;
  m_type = type;
  m_unity = unity;
}

void ParamModel::setValue(double value)
{
  m_value = value;
}
void ParamModel::setiD(std::string id)
{
  m_id = id;
}
void ParamModel::setType(std::string type)
{
  m_type;
}

void ParamModel::setUnity(std::string unity)
{
  m_unity = unity;
}

double ParamModel::getValue()
{
  return m_value;
}

string ParamModel::getId()
{
  return m_id;
}

string ParamModel::getType()
{
  return m_type;
}

string ParamModel::getUnity()
{
  return m_unity;
}
