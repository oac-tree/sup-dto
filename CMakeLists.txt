cmake_minimum_required(VERSION 3.5)

project(sup-dto-project-all VERSION 0.1.0)

option(NO_CODAC "Don't look for the presence of CODAC environment" OFF)

add_subdirectory(src)
add_subdirectory(test)
