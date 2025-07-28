# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Donga VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)   # Enforce the standard

# Specify output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

# Define the source files
set(SOURCES common/dongaLogger.cpp src/main.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# apply the linker flag globally to all executables 
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")


# Define the precomipiled header file
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/common/pch.H")

target_link_libraries(${PROJECT_NAME} pthread)