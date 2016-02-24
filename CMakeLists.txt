############################################################
#
#
# Copyright (c) BioImageLab 2015
#
# AUTHOR:
# Sylvain Prigent
# 

## #################################################################
## Header
## #################################################################

cmake_minimum_required(VERSION 2.8)

#cmake_policy(SET CMP0048 OLD)
#cmake_policy(SET CMP0028 OLD)
#cmake_policy(SET CMP0020 OLD)
#cmake_policy(SET CMP0043 OLD)
project(blab)

set(${PROJECT_NAME}_VERSION_MAJOR 0 CACHE STRING "blab major version number." FORCE)
set(${PROJECT_NAME}_VERSION_MINOR 0 CACHE STRING "blab minor version number." FORCE)
set(${PROJECT_NAME}_VERSION_BUILD 1 CACHE STRING "blab build version number." FORCE)
set(${PROJECT_NAME}_VERSION
  "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)

## #################################################################
## Config file
## #################################################################

# Cmake config file directory path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(blabBuild)
include(blabDependencies)

## #################################################################
## Define Internal Architecture (for includes)
## #################################################################
add_subdirectory( app )
add_subdirectory( src )

## #################################################################
## Build Documentation
## #################################################################
IF ( ${blab_USE_DOXYGEN} )
  message(STATUS "Using Doxygen")
  SET( EXCLUDE_FROM_DOC_PATTERNS "*/external/*" )
  SET( DOC_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc)
  SET( DOC_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
  
  configure_file( cmake/Doxyfile.in 
    ${DOC_OUTPUT_DIR}/Doxyfile
    @ONLY
    )
  
  add_custom_target( doc
    ${DOXYGEN_EXECUTABLE} ${DOC_OUTPUT_DIR}/Doxyfile
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
ELSE( ${blab_USE_DOXYGEN} )
  message(STATUS "Not Using Doxygen")
ENDIF( ${blab_USE_DOXYGEN} )
