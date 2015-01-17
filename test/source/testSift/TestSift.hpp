#ifndef TESTSIFT_H
#define TESTSIFT_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../../source/sift/Sift.hpp"

class TestSift : public CPPUNIT_NS :: TestFixture
{
  CPPUNIT_TEST_SUITE (TestSift);
  CPPUNIT_TEST (findExtremaBorderInfConditionTest);
  CPPUNIT_TEST (findExtremaBorderSupConditionTest);
  CPPUNIT_TEST (findExtremaLevel2isMaximaTest);
  CPPUNIT_TEST (findExtremaLevel2isMinimaTest);
  CPPUNIT_TEST (findExtremaIsFalseTest);
  CPPUNIT_TEST_SUITE_END ();

private :
  Sift m_sift;

public :
  
  void setUp();
  void tearUp();

protected :

  void findExtremaBorderInfConditionTest();
  void findExtremaBorderSupConditionTest();
  void findExtremaLevel2isMaximaTest();
  void findExtremaLevel2isMinimaTest();
  void findExtremaIsFalseTest();
};

#endif
