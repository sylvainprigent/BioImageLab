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
project(blProjectnew)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    controller/blProjectBrowserController.cpp
    controller/blProjectController.cpp
    model/blProjectDatabase.cpp
    model/blProjectInfo.cpp
    model/blProjectAccess.cpp
    model/blProjectTypes.cpp
    model/blProjectTagsInfo.cpp
    model/blProjectModel.cpp
    model/blProjectIndex.cpp
    model/blImportDataInfo.cpp
    model/blMainColumnInfo.cpp
    model/blSubColumnInfo.cpp
    view/blProjectBrowserWidget.cpp
    view/blProjectBrowserWidgetToolBar.cpp 
    view/blProjectBrowserWidgetList.cpp 
    view/blProjectInfoForm.cpp
    view/blProjectImportConditionalView.cpp
    view/blTagsWidget.cpp
    view/blProjectDataView.cpp
    view/HierarchicalHeaderView.cpp
    model/blTagsInfo.cpp
    model/blDataInfo.cpp
)

SET(SRCS_FILES
    controller/blProjectBrowserController.h
    controller/blProjectController.h
    model/blProjectDatabase.h
    model/blProjectInfo.h
    model/blProjectAccess.h
    model/blProjectTypes.h
    model/blProjectModel.h
    model/blProjectTagsInfo.h
    model/blProjectIndex.h
    model/blImportDataInfo.h
    view/blProjectBrowserWidget.h
    view/blProjectBrowserWidgetToolBar.h 
    view/blProjectBrowserWidgetList.h 
    view/blProjectInfoForm.h
    model/blMainColumnInfo.h
    model/blSubColumnInfo.h
    view/blProjectImportConditionalView.h
    view/blTagsWidget.h
    view/blProjectDataView.h
    view/HierarchicalHeaderView.h
    model/blTagsInfo.h
    model/blDataInfo.h
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} blCore blToolCore blWidgets Qt5::Sql Qt5::Xml Qt5::WebEngineWidgets Qt5::Widgets)

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
