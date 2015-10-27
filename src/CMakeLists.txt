############################################################
#
# $Id$
#
# Copyright (c) BioImageLab 2015
#
# AUTHOR:
# Sylvain Prigent
# 

## #################################################################
## Options
## #################################################################
option(blab_BUILD_BLWIDGETS "Build blWidgets" true)
option(blab_BUILD_BLTOOL "Build blTool" true)

## #################################################################
## Add subdirectory
## #################################################################
add_subdirectory( blFinder )
add_subdirectory( blHome )
add_subdirectory( blTool )
add_subdirectory( blWidgets )
