#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <boost/predef.h>
#include <gmock/gmock.h>

using testing::AtLeast;
using testing::AnyNumber;
using testing::_;

class PublishTests : testing::Test { };

TEST(PublishTests, TestSync)
{
#if BOOST_OS_WINDOWS
	std::cout << "windows" << std::endl;
#elif BOOST_OS_LINUX
	std::cout << "linux" << std::endl;
#elif BOOST_OS_MACOS
	std::cout << "macosx" << std::endl;
#endif
}
