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
project(blFinder)

## #################################################################
## Define files
## #################################################################
SET(HEADERS_FILES
    view/blFinderAdminBar.h
    view/blFinderAdminAuthorTable.h
    view/blFinderAdminAuthorEdit.h
    view/blFinderAdminCategoriesTable.h
    view/blFinderAdminCategoryEdit.h
    view/blFinderAdminOriginsTable.h
    view/blFinderAdminOriginEdit.h
    view/blFinderAdminKeywordsTable.h
    view/blFinderAdminKeywordEdit.h
    view/blFinderAdminSectionsTable.h
    view/blFinderAdminSectionEdit.h
    view/blFinderAdminSectionsLinksTable.h
    view/blFinderAdminSectionsLinkEdit.h
    view/blFinderAdminTutorialsLinksTable.h
    view/blFinderAdminTutorialsLinkEdit.h
    view/blFinderAdminTutorialEdit.h
    view/blFinderAdminTutorialsTable.h
    view/blFinderItem.h
    view/blFinderItemList.h
    view/blFinderBar.h
    view/blFinderBrowser.h
    view/blFinderTutorialView.h
    model/blFinderAuthorInfo.h
    model/blFinderCategoryInfo.h
    model/blFinderOriginInfo.h
    model/blFinderKeywordInfo.h
    model/blFinderDatabase.h
    model/blFinderAccess.h
    model/blFinderDatabase.h
    model/blFinderSectionInfo.h
    model/blFinderSectionsLinkInfo.h
    model/blFinderTutorialsLinkInfo.h
    model/blFinderTutorialInfo.h
    model/blSingleton.h
    controller/blFinderDefaultWidget.h
    controller/blFinderAdminDefaultWidget.h
)

SET(SRCS_FILES
    view/blFinderAdminBar.cpp
    view/blFinderAdminAuthorTable.cpp
    view/blFinderAdminAuthorEdit.cpp
    view/blFinderAdminCategoriesTable.cpp
    view/blFinderAdminCategoryEdit.cpp
    view/blFinderAdminOriginsTable.cpp
    view/blFinderAdminOriginEdit.cpp
    view/blFinderAdminKeywordsTable.cpp
    view/blFinderAdminKeywordEdit.cpp
    view/blFinderAdminSectionsTable.cpp
    view/blFinderAdminSectionEdit.cpp
    view/blFinderAdminSectionsLinksTable.cpp
    view/blFinderAdminSectionsLinkEdit.cpp
    view/blFinderAdminTutorialsLinksTable.cpp
    view/blFinderAdminTutorialsLinkEdit.cpp
    view/blFinderAdminTutorialEdit.cpp
    view/blFinderAdminTutorialsTable.cpp
    view/blFinderItem.cpp
    view/blFinderItemList.cpp
    view/blFinderBar.cpp
    view/blFinderBrowser.cpp
    view/blFinderTutorialView.cpp
    model/blFinderAuthorInfo.cpp
    model/blFinderCategoryInfo.cpp
    model/blFinderOriginInfo.cpp
    model/blFinderKeywordInfo.cpp
    model/blFinderDatabase.cpp
    model/blFinderAccess.cpp
    model/blFinderDatabase.cpp
    model/blFinderSectionInfo.cpp
    model/blFinderSectionsLinkInfo.cpp
    model/blFinderTutorialsLinkInfo.cpp
    model/blFinderTutorialInfo.cpp
    controller/blFinderDefaultWidget.cpp
    controller/blFinderAdminDefaultWidget.cpp
)

## #################################################################
## Lib Bin generation
## #################################################################
add_library(${PROJECT_NAME} ${SRCS_FILES} ${HEADERS_FILES} ${TEMPLATES_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries( ${PROJECT_NAME} blWidgets Qt5::Widgets Qt5::Sql Qt5::WebKitWidgets)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")
