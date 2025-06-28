cmake_minimum_required(VERSION 3.30)
project(cxxorm VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cxxorm)
add_subdirectory(util)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PQXX_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PQXX_INCLUDE_DIRS})
