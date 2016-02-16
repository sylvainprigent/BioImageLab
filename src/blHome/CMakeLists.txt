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
project(blHome)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    model/blHomeTileInfo.h
    view/blHomeWidget.h
    view/blHomeWidgetBar.h
    view/blHomeWidgetTile.h
    view/blHomeSettingsView.h
    view/blHomeSettingsGroupView.h
    controller/blHomeDefaultWidget.h
)

SET(SRCS_FILES
    model/blHomeTileInfo.cpp
    view/blHomeWidget.cpp
    view/blHomeWidgetTile.cpp
    view/blHomeWidgetBar.cpp
    view/blHomeSettingsView.cpp
    view/blHomeSettingsGroupView.cpp
    controller/blHomeDefaultWidget.cpp

)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} blCore blWidgets Qt5::Widgets)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
