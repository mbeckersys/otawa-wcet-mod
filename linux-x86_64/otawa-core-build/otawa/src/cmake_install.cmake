# Install script for directory: /home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/prog/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/ast/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/branch/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/cat/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/ccg/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/cfgio/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/etime/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/ets/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/ocpp/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/odec/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/odisplay/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/dcache/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/arm2/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/ppc2/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/lp_solve5/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/config/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/dumpcfg/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/mkff/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/odfa/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/ostat/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/opcg/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/odisasm/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/owcet/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/bpred/cmake_install.cmake")
  include("/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core-build/otawa/src/oipet/cmake_install.cmake")

endif()

