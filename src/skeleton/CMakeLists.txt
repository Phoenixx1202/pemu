cmake_minimum_required(VERSION 3.10)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(cross2dui)

#################
# libcross2dui
#################
include(FindPkgConfig)

set(CROSS2DUI_INCLUDE ..)
file(GLOB CROSS2DUI_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c*
        ${CMAKE_CURRENT_SOURCE_DIR}/skin/*.c*
)

set(FLAGS -D__SSCRAP__)

if (OPTION_UPDATE_CONFIG)
    list(APPEND FLAGS -D__UPDATE_CONFIG__)
endif ()

if (OPTION_FULLSCREEN)
    list(APPEND FLAGS -D__FULLSCREEN__)
endif ()

if (OPTION_MPV_PLAYER)
    pkg_search_module(MPV REQUIRED mpv)
    list(APPEND CROSS2DUI_INCLUDE ${MPV_INCLUDE_DIRS})
    list(APPEND LDFLAGS ${MPV_LIBRARIES})
    list(APPEND FLAGS -D__MPV__)
endif ()

# minizip
pkg_search_module(MINIZIP minizip)
if (MINIZIP_FOUND)
    list(APPEND CROSS2DUI_INCLUDE ${MINIZIP_INCLUDE_DIRS})
    list(APPEND LDFLAGS ${MINIZIP_LIBRARIES})
else ()
    message(WARNING "minizip not found, using embedded one...")
    list(APPEND CROSS2DUI_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external)
    list(APPEND CROSS2DUI_SOURCE
            ${CMAKE_CURRENT_SOURCE_DIR}/external/minizip/ioapi.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/minizip/zip.c
            ${CMAKE_CURRENT_SOURCE_DIR}/external/minizip/unzip.c)
    list(APPEND FLAGS -DIOAPI_NO_64 -DUSE_FILE32API)
endif ()

##########################
# libcross2dui
##########################
add_library(${PROJECT_NAME} STATIC ${CROSS2DUI_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${CROSS2DUI_INCLUDE})
target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
target_link_libraries(${PROJECT_NAME} cross2d sscrap ${LDFLAGS})
