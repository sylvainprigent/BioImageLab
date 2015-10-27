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
project(blToolApp)

## #################################################################
## Exe generation
## #################################################################
SET(NAME blToolApp)
SET(FILE blToolApp.cpp )
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blTool blWidgets)
