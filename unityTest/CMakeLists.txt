CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(test)

# librairie OpenCV
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

#cppUnit library
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

FIND_PACKAGE(CppUnit REQUIRED)
include_directories( ${CppUnit_INCLUDE_DIRS})

# Chercher les fichiers sources
FILE(
    GLOB_RECURSE
    FICHIERS_SOURCES
    ./source/*
    ../source/detector/*
    ../source/imagePyramid/*		
)

ADD_EXECUTABLE(${PROJECT_NAME} ${FICHIERS_SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} ${CppUnit_LIBRARIES})



