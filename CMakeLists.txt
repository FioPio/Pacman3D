cmake_minimum_required(VERSION 3.12)
project(pacman3D)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#find_package(Curses REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include/GameEngine)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

# Link with the ncurses library
#target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
# Link against the ncursesw library
target_link_libraries(${PROJECT_NAME} ncursesw)

# Install executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)