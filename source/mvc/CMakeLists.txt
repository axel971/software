CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(main)

# Appeler automatique le moc quand nécessaire
SET(CMAKE_AUTOMOC ON)

# Les fichiers générés par le moc sont générés dans le dossier bin, dire à CMake de toujours
# inclure les entêtes de ce dossier
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Modules de Qt en dépendance
FIND_PACKAGE(Qt5 COMPONENTS Gui Core Widgets)

# Je trouve qu'il vaut mieux lister les fichiers histoire d'être sûrs des fichiers traités
FILE(
    GLOB_RECURSE
    FICHIERS_SOURCES
    source/*
)

ADD_EXECUTABLE(${PROJECT_NAME} ${FICHIERS_SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)

# Support UI files
qt5_wrap_ui(source/ui_MainWindow.h source/MainWindow.ui)


