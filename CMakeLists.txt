cmake_minimum_required(VERSION 3.12)

project(
  MatrixLinAlgProject
  VERSION 1.0
  LANGUAGES CXX)

# ASAN aktivieren
set(ENABLE_ASAN ON)

# C++20 aktivieren
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable erstellen
add_executable(matrix tests/matrix.cpp)

add_executable(matrix_iter tests/matrix_iterator_test.cpp)

add_executable(matrix_operator_test tests/operators.cpp)

add_executable(vector_test tests/vector.cpp)

# Include-Verzeichnisse angeben

set(MY_TARGETS matrix matrix_iter matrix_operator_test vector_test)

# Include-Verzeichnisse und ggf. ASAN auf alle Targets anwenden
foreach(target ${MY_TARGETS})
  target_include_directories(${target} PRIVATE ${PROJECT_SOURCE_DIR}/include)

  if(ENABLE_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
  endif()
endforeach()
