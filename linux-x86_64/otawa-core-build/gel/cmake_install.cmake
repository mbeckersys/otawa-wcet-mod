# Install script for directory: /home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/include/gel" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/CVS$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core/share/GEL/README;/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core/share/GEL/COPYING;/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core/share/GEL/AUTHORS")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core/share/GEL" TYPE FILE FILES
    "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/README"
    "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/COPYING"
    "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/AUTHORS"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core/share/GEL//autodoc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core/share/GEL/" TYPE DIRECTORY FILES "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/autodoc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/src/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/test/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/tools/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/gel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
