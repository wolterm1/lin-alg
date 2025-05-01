cmake_minimum_required(VERSION 3.12)

project(MatrixLinAlgProject VERSION 1.0 LANGUAGES CXX)

# ASAN aktivieren
set(ENABLE_ASAN ON)

# C++20 aktivieren
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Quellcode-Dateien automatisch einlesen
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE TESTS tests/*.cpp)

# Executable erstellen
add_executable(matrix ${SOURCES})

add_executable(matrix_iter ${TESTS})

# Include-Verzeichnisse angeben
target_include_directories(matrix PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Compiler-Optionen
if(ENABLE_ASAN)
    target_compile_options(matrix PRIVATE -fsanitize=address)
    target_link_options(matrix PRIVATE -fsanitize=address)
endif()

