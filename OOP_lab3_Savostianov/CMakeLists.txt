cmake_minimum_required(VERSION 3.16)

project(OOP_lab3_Savostianov LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(OOP_lab3_Savostianov
  Department_Savostianov.cpp
  BooleanFuncs.cpp
  Employee_Savostianov.cpp
  OOP_lab2_Savostianov.cpp
  Department_Savostianov.h
  Employee_Savostianov.h
  BooleanFuncs.h
)

target_link_libraries(OOP_lab3_Savostianov
    Qt${QT_VERSION_MAJOR}::Core
)

include(GNUInstallDirs)
install(TARGETS OOP_lab3_Savostianov
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Boost configuration
if(NOT DEFINED BOOST_ROOT)
    set(BOOST_ROOT "D:/cpp_libs/boost_1_86_0")
endif()

set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS serialization wserialization)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(OOP_lab3_Savostianov Boost::serialization)
    target_link_libraries(OOP_lab3_Savostianov Boost::wserialization)
else()
    message(FATAL_ERROR "Boost libraries not found!")
endif()
