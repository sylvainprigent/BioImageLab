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
project(blProjectApps)

## #################################################################
## Exe generation
## #################################################################
SET(NAME blProjectApp)
SET(FILE blProjectApp.cpp )
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blProject)
