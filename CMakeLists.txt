cmake_minimum_required(VERSION 3.28)
project(CPP_SE)

set(CMAKE_CXX_STANDARD 20)

include_directories(./easyx/include)
link_directories(./easyx/lib64)
link_libraries(libeasyx.a)

set(PostgreSQL_INCLUDE_DIR "C:/Program Files/PostgreSQL/17/include")
set(PostgreSQL_LIBRARY "C:/Program Files/PostgreSQL/17/lib/libpq.lib")

add_subdirectory(./libpqxx build-libpqxx)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")

add_executable(CPP_SE ${SOURCES} ${HEADERS})

target_link_libraries(CPP_SE PRIVATE pqxx)