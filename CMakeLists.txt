cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD 1)

project(jtest LANGUAGES CXX)

#------------------------------------------------------------------------------
# Library target
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
  src/jtest.cppm
  src/utils.cppm
  src/asserts.cppm
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

#------------------------------------------------------------------------------
# Library target
add_executable(example
  example/main.cpp
)
target_link_libraries(example PUBLIC ${PROJECT_NAME})

