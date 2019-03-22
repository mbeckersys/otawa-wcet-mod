CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# configuration
set(EXEC "ogensim")
set(MODULES )
set(SOURCES
	Cache.cpp
	Execute.cpp
	Fetch.cpp
	GenericSimulator.cpp
	InstructionQueue.cpp
	PipelineStage.cpp
	GenericProcessor.cpp
	Memory.cpp
	FunctionalUnit.cpp
	ExecuteLPC2138.cpp
	hwcache.cpp
	main.cpp)
set(SYSTEMC_INC "/usr/include")
set(SYSTEMC_LIB "-L/usr/lib-linux64 -lsystemc -Wl,-rpath -Wl,/usr/lib-linux64")

# script
project(${EXEC})
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g3 -rdynamic")

# look for OTAWA
if(NOT OTAWA_CONFIG)
	find_program(OTAWA_CONFIG otawa-config DOC "path to otawa-config")
	if(NOT OTAWA_CONFIG)
		message(FATAL_ERROR "ERROR: otawa-config is required !")
	endif()
endif()
message(STATUS "otawa-config at ${OTAWA_CONFIG}")
execute_process(COMMAND "${OTAWA_CONFIG}" --cflags ${MODULES} OUTPUT_VARIABLE OTAWA_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND "${OTAWA_CONFIG}" --libs ${MODULES} --rpath OUTPUT_VARIABLE OTAWA_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND "${OTAWA_CONFIG}" --prefix OUTPUT_VARIABLE OTAWA_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)

# plugin definition
include_directories("${CMAKE_SOURCE_DIR}" "." "${SYSTEMC_INC}")
add_executable(${EXEC} ${SOURCES})
set_property(TARGET ${EXEC} PROPERTY COMPILE_FLAGS "${OTAWA_CFLAGS}")
target_link_libraries(${EXEC} "${OTAWA_LDFLAGS}" "${SYSTEMC_LIB}")
