project(pipeline-mq CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKI_REPOSITORY "http://artifacts.myftp.biz:8080")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmaki/cmaki.cmake")
cmaki_setup()

include_directories(boostorg_predef)

add_subdirectory(tests)
