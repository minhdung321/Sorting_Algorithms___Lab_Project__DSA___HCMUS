cmake_minimum_required(VERSION 3.15)
project(Sorting)

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory to the project
include_directories(include)

# Add the source files to the project
file(GLOB_RECURSE SOURCES "src/*.cpp") 

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

# Option to enable/disable march=native
option(USE_MARCH_NATIVE "Enable -march=native flag" ON) 

# Add the executable
add_executable(Sorting ${SOURCES})

# Set compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Sorting PRIVATE
        $<$<CONFIG:DEBUG>:-g -O0 -fopenmp>
        $<$<CONFIG:RELEASE>:-O3 -DNDEBUG -fopenmp>
    )
    if(USE_MARCH_NATIVE)
        target_compile_options(Sorting PRIVATE -march=native)
    endif()
    target_compile_definitions(Sorting PRIVATE "LINUX")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Sorting PRIVATE
        $<$<CONFIG:DEBUG>:/Zi /Od /RTC1 /openmp>
        $<$<CONFIG:RELEASE>:/O2 /Ob2 /DNDEBUG /openmp /arch:AVX2>
    )
    target_compile_definitions(Sorting PRIVATE "WINDOWS")
endif()
