#include "ceaser.h"
#include "replace.h"
#include <iostream>
#include <string>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TextTestRunner.h>

using namespace std;

class Tester:public CppUnit::TestFixture
{
private:
	Ceaser * cpos;
	Replace * rpos;

public:
	void setUp()
	{
		cpos = new Ceaser(3);
		rpos = new Replace(string("qazwsxedcrfvtgbyhnujmikolp"));
	}
	void tearDown()
	{
		delete cpos;
		delete rpos;
	}
	void zeroString()
	{
		CPPUNIT_ASSERT_THROW_MESSAGE("Zero string",cpos->encrypt(string("")),CeaserException);
		CPPUNIT_ASSERT_THROW_MESSAGE("Zero string",rpos->decrypt(string("")),ReplaceException);
	}
	void lessKey()
	{
		CPPUNIT_ASSERT_THROW_MESSAGE("Zero key [Ceaser]", Ceaser(0), CeaserException );
		CPPUNIT_ASSERT_THROW_MESSAGE("The key is less than 26 [Replace]", Replace(string("hfdgskqr")), ReplaceException );
		CPPUNIT_ASSERT_THROW_MESSAGE("A degenerate key [Replace] ", Replace(string("abcdefghijklmnopqrstuvwxyz")), ReplaceException );
	}
	void plusTest()
	{
		CPPUNIT_ASSERT_NO_THROW(cpos->encrypt(string("I'm waking up to ash and dust. I wipe my brow and I sweat my rust")));
		CPPUNIT_ASSERT_NO_THROW(rpos->decrypt(string("Yesterday. All my troubles seemed so far away")));
	}
};

int main(void)
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite("Tester");

	suite->addTest(new CppUnit::TestCaller<Tester>
		("plusTest", &Tester::plusTest ));

	suite->addTest(new CppUnit::TestCaller<Tester>
		("zeroString", &Tester::zeroString ));

	suite->addTest(new CppUnit::TestCaller<Tester>
		("lessKey", &Tester::lessKey ));

	CppUnit::TextTestRunner runner;
	runner.addTest(suite);
	runner.run();
	return 0;
}
