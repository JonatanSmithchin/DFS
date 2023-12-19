cmake_minimum_required(VERSION 3.22.1)

aux_source_directory(. INODE)

add_library(INode SHARED ${INODE})