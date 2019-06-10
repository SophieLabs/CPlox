cmake_minimum_required(VERSION 3.12.0)
project(cplox CXX)

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Default locations to search for on various platforms.
list(APPEND SEARCH_LIBS /usr/lib)
list(APPEND SEARCH_LIBS /usr/local/lib)
list(APPEND SEARCH_LIBS /usr/local/homebrew/lib) # Mac OS X
list(APPEND SEARCH_LIBS /opt/local/lib)

list(APPEND SEARCH_HEADERS /usr/include)
list(APPEND SEARCH_HEADERS /usr/local/include)
list(APPEND SEARCH_HEADERS /usr/local/homebrew/include) # Mac OS X
list(APPEND SEARCH_HEADERS /opt/local/include)

# Change the default build type from Debug to Release, while still
# supporting overriding the build type.
#
# The CACHE STRING logic here and elsewhere is needed to force CMake
# to pay attention to the value of these variables.
if(NOT CMAKE_BUILD_TYPE)
  message("-- No build type specified; defaulting to CMAKE_BUILD_TYPE=Release.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: \
    None Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
endif()

# C++17 support.
include(EnableCPP17.cmake)

set(MY_LIBRARY_DEPENDENCIES)

#
# gcc settings.
#
if(CMAKE_COMPILER_IS_GNUCXX)
  # No warnings for C.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-sign-compare \
    -Wno-unused-parameter -fpic")
endif()

#
# Clang settings
#
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-sign-compare \
    -Wno-unused-parameter -fpic")
endif()

#
# MSVC settings
#
if(MSVC)
  # Disable deprecation warning for standard functions.
  add_definitions("/wd4996")
  # To get rid of annoying min and max macros if windows.h
  # is included.
  add_definitions("-DNOMINMAX=1")
  # Get rid of annoying windows.h GetObject definition
  #ADD_DEFINITIONS("-D_M_CEE")
  add_definitions("-D_VARIADIC_MAX=6")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

#
# Function for unrolling directory structure into filters in VS
#
function(getdirlist curDir result)
  file(GLOB children RELATIVE ${curDir} ${curDir}/*)
  set(dirList "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curDir}/${child})
      list(APPEND dirList ${child})
    endif()
  endforeach()
  set(${result} ${dirList} PARENT_SCOPE)
endfunction()

set(src_suffix "src")
set(include_suffix "include")

set(suffixes "${src_suffix};${include_suffix}")

set(fileList "")
# For each suffix, get all the subfolders, grab all files in each subfolder
# and set up a filter in VS for them. Also add all files to the fileList
# variable for adding to the project
foreach(suffix ${suffixes})
  set(MRCPP_DIR_${suffix} "${CMAKE_CURRENT_SOURCE_DIR}/${suffix}")
  getdirlist(${MRCPP_DIR_${suffix}} "${suffix}Dirs")

  foreach(dir ${${suffix}Dirs})
    file(GLOB_RECURSE "${suffix}_${dir}_files"
      "${MRCPP_DIR_${suffix}}/${dir}/*")
    list(APPEND fileList ${${suffix}_${dir}_files})
    source_group(${suffix}\\${dir} FILES ${${suffix}_${dir}_files})
  endforeach()
endforeach()

file(GLOB HPP_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB SRC_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp")

#
# Include directories
#
include_directories(${CMAKE_SOURCE_DIR})

#
# Compile the source code separately so that it can be reused
# in both the main executable and the unit tests. Need to ignore
# main.cpp here as it defines int main()
#
list(FILTER SRC_MAIN EXCLUDE REGEX ".*main.cpp$")
add_library(objfiles OBJECT ${SRC_MAIN})
target_include_directories(objfiles PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)
# target_include_directories(objfiles
#   PRIVATE ${CMAKE_SOURCE_DIR}/external)

#
# Build main executable
#
add_executable(cplox
  $<TARGET_OBJECTS:objfiles>
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${HPP_MAIN}
  ${fileList})
target_include_directories(cplox
  PRIVATE ${CMAKE_SOURCE_DIR}/external)
source_group("src" FILES ${SRC_MAIN})
source_group("include" FILES ${HPP_MAIN})

# add_definitions("-DFMT_HEADER_ONLY")

#
# Compile unit tests.
#
# file(GLOB TEST_SRC_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/*cpp")
# list(FILTER TEST_SRC_MAIN EXCLUDE REGEX ".*main.cpp$")

# add_library(Catch INTERFACE)
# target_include_directories(Catch INTERFACE
  # "${CMAKE_CURRENT_SOURCE_DIR}/external/catch2")

# add_library(test-main OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/main.cpp)
# target_link_libraries(test-main Catch)

# add_executable(cplox-test
#   $<TARGET_OBJECTS:objfiles> # Object files from main executable
#   $<TARGET_OBJECTS:test-main> # unit_tests/main.o
#   ${TEST_SRC_MAIN}) # All tests
# target_link_libraries(cplox-test Catch)
# target_include_directories(cplox-test PUBLIC
#   "${CMAKE_CURRENT_SOURCE_DIR}/external")
# enable_testing()
# add_test(NAME CploxTests COMMAND cplox-test)
