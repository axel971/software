#ifndef TESTDOGDETECTOR_H
#define TESTDOGDETECTOR_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../../source/detector/DOGDetector.hpp"

class TestDOGDetector : public CPPUNIT_NS :: TestFixture
{
  CPPUNIT_TEST_SUITE (TestDOGDetector);
  CPPUNIT_TEST(executionTest);
  CPPUNIT_TEST(twiceExecutionTest);
  // CPPUNIT_TEST(limitCaseTest);
  CPPUNIT_TEST_SUITE_END ();

private :
  //  DOGDetector m_dogDetector;
  
public :
  
  void setUp();
  void tearUp();

protected :

  void executionTest();
  void twiceExecutionTest();
  void limitCaseTest();
};

#endif
