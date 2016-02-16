############################################################
#
# $Id$
#
# Copyright (c) bioImageLab 2015
#
# AUTHOR:
# Sylvain Prigent
# 

# Project name
project(blToolCore)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    model/blioDataInfo.h 
    model/blioDataList.h 
    model/blToolInfo.h 
    model/blToolIO.h 
    model/blToolParser.h 
    model/blioParameters.h 
    model/blToolParameters.h 
    model/blToolExec.h 
    model/blToolExecViewer.h 
    model/blToolExecLog.h 
    model/blToolParser.h
)

SET(SRCS_FILES
    model/blioDataInfo.cpp
    model/blioDataList.cpp 
    model/blToolInfo.cpp
    model/blToolIO.cpp
    model/blToolParser.cpp 
    model/blioParameters.cpp
    model/blToolParameters.cpp 
    model/blToolExec.cpp
    model/blToolExecViewer.cpp
    model/blToolExecLog.cpp
    model/blToolParser.cpp
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} Qt5::Xml Qt5::Widgets)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
