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
include src/base/tests/CMakeFiles/LoggingTest.dir/depend.make

# Include the progress variables for this target.
include src/base/tests/CMakeFiles/LoggingTest.dir/progress.make

# Include the compile flags for this target's objects.
include src/base/tests/CMakeFiles/LoggingTest.dir/flags.make

src/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o: src/base/tests/CMakeFiles/LoggingTest.dir/flags.make
src/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o: ../src/base/tests/LoggingTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ecs-user/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o"
	cd /home/ecs-user/MdServer/build/src/base/tests && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o -c /home/ecs-user/MdServer/src/base/tests/LoggingTest.cpp

src/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoggingTest.dir/LoggingTest.cpp.i"
	cd /home/ecs-user/MdServer/build/src/base/tests && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ecs-user/MdServer/src/base/tests/LoggingTest.cpp > CMakeFiles/LoggingTest.dir/LoggingTest.cpp.i

src/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoggingTest.dir/LoggingTest.cpp.s"
	cd /home/ecs-user/MdServer/build/src/base/tests && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ecs-user/MdServer/src/base/tests/LoggingTest.cpp -o CMakeFiles/LoggingTest.dir/LoggingTest.cpp.s

# Object files for target LoggingTest
LoggingTest_OBJECTS = \
"CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o"

# External object files for target LoggingTest
LoggingTest_EXTERNAL_OBJECTS =

../bin/LoggingTest: src/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o
../bin/LoggingTest: src/base/tests/CMakeFiles/LoggingTest.dir/build.make
../bin/LoggingTest: src/base/libserver_base.a
../bin/LoggingTest: src/base/tests/CMakeFiles/LoggingTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ecs-user/MdServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../bin/LoggingTest"
	cd /home/ecs-user/MdServer/build/src/base/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LoggingTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/base/tests/CMakeFiles/LoggingTest.dir/build: ../bin/LoggingTest

.PHONY : src/base/tests/CMakeFiles/LoggingTest.dir/build

src/base/tests/CMakeFiles/LoggingTest.dir/clean:
	cd /home/ecs-user/MdServer/build/src/base/tests && $(CMAKE_COMMAND) -P CMakeFiles/LoggingTest.dir/cmake_clean.cmake
.PHONY : src/base/tests/CMakeFiles/LoggingTest.dir/clean

src/base/tests/CMakeFiles/LoggingTest.dir/depend:
	cd /home/ecs-user/MdServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ecs-user/MdServer /home/ecs-user/MdServer/src/base/tests /home/ecs-user/MdServer/build /home/ecs-user/MdServer/build/src/base/tests /home/ecs-user/MdServer/build/src/base/tests/CMakeFiles/LoggingTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/base/tests/CMakeFiles/LoggingTest.dir/depend

