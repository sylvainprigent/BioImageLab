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
project(blLab)

## #################################################################
## Exe generation
## #################################################################
SET(NAME blLab)
SET(FILE blLabApp.cpp blLabController.cpp blLabController.h)
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blCore blHome blFinder blToolCore blTool blProject)
