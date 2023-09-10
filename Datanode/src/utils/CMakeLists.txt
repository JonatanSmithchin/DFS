cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(. UTILS)
add_library(utils STATIC ${UTILS})