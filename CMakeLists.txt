cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Glob all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Loop through each source file and create an executable
foreach(SOURCE_FILE ${SOURCES})
	# Get the file name without the extension
	get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
	
	# Add the executable
	add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
endforeach()