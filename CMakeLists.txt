#-------------------------------------------------------------------------------
# Copyright (c) 2021, Alamy Liu. All rights reserved.
#
# SPDX-License-Identifier: GPL-2.0
#
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.15)


set(PROJECT_NAME ardesia)
set(PROJECT_VERSION 1.2)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

message(STATUS CMAKE_CURRENT_DIR = ${CMAKE_CURRENT_DIR})
message(STATUS CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX})
message(STATUS CMAKE_INSTALL_BINDIR = ${CMAKE_INSTALL_BINDIR})

############################ CONFIGURATION #####################################

# The default build type is release. If debug symbols are needed then
# -DCMAKE_BUILD_TYPE=debug should be used (likewise with other build types)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type: [Debug, Release, RelWithDebInfo, MinSizeRel]" FORCE)
endif()

############################### Compiler configuration #########################



############################ Config Check ######################################

#include(${CMAKE_SOURCE_DIR}/config/check_config.cmake)


################################################################################

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C)

configure_file(config.h.in config.h)

find_package(PkgConfig)
pkg_check_modules(GSL REQUIRED gsl)
pkg_check_modules(GTK3 REQUIRED "gtk+-3.0 >= 3.22")
pkg_check_modules(LIBGSF REQUIRED libgsf-1)
pkg_check_modules(LIBRSVG REQUIRED librsvg-2.0)
pkg_check_modules(LIBXML REQUIRED libxml-2.0)
pkg_check_modules(X11 REQUIRED x11)


set(SRC_PATH src)
set(SOURCES
    ${SRC_PATH}/annotation_window.c
    ${SRC_PATH}/annotation_window_callbacks.c
    ${SRC_PATH}/ardesia.c
    ${SRC_PATH}/background_window.c
    ${SRC_PATH}/background_window_callbacks.c
    ${SRC_PATH}/bar.c
    ${SRC_PATH}/bar_callbacks.c
    ${SRC_PATH}/bezier_spline.c
    ${SRC_PATH}/broken.c
    ${SRC_PATH}/color_chooser.c
    ${SRC_PATH}/crash_dialog.c
    ${SRC_PATH}/crash_dialog_callbacks.c
    ${SRC_PATH}/cursors.c
    ${SRC_PATH}/fill.c
    ${SRC_PATH}/info_dialog.c
    ${SRC_PATH}/input.c
    ${SRC_PATH}/iwb_loader.c
    ${SRC_PATH}/iwb_saver.c
    ${SRC_PATH}/keyboard.c
    ${SRC_PATH}/pdf_saver.c
    ${SRC_PATH}/preference_dialog.c
    ${SRC_PATH}/preference_dialog_callbacks.c
    ${SRC_PATH}/project_dialog.c
    ${SRC_PATH}/project_dialog_callbacks.c
    ${SRC_PATH}/recorder.c
    ${SRC_PATH}/saver.c
    ${SRC_PATH}/share_confirmation_dialog.c
    ${SRC_PATH}/share_confirmation_dialog_callbacks.c
    ${SRC_PATH}/text_window.c
    ${SRC_PATH}/utils.c
    ${SRC_PATH}/windows_utils.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        HAVE_CONFIG_H
        GTK_DISABLE_SINGLE_INCLUDES
        GTK_DISABLE_DEPRECATED
        GDK_DISABLE_DEPRECATED
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_BINARY_DIR}   # to find config.h
        ${GNUInstallDirs}
        ${GSL_INCLUDE_DIRS}
        ${GTK3_INCLUDE_DIRS}
        ${LIBGSF_INCLUDE_DIRS}
        ${LIBRSVG_INCLUDE_DIRS}
        ${LIBXML_INCLUDE_DIRS}
        ${X11_INCLUDE_DIRS}
        ${SRC_PATH}
)

# $<$<C_COMPILER_ID:GNU>:-export-dynamic>

target_link_options(${PROJECT_NAME}
    PRIVATE
        -export-dynamic
)

target_link_libraries(${PROJECT_NAME}
        ${GSL_LIBRARIES}
        ${GTK3_LIBRARIES}
        ${LIBGSF_LIBRARIES}
        ${LIBRSVG_LIBRARIES}
        ${LIBXML_LIBRARIES}
        ${X11_LIBRARIES}
)


######################### Generate Debian package ##############################

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

SET(CPACK_GENERATOR "DEB")
SET(CPAKC_DEBIAN_PACKAGE_MAINTAINER "cmake")
INCLUDE(CPack)

