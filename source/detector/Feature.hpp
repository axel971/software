#ifndef FEATURE_H
#define FEATURE_H

#include <iostream>

class Feature
{
private :
  double m_sigma;
  double m_row;
  double m_col;
  int m_level;
  int m_octave;
  double m_theta;

public :

  Feature();
  Feature(double row, double col, double sigma, double theta);
  Feature(double row, double col, double sigma, double theta, int octave, int level);

  
  double const& getRow() const;
  double const& getCol() const;
  double const& getSigma() const;
  double const& getTheta() const;
  int const& getOctave() const;
  int const& getLevel() const;
  void setOctave(int octave);
  void setLevel(int level);
  void setRow(double row);
  void setCol(double col);
  void setSigma(double sigma);
  void setTheta(double tetha);

  friend std::ostream& operator << (std::ostream& flux, const Feature& feature);
  
};

#endif
