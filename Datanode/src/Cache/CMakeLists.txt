cmake_minimum_required(VERSION 3.22.1)

aux_source_directory(. CACHE)

add_library(Cache STATIC ${CACHE})
