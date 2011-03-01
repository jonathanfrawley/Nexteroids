/**
Nexteroids - A cross platform, networked asteroids game.
Copyright (C) 2010 Jonathan Frawley

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*
#define BOOST_TEST_DYN_LINK
// TODO: Include your class to test here.
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MyTestCase)
{
	// To simplify this example test, let's suppose we'll test 'float'.
	// Some test are stupid, but all should pass.
	float x = 9.5f;

	BOOST_CHECK(x != 0.0f);
	BOOST_CHECK_EQUAL((int)x, 9);
	BOOST_CHECK_CLOSE(x, 9.5f, 0.0001f); // Checks differ no more then 0.0001%
}
*/
//#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ProcessManager


#include <boost/test/unit_test.hpp>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "nxProcess/nxProcessManager.hpp"  

struct Fixture
{
	nxProcessManager processManager;
};


BOOST_AUTO_TEST_CASE (HasProcess)
{
    Fixture f;
    BOOST_CHECK_EQUAL (f.processManager.HasProcesses(), false);
}  

/*
BOOST_AUTO_UNIT_TEST (TestCase2)
{
    MyFixture f;
    BOOST_CHECK_EQUAL (f.str, std::string("Hello"));
    BOOST_CHECK_CLOSE (f.someValue, 2.0f, 0.005f);
    // Boost deals with this OK and reports the problem
    //f.myObject.UseBadPointer();
    // Same with this
    //myObject.DivideByZero();
}  

BOOST_AUTO_UNIT_TEST (TestCase3)
{
    MyFixture f;
    BOOST_CHECK_EQUAL (1, f.myObject.s_currentInstances);
    BOOST_CHECK_EQUAL (3, f.myObject.s_instancesCreated);
    BOOST_CHECK_EQUAL (1, f.myObject.s_maxSimultaneousInstances);
}
*/
