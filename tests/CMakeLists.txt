add_executable(cmaki_identifier cmaki_identifier.cpp)
install(TARGETS cmaki_identifier DESTINATION $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_all
    COMMAND CMAKI_INFO=ALL cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_so
    COMMAND CMAKI_INFO=SO cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_arch
    COMMAND CMAKI_INFO=ARCH cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_compiler
    COMMAND CMAKI_INFO=COMPILER cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
