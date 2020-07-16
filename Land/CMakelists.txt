#######################################################################################################################
#  COPYRIGHT
#  -------------------------------------------------------------------------------------------------------------------
#  \verbatim
#  Copyright (c) 2020 by Youngho Kim.                                                  All rights reserved.
#
#                This software is copyright protected and proprietary to Youngho Kim.
#  -------------------------------------------------------------------------------------------------------------------
#  FILE DESCRIPTION
#  -----------------------------------------------------------------------------------------------------------------*/
#
#         \file  CMakeLists.txt
#        \brief  This file is part of the CMake build-configuration.
#
#      \details  This file is part of the CMake build-configuration.
#
#######################################################################################################################

#######################################################################################################################
#  REVISION HISTORY
#  -------------------------------------------------------------------------------------------------------------------
#  Refer to the module's ChangeHistory.txt
#
#
#  FILE VERSION
#  -------------------------------------------------------------------------------------------------------------------
#  The file version is identical to the component version. To determine the actual version of the component,
#  see the technical reference.
#
#######################################################################################################################

cmake_minimum_required(VERSION 3.17)

project(
  land-expect
  LANGUAGES CXX
)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER g++)

# Add subdirectories to the build.
add_subdirectory(src)
