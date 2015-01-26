#ifndef FEATURE_H
#define FEATURE_H

#include <iostream>

class Feature
{
private :
  double m_sigma;
  int m_row;
  int m_col;
  int m_level;
  int m_octave;
  double m_theta;

public :

  Feature();
  Feature(int row, int col, double sigma, double theta);
  Feature(int row, int col, double sigma, double theta, int octave, int level);

  
  int const& getRow() const;
  int const& getCol() const;
  double const& getSigma() const;
  double const& getTheta() const;
  int const& getOctave() const;
  int const& getLevel() const;
  void setOctave(int octave);
  void setLevel(int level);

  friend std::ostream& operator << (std::ostream& flux, const Feature& feature);
  
};

#endif
