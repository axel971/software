CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(main)

#FIND_PACKAGE(Qt5 COMPONENTS Gui Core Widgets)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Je trouve qu'il vaut mieux lister les fichiers histoire d'être sûrs des fichiers traités
FILE(
    GLOB_RECURSE
    FICHIERS_SOURCES
    source/*
)

ADD_EXECUTABLE(${PROJECT_NAME} ${FICHIERS_SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})




