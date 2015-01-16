#ifndef TESTSIFT_H
#define TESTSIFT_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../../source/sift/Sift.hpp"

class TestSift : public CPPUNIT_NS :: TestFixture
{
  CPPUNIT_TEST_SUITE (TestSift);
  CPPUNIT_TEST (isExtremaTest);
  //CPPUNIT_TEST ();
  CPPUNIT_TEST_SUITE_END ();

public :
  
  void setUp();
  void tearUp();

protected :
  void isExtremaTest();

};

#endif
