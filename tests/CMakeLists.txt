cmaki2_gtest(sync_publish sync_publish.cpp PTHREADS)
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
	message("sync_subscribe is skipped because can stuck compilation")
else()
	cmaki2_gtest(sync_subscribe sync_subscribe.cpp PTHREADS)
endif()

