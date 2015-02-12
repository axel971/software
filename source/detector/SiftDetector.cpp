#include "SiftDetector.hpp"


using namespace std;
using namespace cv;


SiftDetector::SiftDetector(Mat image, int octave, int level, double sigma): m_image(image), m_level(level), m_octave(octave), m_sigma(sigma)
{ }

vector<Feature> SiftDetector::getFeatures()
{
  return m_features;
}

vector<Feature> SiftDetector::getFeaturesScaled()
{
  vector<Feature> features(m_features.size());

  for(int i = 0; i < m_features.size(); ++i)
    {
      features[i] = m_features[i];

      features[i].setRow(features[i].getRow() * pow(2, features[i].getOctave()));
      features[i].setCol(features[i].getCol() * pow(2, features[i].getOctave()));
    }
  
  return features;
}

int SiftDetector::getNumbersFeatures()
{
  return m_features.size();
}
