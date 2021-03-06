cmake_minimum_required(VERSION 2.6)
project("otawa")
set(PACKAGE "otawa")
SET(CMAKE_BUILD_TYPE Debug)
SET(USE_SYSTEMC ON CACHE BOOL "links systemc into otawa")

# debugging activated
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g")
file(READ "VERSION" RELEASE_VERSION)
if(APPLE)
	set(ORIGIN @executable_path)
else()
	set(ORIGIN $ORIGIN)
endif()

# installation level
set(INSTALL_TYPE "bin,lib,inc,doc" CACHE STRING "Type of installation (a ',' separated combination of bin, lib, inc, doc).")
if(NOT INSTALL_TYPE OR INSTALL_TYPE MATCHES "all")
	set(INSTALL_BIN yes)
	set(INSTALL_LIB yes)
	set(INSTALL_INC yes)
#	set(INSTALL_DOC yes)
endif()
if(INSTALL_TYPE MATCHES ".*bin.*")
	set(INSTALL_BIN yes)
endif()
if(INSTALL_TYPE MATCHES ".*lib.*")
	set(INSTALL_LIB yes)
endif()
if(INSTALL_TYPE MATCHES ".*inc.*")
	set(INSTALL_INC yes)
endif()
if(INSTALL_TYPE MATCHES ".*doc.*")
	set(INSTALL_DOC yes)
endif()

# gcc based compiler lack of support by cmake (opposed to VS)
# so need to make some manual adjustment in this case
if (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -Wl,--kill-at -Wl,--add-stdcall-alias")
  set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wl,--kill-at -Wl,--add-stdcall-alias")
endif (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))


# install directories
if(MINGW_LINUX OR WIN32)
	set(LIBDIR "bin")
else()
	set(LIBDIR "lib")
endif()
set(PLUGDIR      "${CMAKE_INSTALL_PREFIX}/lib/otawa")
set(PROCDIR      "${PLUGDIR}/proc")
set(LOADERDIR    "${PLUGDIR}/loader")
set(SIMDIR       "${PLUGDIR}/sim")
set(ILPDIR       "${PLUGDIR}/ilp")


# adding Flex and Bison support
# the version of flex included with msys is bugged,
# so those scripts had to be heavily modded
if(WIN32)
include(CMakeUserUseBison.cmake RESULT_VARIABLE BISON)
include(CMakeUserUseFlex.cmake RESULT_VARIABLE FLEX)
endif(WIN32)

