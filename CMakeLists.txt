cmake_minimum_required(VERSION 3.14)
project(lextsuggest VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default install path" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(DATA_INSTALL_DIR "share/${PROJECT_NAME}")
set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")

configure_file(
    "${CMAKE_SOURCE_DIR}/src/config.hpp.in"
    "${CMAKE_BINARY_DIR}/include/config.hpp"
    @ONLY
)

# extra files/directories to be removed during clean
set_property(DIRECTORY APPEND PROPERTY 
    ADDITIONAL_MAKE_CLEAN_FILES 
    "${CMAKE_BINARY_DIR}/bin"
    "${CMAKE_BINARY_DIR}/lib"
    "${CMAKE_BINARY_DIR}/src"
    "${CMAKE_BINARY_DIR}/include"
    "${CMAKE_BINARY_DIR}/cmake_install.cmake"
    "${CMAKE_SOURCE_DIR}/cmake"
)

add_subdirectory(src)

install(DIRECTORY ${DATA_DIR}/
        DESTINATION ${DATA_INSTALL_DIR}
        FILES_MATCHING PATTERN "*.txt")

file(COPY ${DATA_DIR}/
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data
     FILES_MATCHING PATTERN "*.txt")

add_custom_target(local-install
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install -P cmake_install.cmake
    DEPENDS lextsuggest
)
