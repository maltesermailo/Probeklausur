cmake_minimum_required(VERSION 3.14)

project(Probeklausur LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Probeklausur
  main.cpp
  mysports.h mysports.cpp
  athlete.h athlete.cpp
  runner.h runner.cpp
  trainer.h trainer.cpp
  swimmer.h swimmer.cpp
  mysportscli.h mysportscli.cpp
)
target_link_libraries(Probeklausur Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS Probeklausur
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
