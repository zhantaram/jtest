cmake_minimum_required(VERSION 3.31)

project(jtest LANGUAGES CXX)

#------------------------------------------------------------------------------
# Library target
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
  src/jtest.cppm

  src/utils.cppm
  src/asserts.cppm
  src/registry.cppm
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

#------------------------------------------------------------------------------
# Library target
add_executable(example
  example/main.cpp
)
target_link_libraries(example PUBLIC ${PROJECT_NAME})

