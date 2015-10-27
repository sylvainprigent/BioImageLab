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
project(blHomeApps)

## #################################################################
## Exe generation
## #################################################################
SET(NAME blHomeApp)
SET(FILE blHomeApp.cpp )
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blHome)
