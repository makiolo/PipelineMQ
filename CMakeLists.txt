project(pipeline-mq CXX)
cmake_minimum_required(VERSION 3.0.2)

set(CMAKI_REPOSITORY "http://artifacts.myftp.biz:8080")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmaki/cmaki.cmake")
cmaki_setup()

cmaki_find_package(paho-mqtt3)
cmaki_find_package(paho-mqttpp3)

find_library(RF24_LIBRARY rf24-bcm)
if(RF24_LIBRARY_NOTFOUND)
	message(FATAL_ERROR "rf24 not found: ${RF24_LIBRARY}")
endif()
cmaki2_executable(receiver receiver.cpp PTHREADS DEPENDS ${RF24_LIBRARY})
add_subdirectory(tests)

