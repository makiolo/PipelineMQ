project(pipeline-mq CXX)
cmake_minimum_required(VERSION 3.0.2)

set(CMAKI_REPOSITORY "http://artifacts.myftp.biz:8080")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmaki/cmaki.cmake")
cmaki_setup()

# I prefer use full rpath because is raspberry environment
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_BUILD_TYPE})

cmaki_find_package(paho-mqtt3)
cmaki_find_package(paho-mqttpp3)

# paho-mqtt can be compiled with cmaki but 
# rf24 and mysqlcppconn libraries come from apt-get install ....
find_library(RF24_LIBRARY rf24-bcm)
if(RF24_LIBRARY_NOTFOUND)
	message(FATAL_ERROR "rf24 not found: ${RF24_LIBRARY}")
endif()
find_library(MYSQL_LIBRARY mysqlcppconn)
if(MYSQL_LIBRARY_NOTFOUND)
	message(FATAL_ERROR "mysql not found: ${MYSQL_LIBRARY}")
endif()
cmaki2_executable(receiver receiver.cpp PTHREADS DEPENDS ${RF24_LIBRARY} ${MYSQL_LIBRARY})

add_subdirectory(tests)

# TODO: studied RF24 over TCP/IP: http://tmrh20.github.io/RF24Ethernet/
