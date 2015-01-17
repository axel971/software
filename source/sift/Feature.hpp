#ifndef FEATURE_H
#define FEATURE_H

class Feature
{
private :
  double m_sigma;
  int m_x;
  int m_y;
  double m_theta;

public :

  Feature();
  Feature(int x, int y, double sigma, double theta);

  int const& getX() const;
  int const& getY() const;
  double const& getSigma() const;
  double const& getTheta() const;
};

#endif
