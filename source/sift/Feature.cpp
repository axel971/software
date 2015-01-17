#include "Feature.hpp"

Feature::Feature() : m_sigma(0), m_x(0), m_y(0), m_theta(0)
{}

Feature::Feature(int x, int y, double sigma, double theta): m_x(x), m_y(y), m_sigma(sigma), m_theta(theta)
{}


int const& Feature::getX() const
{
  return m_x;
}

int const& Feature::getY() const
{
  return m_y;
}
 
double const& Feature::getSigma() const
{
  return m_sigma;
}

double const& Feature::getTheta() const
{
  return m_theta;
}
