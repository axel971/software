#ifndef PARAM_HPP
#define PARAM_HPP

#include<string>

class ParamModel
{
private:

  double m_value;
  std::string m_id;
  std::string m_type;
  std::string m_unity;

public:

  ParamModel(double value, std::string id, std::string type, std::string unity = "Unknown");

  void setValue(double value);
  void setiD(std::string id);
  void setType(std::string type);
  void setUnity(std::string unity);
  double getValue();
  std::string getId();
  std::string getType();
  std::string getUnity();

};

#endif
