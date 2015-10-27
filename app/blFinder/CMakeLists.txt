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
project(blFinderApps)

## #################################################################
## Exe generation
## #################################################################
SET(NAME blFinderAdminApp)
SET(FILE blFinderAdminApp.cpp )
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blFinder)

SET(NAME blFinderApp)
SET(FILE blFinderApp.cpp )
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} Qt5::Widgets blFinder)
