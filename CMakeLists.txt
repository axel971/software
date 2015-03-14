CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(application)


# Appeler automatique le moc quand nécessaire
SET(CMAKE_AUTOMOC ON)

# Les fichiers générés par le moc sont générés dans le dossier bin, dire à CMake de toujours
# inclure les entêtes de ce dossier
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Modules de Qt en dépendance
FIND_PACKAGE(Qt5 COMPONENTS Gui Core Widgets)

# librairie OpenCV
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

if(CONTRACTS EQUAL USE_ASSERT)
add_definitions(-DCONTRACTS_USE_ASSERT)
endif()

# Chercher les fichiers sources
FILE(
    GLOB_RECURSE
    FICHIERS_SOURCES
    source/*
)
FILE(
    GLOB_RECURSE
    UI_FILES	
    source/*.ui
)

# Support UI files
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} ${FICHIERS_SOURCES} ${UI_HEADER})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui)



