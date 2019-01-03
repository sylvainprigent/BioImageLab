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
project(blProject)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    controller/blProjectWidget.cpp
    model/blProjectDatabase.cpp
    model/blProjectInfo.cpp
    model/blProjectFolderFilter.cpp
    model/blProjectFolderLabelExtractor.cpp
    model/blFileSearch.cpp
    model/blProjectModel.cpp
    model/blProjectModelMainColumn.cpp
    model/blProjectModelColumn.cpp
    model/blProjectAccess.cpp
    model/blCreateMiniature.cpp
    view/blProjectControler.cpp
    view/blProjectBrowserWidget.cpp
    view/blProjectBrowserWidgetToolBar.cpp 
    view/blProjectBrowserWidgetList.cpp 
    view/blProjectNewFormWidget.cpp
    view/blProjectNewFormWidgetLabel.cpp 
    view/blProjectNewFormWidgetImport.cpp 
    view/blProjectNewFormWidgetFilter.cpp
    view/blProjectNewFormWidgetDescription.cpp 
    view/blProjectNewFormWidgetFilterSingle.cpp 
    view/blProjectView.cpp
    view/blProjectViewColumn.cpp
    view/blProjectViewColumnSelector.cpp 
    view/blProjectViewColumnParameters.cpp
    view/blProjectViewColumnHeader.cpp
    view/blProjectViewTab.cpp 
    view/blProjectAddImageWidget.cpp
    view/blProjectSplitLabelWidget.cpp
    view/blProjectLabelSplitter.cpp
    view/blProjectAddRemoveSubColumnWidget.cpp
)

SET(SRCS_FILES
    controller/blProjectWidget.h
    model/blProjectDatabase.h
    model/blProjectInfo.h
    model/blProjectFolderFilter.h
    model/blProjectFolderLabelExtractor.h
    model/blFileSearch.h
    model/blProjectModel.h
    model/blProjectModelMainColumn.h
    model/blProjectModelColumn.h
    model/blProjectAccess.h
    model/blCreateMiniature.h
    view/blProjectControler.h
    view/blProjectBrowserWidget.h
    view/blProjectBrowserWidgetToolBar.h 
    view/blProjectBrowserWidgetList.h 
    view/blProjectNewFormWidget.h
    view/blProjectNewFormWidgetLabel.h 
    view/blProjectNewFormWidgetImport.h 
    view/blProjectNewFormWidgetFilter.h
    view/blProjectNewFormWidgetDescription.h 
    view/blProjectNewFormWidgetFilterSingle.h 
    view/blProjectView.h
    view/blProjectViewColumn.h
    view/blProjectViewColumnSelector.h 
    view/blProjectViewColumnParameters.h
    view/blProjectViewColumnHeader.h
    view/blProjectViewTab.h 
    view/blProjectAddImageWidget.h
    view/blProjectSplitLabelWidget.h
    view/blProjectLabelSplitter.h
    view/blProjectAddRemoveSubColumnWidget.h
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

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
