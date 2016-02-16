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
project(bioseApps)

## #################################################################
## Exe generation
## #################################################################
SET(NAME bioseApp)
SET(FILE bioseApp.cpp bioseController.cpp bioseController.h)
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blCore blHome blFinder blToolCore blTool)
