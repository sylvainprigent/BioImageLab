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
project(blProjectEditor)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    controller/blProjectEditorController.h
    controller/blProjectNewController.h
    view/blProjectEditorWidget.h
    view/blProjectEditorInfoWidget.h
    view/blProjectEditorToolbarWidget.h
    view/blProjectEditorTableWidget.h
    view/blProjectEditorFooterWidget.h
    view/blProjectEditorTagsWidget.h
    model/blProjectTag.h
    model/blProjectTagDatabase.h
)

SET(SRCS_FILES
    controller/blProjectEditorController.cpp
    controller/blProjectNewController.cpp
    view/blProjectEditorWidget.cpp
    view/blProjectEditorInfoWidget.cpp
    view/blProjectEditorToolbarWidget.cpp
    view/blProjectEditorTableWidget.cpp
    view/blProjectEditorFooterWidget.cpp
    view/blProjectEditorTagsWidget.cpp
    model/blProjectTag.cpp
    model/blProjectTagDatabase.cpp
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} blCore blProjectCore blWidgets Qt5::Sql Qt5::Xml Qt5::WebEngineWidgets Qt5::Widgets)

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
