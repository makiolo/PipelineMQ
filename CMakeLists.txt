project(pipeline-mq CXX)
cmake_minimum_required(VERSION 3.0.2)

set(CMAKI_REPOSITORY "http://artifacts.myftp.biz:8080")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmaki/cmaki.cmake")
cmaki_setup()

cmaki_find_package(paho-mqtt3)
cmaki_find_package(paho-mqttpp3)
cmaki2_gtest(sync_publish sync_publish.cpp PTHREADS)
