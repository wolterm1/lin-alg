cmake_minimum_required(VERSION 3.12)

project(
  MatrixLinAlgProject
  VERSION 1.0
  LANGUAGES CXX)

# ASAN
set(ENABLE_ASAN ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(matrix tests/matrix.cpp)

add_executable(matrix_iter tests/matrix_iterator_test.cpp)

add_executable(matrix_operator_test tests/operators.cpp)

add_executable(vector_test tests/vector_tests.cpp)

add_executable(nn_test src/nntest.cpp neural_net/net.cpp neural_net/helper.cpp neural_net/EvalResult.cpp)

add_executable(loadEval src/loadEval.cpp neural_net/net.cpp neural_net/helper.cpp neural_net/EvalResult.cpp)

set(MY_TARGETS matrix matrix_iter matrix_operator_test vector_test nn_test loadEval)

target_include_directories(nn_test PRIVATE ${PROJECT_SOURCE_DIR}/neural_net)
target_compile_options(nn_test PRIVATE -fsanitize=address)
target_link_options(nn_test PRIVATE -fsanitize=address)

target_include_directories(loadEval PRIVATE ${PROJECT_SOURCE_DIR}/neural_net)
target_compile_options(loadEval PRIVATE -fsanitize=address)
target_link_options(loadEval PRIVATE -fsanitize=address)

foreach(target ${MY_TARGETS})
  target_include_directories(${target} PRIVATE ${PROJECT_SOURCE_DIR}/include)

  if(ENABLE_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
  endif()
endforeach()
