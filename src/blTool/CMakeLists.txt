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
project(blTool)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    controller/blToolDefaultWidget.h 
    model/blToolHistoryBrowser.h
    view/blToolIOPluginInterface.h
    view/blToolExecGui.h 
    view/blToolInputSelectorWidget.h 
    view/blToolInputWidget.h 
    view/blToolParameterSelectorWidget.h 
    view/blToolRunWidget.h 
    view/blToolHistoryBar.h 
    view/blToolHistoryBarWidget.h 
    view/blToolHistoryInfo.h 
    view/blToolHistoryWidget.h 
    view/blToolHistoryWidgetList.h 
    view/blToolDocWidget.h 
    view/blToolStandardOutputViewer.h
    view/blToolInputSelectorWidgetInterface.h
    view/blToolInputSelectorWidgetFile.h
    view/blToolInputSelectorWidgetDir.h
)

SET(SRCS_FILES
    controller/blToolDefaultWidget.cpp 
    model/blToolHistoryBrowser.cpp
    view/blToolExecGui.cpp 
    view/blToolInputSelectorWidget.cpp 
    view/blToolInputWidget.cpp
    view/blToolParameterSelectorWidget.cpp 
    view/blToolRunWidget.cpp 
    view/blToolHistoryBar.cpp 
    view/blToolHistoryBarWidget.cpp 
    view/blToolHistoryInfo.cpp 
    view/blToolHistoryWidget.cpp 
    view/blToolHistoryWidgetList.cpp 
    view/blToolDocWidget.cpp 
    view/blToolStandardOutputViewer.cpp
    view/blToolInputSelectorWidgetInterface.cpp
    view/blToolInputSelectorWidgetFile.cpp
    view/blToolInputSelectorWidgetDir.cpp
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} blToolCore blWidgets Qt5::Xml Qt5::WebKit Qt5::WebKitWidgets Qt5::Widgets)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
