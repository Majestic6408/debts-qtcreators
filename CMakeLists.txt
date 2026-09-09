cmake_minimum_required(VERSION 3.16)
project(Lab4_Autos)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    MainWindow.cpp
    Car.cpp
)

set(HEADERS
    MainWindow.h
    Car.h
)

qt6_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(Lab4_Autos ${SOURCES} ${MOC_SOURCES})

target_link_libraries(Lab4_Autos Qt${QT_VERSION_MAJOR}::Widgets)

if(Qt6_FOUND)
    qt6_standard_project_setup()
endif()
