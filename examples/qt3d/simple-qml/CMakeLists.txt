# Generated from simple-qml.pro.

cmake_minimum_required(VERSION 3.14)
project(simple-qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_EXAMPLEDIR "examples")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Qml)
find_package(Qt6 COMPONENTS Quick)

add_qt_gui_executable(simple-qml
    main.cpp
)
target_link_libraries(simple-qml PUBLIC
    Qt::3DCore
    Qt::3DInput
    3DLogic
    Qt::3DQuick
    Qt::3DQuickExtras
    Qt::3DRender
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)


# Resources:
set(simple-qml_resource_files
    "main.qml"
)

qt6_add_resources(simple-qml "simple-qml"
    PREFIX
        "/"
    FILES
        ${simple-qml_resource_files}
)

target_sources(simple-qml PRIVATE ${simple-qml_resource_files})

install(TARGETS simple-qml
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
