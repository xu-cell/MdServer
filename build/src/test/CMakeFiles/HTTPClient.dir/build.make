# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ecs-user/MdServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ecs-user/MdServer/build

# Include any dependencies generated for this target.
include src/test/CMakeFiles/HTTPClient.dir/depend.make

# Include the progress variables for this target.
include src/test/CMakeFiles/HTTPClient.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/CMakeFiles/HTTPClient.dir/flags.make

src/test/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o: src/test/CMakeFiles/HTTPClient.dir/flags.make
src/test/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o: ../src/test/HTTPClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ecs-user/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/test/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o"
	cd /home/ecs-user/MdServer/build/src/test && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o -c /home/ecs-user/MdServer/src/test/HTTPClient.cpp

src/test/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HTTPClient.dir/HTTPClient.cpp.i"
	cd /home/ecs-user/MdServer/build/src/test && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ecs-user/MdServer/src/test/HTTPClient.cpp > CMakeFiles/HTTPClient.dir/HTTPClient.cpp.i

src/test/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HTTPClient.dir/HTTPClient.cpp.s"
	cd /home/ecs-user/MdServer/build/src/test && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ecs-user/MdServer/src/test/HTTPClient.cpp -o CMakeFiles/HTTPClient.dir/HTTPClient.cpp.s

# Object files for target HTTPClient
HTTPClient_OBJECTS = \
"CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o"

# External object files for target HTTPClient
HTTPClient_EXTERNAL_OBJECTS =

../bin/HTTPClient: src/test/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o
../bin/HTTPClient: src/test/CMakeFiles/HTTPClient.dir/build.make
../bin/HTTPClient: src/test/CMakeFiles/HTTPClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ecs-user/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/HTTPClient"
	cd /home/ecs-user/MdServer/build/src/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HTTPClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/CMakeFiles/HTTPClient.dir/build: ../bin/HTTPClient

.PHONY : src/test/CMakeFiles/HTTPClient.dir/build

src/test/CMakeFiles/HTTPClient.dir/clean:
	cd /home/ecs-user/MdServer/build/src/test && $(CMAKE_COMMAND) -P CMakeFiles/HTTPClient.dir/cmake_clean.cmake
.PHONY : src/test/CMakeFiles/HTTPClient.dir/clean

src/test/CMakeFiles/HTTPClient.dir/depend:
	cd /home/ecs-user/MdServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ecs-user/MdServer /home/ecs-user/MdServer/src/test /home/ecs-user/MdServer/build /home/ecs-user/MdServer/build/src/test /home/ecs-user/MdServer/build/src/test/CMakeFiles/HTTPClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/test/CMakeFiles/HTTPClient.dir/depend
