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

#define PACKAGE "boost"
#define VERSION "1.64"

class PublishTests : testing::Test { };

/*
////////// /////OS
BOOST_OS_AIX
BOOST_OS_AMIGAOS
BOOST_OS_ANDROID
BOOST_OS_BEOS
BOOST_OS_BSD
	BOOST_OS_BSD_DRAGONFLY DragonFly BSD
	BOOST_OS_BSD_FREE FreeBSD
	BOOST_OS_BSD_BSDI BSDi BSD/OS
	BOOST_OS_BSD_NET NetBSD
	BOOST_OS_BSD_OPEN OpenBSD
BOOST_OS_CYGWIN
BOOST_OS_HPUX
BOOST_OS_IRIX
BOOST_OS_LINUX
BOOST_OS_MACOS
BOOST_OS_OS400
BOOST_OS_QNX
BOOST_OS_SOLARIS
BOOST_OS_UNIX
BOOST_OS_SVR4
BOOST_OS_VMS
BOOST_OS_WINDOWS

////////////////// COMPILERS
BOOST_COMP_BORLAND
BOOST_COMP_CLANG
BOOST_COMP_COMO Comeau C++
BOOST_COMP_DEC
BOOST_COMP_DIAB
BOOST_COMP_DMC
BOOST_COMP_SYSC
BOOST_COMP_EDG
BOOST_COMP_PATH
BOOST_COMP_GNUC
BOOST_COMP_GCCXML
BOOST_COMP_GHS
BOOST_COMP_HPACC
BOOST_COMP_IAR
BOOST_COMP_IBM
BOOST_COMP_INTEL
BOOST_COMP_KCC
BOOST_COMP_LLVM
BOOST_COMP_HIGHC
BOOST_COMP_MWERKS
BOOST_COMP_MRI
BOOST_COMP_MPW
BOOST_COMP_PALM
BOOST_COMP_PGI
BOOST_COMP_SGI
BOOST_COMP_SUNPRO
BOOST_COMP_TENDRA
BOOST_COMP_MSVC
BOOST_COMP_WATCOM

BOOST_ARCH_ALPHA
BOOST_ARCH_ARM
BOOST_ARCH_BLACKFIN
BOOST_ARCH_CONVEX
BOOST_ARCH_IA64
BOOST_ARCH_M68K
BOOST_ARCH_MIPS
BOOST_ARCH_PARISK
BOOST_ARCH_PPC
BOOST_ARCH_PYRAMID
BOOST_ARCH_RS6000
BOOST_ARCH_SPARC
BOOST_ARCH_SH
BOOST_ARCH_SYS370
BOOST_ARCH_SYS390
BOOST_ARCH_X86
BOOST_ARCH_X86_32
BOOST_ARCH_X86_64
BOOST_ARCH_Z
*/

TEST(PublishTests, TestSync)
{
#if BOOST_OS_WINDOWS
	#if BOOST_ARCH_X86_32
		#define OPERATIVE_SYSTEM "win32"
	#elif BOOST_ARCH_X86_64
		#define OPERATIVE_SYSTEM "win64"
	#else
		#define OPERATIVE_SYSTEM "unknown_so"
	#endif
#elif BOOST_OS_ANDROID
	#define OPERATIVE_SYSTEM "android"
#elif BOOST_OS_LINUX
	// use __GLIBC__ and __GLIBC_MINOR__ ? for detect binary compatibility
	#define OPERATIVE_SYSTEM "linux"
#elif BOOST_OS_MACOS
	#define OPERATIVE_SYSTEM "macosx"
#else
	#define OPERATIVE_SYSTEM "unknown_so"
#endif
	
#if BOOST_OS_WINDOWS
	#ifdef _MSC_VER
		#if _MSC_VER == 1911
			#define COMPILER "msvc2017"
		#elif _MSC_VER == 1910
			#define COMPILER "msvc2017"
		#elif _MSC_VER == 1900
			#define COMPILER "msvc2015"
		#elif _MSC_VER == 1800
			#define COMPILER "msvc2013"
		#elif _MSC_VER == 1700
			#define COMPILER "msvc2012"
		#elif _MSC_VER == 1600
			#define COMPILER "msvc2010"
		#elif _MSC_VER == 1500
			#define COMPILER "msvc2008"
		#elif _MSC_VER == 1400
			#define COMPILER "msvc2005"
		#elif _MSC_VER == 1310
			#define COMPILER "msvc2003"
		#else
			#define COMPILER "unknown_compiler"
		#endif
	#elif BOOST_COMP_GNUC
		#define COMPILER "gcc"
	#elif BOOST_COMP_CLANG
		#define COMPILER "clang"
	#else
		#define COMPILER "unknown_compiler"
	#endif
#else
	#if BOOST_COMP_GNUC
		#define COMPILER "gcc"
	#elif BOOST_COMP_CLANG
		#define COMPILER "clang"
	#else
		#define COMPILER "unknown_compiler"
	#endif
#endif

#if BOOST_ARCH_ARM
	#define ARCHITECTURE "arm"
#elif BOOST_ARCH_X86
	#if BOOST_ARCH_X86_32
		#define ARCHITECTURE "x32"
	#elif BOOST_ARCH_X86_64
		#define ARCHITECTURE "x64"
	#else
		#define ARCHITECTURE "unknown_arch"
	#endif
#else
	#define ARCHITECTURE "unknown_arch"
#endif
	
	std::cout << PACKAGE << "-" << VERSION << "-" << OPERATIVE_SYSTEM << "-" << ARCHITECTURE << "-" << COMPILER << "-" << getenv("MODE") << std::endl;
}
