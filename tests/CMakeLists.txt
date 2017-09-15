add_executable(cmaki_identifier cmaki_identifier.cpp)
install(TARGETS cmaki_identifier DESTINATION $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_all
    COMMAND CMAKI_INFO=ALL $ENV{CMAKI_INSTALL}/cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_so
    COMMAND CMAKI_INFO=SO $ENV{CMAKI_INSTALL}/cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_arch
    COMMAND CMAKI_INFO=ARCH $ENV{CMAKI_INSTALL}/cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
add_test(
    NAME cmaki_identifier_test_compiler
    COMMAND CMAKI_INFO=COMPILER $ENV{CMAKI_INSTALL}/cmaki_identifier
    WORKING_DIRECTORY $ENV{CMAKI_INSTALL})
