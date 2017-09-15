set(PLATFORM "")
set(dirscript ${CMAKE_CURRENT_LIST_DIR})
find_program(path cmaki_identifier ${dirscript})
execute_process(COMMAND ${path}
			WORKING_DIRECTORY ${dirscript}
			OUTPUT_VARIABLE PLATFORM
			OUTPUT_STRIP_TRAILING_WHITESPACE)
MESSAGE("${PLATFORM}")

