#include "Feature.hpp"

using namespace std;

Feature::Feature() : m_sigma(0), m_row(0), m_col(0), m_theta(0), m_octave(0), m_level(0)
{}

Feature::Feature(double row, double col, double sigma, double theta): m_row(row), m_col(col), m_sigma(sigma), m_theta(theta), m_octave(0), m_level(0)
{}

Feature::Feature(double row, double col, double sigma, double theta, int octave, int level) : m_row(row), m_col(col), m_sigma(sigma), m_theta(theta), m_octave(octave), m_level(level)
{}

double const& Feature::getRow() const
{
  return m_row;
}

double const& Feature::getCol() const
{
  return m_col;
}
 
double const& Feature::getSigma() const
{
  return m_sigma;
}

double const& Feature::getTheta() const
{
  return m_theta;
}

int const& Feature::getOctave() const
{
  return m_octave;
}

int const& Feature::getLevel() const
{
  return m_level;
}

void Feature::setRow(double row)
{
  m_row = row;
}

void Feature::setCol(double col)
{
  m_col = col;
}

void Feature::setSigma(double sigma)
{
  m_sigma = sigma;
}

void Feature::setOctave(int octave)
{
  m_octave = octave;
}

void Feature::setLevel(int level)
{
  m_level = level;
}

 
ostream& operator << (ostream& flux, const Feature& feature)
{
  //Display the argument
  flux << "row : " << feature.getRow() << endl;
  flux << "col : " << feature.getCol() << endl;
  flux << "scale : " << feature.getSigma() << endl;
  flux << "theta : " << feature.getTheta() << endl;
  flux << "Octave pyramid : " << feature.getOctave() << endl;
  flux << "Level pyramid : " << feature.getLevel() << endl;

  return flux;

}



