############################################################
#
# $Id$
#
# Copyright (c) bioImageLab 2018
#
# AUTHOR:
# Sylvain Prigent
# 

# Project name
project(blProjectBrowser)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    controller/blProjectBrowserController.h
    view/blProjectBrowserWidget.h
    view/blProjectBrowserWidgetToolBar.h
    view/blProjectBrowserWidgetList.h
)

SET(SRCS_FILES
    controller/blProjectBrowserController.cpp
    view/blProjectBrowserWidget.cpp
    view/blProjectBrowserWidgetToolBar.cpp
    view/blProjectBrowserWidgetList.cpp
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} blCore blWidgets blProjectCore Qt5::Sql Qt5::Xml Qt5::WebEngineWidgets Qt5::Widgets)

## #################################################################
## Export header file
## #################################################################

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
