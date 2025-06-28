set(SOURCES
        ${CMAKE_SOURCE_DIR}/cxxorm/src/postgresql.cpp
        ${CMAKE_SOURCE_DIR}/cxxorm/inc/postgresql.h
        ${CMAKE_SOURCE_DIR}/cxxorm/inc/connection.h
        ${CMAKE_SOURCE_DIR}/cxxorm/inc/concepts.h
        ${CMAKE_SOURCE_DIR}/cxxorm/inc/util.h

        CACHE INTERNAL ""
)

set(INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/cxxorm/inc
        CACHE INTERNAL ""
)

add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/main.cpp

        ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${INCLUDE_DIRS}
)