# Управление флагами компиляции языка С++.

IF (NOT CMAKE_CXX_COMPILER MATCHES cl)
  #if C++ comiler is g++, then...
  EXEC_PROGRAM(${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE GCC_VERSION)
  MESSAGE(STATUS "GCC_VERSION " ${GCC_VERSION})
  IF ( (GCC_VERSION MATCHES gcc) OR (GCC_VERSION MATCHES "g[+][+]") OR (GCC_VERSION MATCHES "c[+][+]"))
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -Wextra -O0")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -march=native")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
    MESSAGE(STATUS "CMAKE_CXX_FLAGS" ${CMAKE_CXX_FLAGS})
  ENDIF ()
ENDIF (NOT CMAKE_CXX_COMPILER MATCHES cl)
