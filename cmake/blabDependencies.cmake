############################################################
#
# $Id$
#
# Copyright (c) bioImageLab 2015
#
# AUTHOR:
# Sylvain Prigent
# 

## #################################################################
## Qt5
## #################################################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED) 
find_package(Qt5Xml REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)
find_package(Qt5Sql REQUIRED)

## #################################################################
## Doxygen
## #################################################################
find_package(Doxygen QUIET)
if(${DOXYGEN_FOUND})
  set(blab_USE_DOXYGEN 1)
endif(${DOXYGEN_FOUND})