add_definitions(-DILP_PATHS=\"${PROJECT_BINARY_DIR}/lib/otawa/ilp\")
add_definitions(-DLOADER_PATHS=\"${PROJECT_BINARY_DIR}/lib/otawa/loader:${CMAKE_INSTALL_PREFIX}/lib/otawa/loader\")
add_definitions(-DSIMULATOR_PATHS=\"${PROJECT_BINARY_DIR}/lib/otawa/sim:${CMAKE_INSTALL_PREFIX}/lib/otawa/sim\")
add_definitions(-DPROC_PATHS=\"${PROJECT_BINARY_DIR}/lib/otawa/proc\")
add_definitions(-DHAS_RELOCATION)
add_definitions(-DOTAWA_CMAKE)

if (USE_SYSTEMC)
	add_definitions(-DHAS_SYSTEMC)
	set(SYSTEMC_INC "/usr/include")
	include_directories(${SYSTEMC_INC})
	set(SYSTEMC_LIB "-L/usr/lib-linux64 -lsystemc -Wl,-rpath -Wl,/usr/lib-linux64")
endif()

# looking for ARM loader
set(ARM5_PATH "${CMAKE_SOURCE_DIR}/../armv5t")
set(ARM7_PATH "${CMAKE_SOURCE_DIR}/../armv7t")
set(ARM_PATH "ARM_PATH-NOTFOUND" CACHE PATH "path to GLISS ARM path")
set(ARM_LIB "ARM_LIB-NOTFOUND" CACHE PATH "path to ARM library")
set(ARM_SIM ON CACHE BOOL "Compile in the ARM functional simulator")

if(EXISTS "${ARM7_PATH}")
	set(ARM_PATH "${ARM7_PATH}")
	set(ARM7 "ON")
elseif(EXISTS "${ARM5_PATH}")
    set(ARM_PATH "${ARM5_PATH}")
endif()
message(STATUS "ARM_PATH=${ARM_PATH}")

if(ARM_PATH)
	if(MINGW_LINUX)
		set(path "${ARM_PATH}/src/libarm.a")
		if(EXISTS ${path})
			set(path "${path}")
		endif()
	else()
		find_library(ARM_LIB arm PATHS "${ARM_PATH}/src" NO_DEFAULT_PATH)
	endif()
endif()

if(ARM_LIB)
	message(STATUS "ARM library found at ${ARM_LIB}")
else()
	message(STATUS "ARM library not found")
endif()


# looking for PPC loader
set(PPC_PATH "${CMAKE_SOURCE_DIR}/../ppc2" CACHE PATH "path to GLISS PPC path")
if(EXISTS "${PPC_PATH}")
	if(MINGW_LINUX)
		set(path "${PPC_PATH}/src/libppc.a")
		if(NOT EXISTS ${path})
			set(path PPC_LIB-NOTFOUND)
		endif()
		set(PPC_LIB "${path}" CACHE PATH "path to PPC library")
	else()
		find_library(PPC_LIB ppc PATHS "${PPC_PATH}/src" NO_DEFAULT_PATH)
	endif()
endif()
if(PPC_LIB)
	message(STATUS "PPC library found at ${PPC_LIB}")
else()
	message(STATUS "PPC library not found")
endif()


# look for lp_solve5
set(LP_SOLVE5_PATH "${CMAKE_SOURCE_DIR}/../lp_solve5" CACHE PATH "path to lp_solve5 path")
if(EXISTS "${LP_SOLVE5_PATH}")
	if(MINGW_LINUX)
		set(path "${LP_SOLVE5_PATH}/lpsolve55/liblpsolve55.a")
		if(NOT EXISTS ${path})
			set(path LP_SOLVE5_LIB-NOTFOUND)
		endif()
		set(LP_SOLVE5_LIB "${path}" CACHE PATH "path to lp_solve5 library")
	else()
		find_library(LP_SOLVE5_LIB lpsolve55 PATHS "${LP_SOLVE5_PATH}/lpsolve55" NO_DEFAULT_PATH)
	endif()
else()
    find_library(LP_SOLVE5_LIB NAMES liblpsolve55.so liblpsolve55_pic.a)
      FIND_PATH(LPSOLVE_INCLUDE_PATH lpsolve/lp_lib.h ${LPSOLVE_INCLUDE_PATH} ${LPSOLVE_INCLUDE_TRIAL_PATH})
      message(STATUS ${LPSOLVE_INCLUDE_PATH})
      include_directories(${LPSOLVE_INCLUDE_PATH}/lpsolve/)
endif()
if(LP_SOLVE5_LIB)
	message(STATUS "lp_solve5 library found at ${LP_SOLVE5_LIB}")
else()
	message(STATUS "lp_solve5 library not found")
endif()


# looking for CPLEX
if(CPLEX_ROOT)
    string(REPLACE "_" "-" x "${CMAKE_SYSTEM_PROCESSOR}")
    string(TOLOWER "${x}_${CMAKE_SYSTEM_NAME}" CPLEX_OS)
    set(CPLEX_LIB_PATH "${CPLEX_ROOT}/cplex/lib/${CPLEX_OS}/static_pic")
    find_library(CPLEX_ILOCPLEX_LIB    "ilocplex"       PATHS "${CPLEX_LIB_PATH}")
    find_library(CPLEX_CPLEX_LIB        "cplex"         PATHS "${CPLEX_LIB_PATH}")
    set(CPLEX_CONCERT_PATH "${CPLEX_ROOT}/concert/lib/${CPLEX_OS}/static_pic")
    find_library(CPLEX_CONCERT_LIB      "concert"       PATHS "${CPLEX_CONCERT_PATH}")
    if(CPLEX_CPLEX_LIB AND CPLEX_ILOCPLEX_LIB AND CPLEX_DISTMIP_LIB AND CPLEX_CONCERT_LIB)
        set(CPLEX_LIB "${CPLEX_ILOCPLEX_LIB}" "${CPLEX_CPLEX_LIB}" "${CPLEX_CONCERT_LIB}")
        message(STATUS "CPLEX found at ${CPLEX_LIB}")
        set(CPLEX_INCLUDE "${CPLEX_ROOT}/cplex/include" "${CPLEX_ROOT}/concert/include")
    endif()
endif()


# setting default ILP plugin
if(LP_SOLVE5_LIB)
    set(DEFAULT_ILP lp_solve5)
elseif(CPLEX_LIB)
    set(DEFAULT_ILP cplex)
endif()
if(DEFAULT_ILP)
    file(WRITE "default.eld"
"[elm-plugin]
path=$ORIGIN/${DEFAULT_ILP}
")
    install(FILES default.eld DESTINATION "${ILPDIR}")
endif()

# looking for version
find_program(HG_PATH hg)
if(HG_PATH)
    execute_process(
        COMMAND "${HG_PATH}" summary
        OUTPUT_VARIABLE OTAWA_VERSION
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE "parent: ([^:]+):.*" "\\1" OTAWA_VERSION "${OTAWA_VERSION}")
endif()
if(OTAWA_TAG)
    set(OTAWA_VERSION "${OTAWA_VERSION}-${OTAWA_TAG}")
endif()
message(STATUS "OTAWA version: ${OTAWA_VERSION}")


# compute the date
if(WIN32)
	execute_process(COMMAND "cmd" "/C date /T" OUTPUT_VARIABLE RESULT)
elseif(UNIX OR MINGW_LINUX)
	execute_process(COMMAND "date" "+%d/%m/%Y" OUTPUT_VARIABLE RESULT OUTPUT_STRIP_TRAILING_WHITESPACE)
endif(WIN32)
if(WIN32 AND NOT MINGW_LINUX)
    string(REGEX REPLACE "([0-9][0-9])/([0-9][0-9])/([0-9][0-9][0-9][0-9]).*" "\\1\\2\\3" RESULT ${RESULT})
endif()
set(OTAWA_DATE "${RESULT}")
#add_definitions(-DDAYDATE=\"${RESULT}\")
#	message(STATUS ${RESULT})
message(STATUS "OTAWA date: ${OTAWA_DATE}")

###########################
#adding Doxygen support
if(UNIX OR APPLE)
	#if using a unix system
	message(STATUS "Using Unix system, not MacOS")
	find_program(DOXYGEN doxygen
		/usr/local/bin
		/usr/bin
		)
elseif(WIN32 OR MINGW)
	#not tested
	message(STATUS "Using Win32 system")
	find_program(DOXYGEN doxygen
		PATH
		)
elseif(APPLE)
	#not tested either, and shall not test
	message(WARNING "MacOS not supported")
else(UNIX AND NOT APPLE)
	#in case of some more exotic OS
	message(WARNING "OS not supported")
endif()

#once Doxygen path has been searched for
#generation of documentation IF Doxygen has been found
#tried testing for DEFINED DOXYGEN_DIR, doesn't work
if(DOXYGEN AND WIN32)
	message(STATUS "Doxygen found, generation of documentation")
	execute_process(COMMAND "cmd" "/C doxygen Doxyfile")
elseif(DOXYGEN AND UNIX) #not tested
	message(STATUS "Doxygen found, generation of documentation")
	execute_process(COMMAND "bash" "doxygen Doxyfile")
else(DOXYGEN AND WIN32)
	message(WARNING "Doxygen not found, cannot generate documentation")
endif(DOXYGEN AND WIN32)

###########################


# build configuration file
configure_file (
  "${PROJECT_SOURCE_DIR}/config.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)


# linking to elm and gel libraries
# linking is hardcoded, but libraries will be searched for
# in all directories in PATH
if(MINGW_LINUX)
	set(LIBELM ${otawa_SOURCE_DIR}/../elm/src/libelm.dll)
	set(LIBGEL ${otawa_SOURCE_DIR}/../gel/src/libgel.dll)
	set(LIBGEL_DWARF ${otawa_SOURCE_DIR}/../gel/src/libgel_dwarf.dll)
elseif(WIN32)
	find_library(LIBELM elm PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../elm/src)
	find_library(LIBGEL gel PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../gel/src)
	find_library(LIBGEL_DWARF gel_dwarf PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../gel/src)
else()
	find_library(LIBELM elm PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../elm/src NO_SYSTEM_ENVIRONMENT_PATH)
	if(NOT LIBELM)
		message(FATAL_ERROR "libelm is mandatory!")
	else()
		message(STATUS "libelm found at ${LIBELM}")
		get_filename_component(dir "${LIBELM}" DIRECTORY)
		include_directories("${dir}/../include")
	endif()
	find_library(LIBGEL gel PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../gel/src NO_SYSTEM_ENVIRONMENT_PATH)
	if(NOT LIBGEL)
		message(FATAL_ERROR "libgel is mandatory!")
	else()
		message(STATUS "libgel found at ${LIBGEL}")
		get_filename_component(dir "${LIBGEL}" DIRECTORY)
		include_directories("${dir}/../include")
	endif()
	find_library(LIBGEL_DWARF gel_dwarf PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../gel/src NO_SYSTEM_ENVIRONMENT_PATH)
endif()


# add subdirectories
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(bin)


# share installation
add_subdirectory(data)

# testing
if(OTAWA_TEST)
	add_subdirectory(test)
endif()

# handle autodoc
if(DOXYGEN AND INSTALL_DOC)
	add_custom_target("make-autodoc" ALL DEPENDS "autodoc")
	add_custom_command(
		OUTPUT "autodoc"
		DEPENDS "Doxyfile"
		COMMAND "${DOXYGEN}"
	)
	install(DIRECTORY autodoc DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Otawa/")
endif()
