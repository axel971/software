#ifndef TESTGAUSSIANPYRAMID_HPP
#define TESTGAUSSIANPYRAMID_HPP

#define DIFF_EPS 1e-6

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../../source/imagePyramid/GaussianPyramid.hpp"

class TestGaussianPyramid : public CPPUNIT_NS :: TestFixture
{

  CPPUNIT_TEST_SUITE(TestGaussianPyramid);
  CPPUNIT_TEST(pyramidSizeTest);
  CPPUNIT_TEST(sigmaTest);
  CPPUNIT_TEST(eltPyramidDifferentTest);
  CPPUNIT_TEST(twiceExecutionTest);
  CPPUNIT_TEST_SUITE_END();

private :

public :

  void setUp();
  void tearUp();

protected :

  void pyramidSizeTest();
  void sigmaTest();
  void eltPyramidDifferentTest();
  void twiceExecutionTest();
};
#endif
