cmake_minimum_required(VERSION 3.10)
project(EndGame_ucode)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES main.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include SDL2
if (WIN32)
    # For Windows
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL2/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2main.lib ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib)
elseif(UNIX)
    # For Unix-like systems
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
endif()