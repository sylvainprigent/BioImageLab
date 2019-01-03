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
project(blWidgets)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
  blHideableWidget.h
  blButtonId.h
  blButtonId2.h
  blMultipleLineEdit.h
  blMultipleComboBox.h
  blSearchBarWidget.h
  blFlowLayout.h
  blSlidingStackedWidget.h
  blClosableButton.h
  blWebBrowser.h
  blClickableIcon.h
  blBrowseBarWidget.h
  blTwoSideWidget.h
  blTwoSideLeftContainer.h
  blTwoSideRightContainer.h
  blTwoSidedContainer.h
  blImageView.h
  blHoverWidget.h
  blHoverableWidget.h
)

SET(SRCS_FILES
  blHideableWidget.cpp
  blButtonId.cpp
  blButtonId2.cpp
  blMultipleLineEdit.cpp
  blMultipleComboBox.cpp
  blSearchBarWidget.cpp
  blFlowLayout.cpp
  blSlidingStackedWidget.cpp
  blClosableButton.cpp
  blWebBrowser.cpp
  blClickableIcon.cpp
  blBrowseBarWidget.cpp
  blTwoSideWidget.cpp
  blTwoSideLeftContainer.cpp
  blTwoSideRightContainer.cpp
  blTwoSidedContainer.cpp
  blImageView.cpp
  blHoverWidget.cpp
  blHoverableWidget.cpp
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries( ${PROJECT_NAME} Qt5::Widgets Qt5::Xml Qt5::WebEngineWidgets)

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
