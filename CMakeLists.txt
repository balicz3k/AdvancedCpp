cmake_minimum_required(VERSION 3.16)

project(AdvancedCpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_WARNINGS ON)
option(ENABLE_ASAN OFF)

function(enable_target_warnings target)
    if(NOT ENABLE_WARNINGS)
        return()
    endif()
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
    endif()
endfunction()

if(ENABLE_ASAN AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address -fno-omit-frame-pointer)
    endif()
endif()

add_subdirectory(modules/Polymorphism)
add_subdirectory(modules/SmartPointers)
add_subdirectory(modules/Multithreading)
add_subdirectory(modules/Coroutines)

